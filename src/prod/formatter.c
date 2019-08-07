/*
 * File: formatter.c
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "fmacro.h"
#include "formatter.h"
#include "string_util.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

static const char* const MONTHS[12] =
{ "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
  "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };

/* Starts from Sunday because in the struct tm returned by localtime()
tm_day value of 0 equals Sunday. */
static const char* const WEEKDAYS[7] =
{ "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY",
  "THURSDAY", "FRIDAY", "SATURDAY" };

static size_t _formatter_expand_fm(const formatter_t* formatter,
                                   char* dest,
                                   LG_FM_ID fm,
                                   const char* msg,
                                   LG_LEVEL lvl);

static void _formatter_get_time(formatter_t* formatter);

static size_t _formatter_fm_as_str(const formatter_t* formatter,
                                   char* dest,
                                   const char* src);

static fm_info_t _formatter_recognize_fm(const formatter_t* formatter,
                                         const char* src);

static char* _formatter_do_format(formatter_t* formatter,
                                  char* dest,
                                  const char* msg,
                                  LG_LEVEL lvl);

static char* _formatter_get_mname(const formatter_t* formatter,
                                  char* dest,
                                  char* decapitalize_from);

static char* _formatter_get_wday(const formatter_t* formatter,
                                 char* dest,
                                 char* decapitalize_from);

static char* _get_lvl(LG_LEVEL lvl,
                      char* dest,
                      char* decapitalize_from);

bool _formatter_is_valid_format(const formatter_t* formatter, const char* format);

formatter_t* formatter_init(formatter_t* buffer, const char* format, uint16_t flags)
{
    formatter_t* formatter = buffer;
    if (!formatter)
    {
        formatter = LG_alloc(sizeof(formatter_t));
    }

    if (formatter)
    {
        formatter->flags = flags;
        memset(&(formatter->time), 0x00, sizeof(struct tm));
        if (formatter_set(formatter, format))
        {
            return formatter;
        }
    }

    /* Memory allocation failed or format was invalid. Clean up
    and return NULL. */
    if (formatter)
    {
        LG_dealloc(formatter);
    }
    return NULL;
}

void formatter_free(formatter_t* formatter)
{
    LG_dealloc(formatter);
}

bool formatter_set(formatter_t* formatter, const char* format)
{
    if (!_formatter_is_valid_format(formatter, format))
    {
        return false;
    }
    
    strcpy(formatter->format, format);

    return true;
}

char* formatter_get(formatter_t* formatter, char* dest)
{
    strcpy(dest, formatter->format);
    return dest;
}

char* formatter_entry(formatter_t* formatter,
                   char* dest,
                   const char* msg,
                   LG_LEVEL lvl)
{
    assert(formatter->flags & LG_FORMAT_ENTRIES);
    return _formatter_do_format(formatter, dest, msg, lvl);
}

char* formatter_path(formatter_t* formatter, char* dest)
{
    assert(formatter->flags & LG_FORMAT_PATHS);
    return _formatter_do_format(formatter, dest, NULL, LG_NO_LEVEL);
}

static void _formatter_get_time(formatter_t* formatter)
{
    time_t raw_time;
    time(&raw_time);
    memcpy(&(formatter->time), localtime(&raw_time), sizeof(struct tm));
}

size_t _formatter_fm_as_str(const formatter_t* formatter, char* dest, const char* src)
{
    size_t fm_len = 0;

    assert(*src == LG_FM_BEGIN_INDIC);
    char* left_delim = strchr(src, LG_FM_LEFT_DELIM);
    char* right_delim = strchr(src, LG_FM_RIGHT_DELIM);

    if (left_delim && right_delim && left_delim == src + 1)
    {
        if (left_delim < right_delim)
        {
            /* The length of the fm body. */
            fm_len = right_delim - src - 2;
            strncpy(dest, left_delim + 1, fm_len);
            dest[fm_len] = '\0';
            /* Add the length of the begin indicator and delimiters. */
            fm_len += 3;
        }
    }
    return fm_len;
}

static fm_info_t _formatter_recognize_fm(const formatter_t* formatter, const char* src)
{
    char fm_str[LG_MAX_FM_S_LEN];

    fm_info_t fm = { "", 0, LG_FM_NO_MACRO };
    if (*src != LG_FM_BEGIN_INDIC)
    {
        return fm;
    }

    fm.len = _formatter_fm_as_str(formatter, fm_str, src);
    if (fm.len != 0)
    {
        for (size_t i = 0; i < LG_FM_COUNT; ++i)
        {
            if (strcmp(fm_str, _FM_TABLE[i].str) == 0)
            {
                fm.id = i + 1;
            }
        }
    }
    return fm;
}

static char* _formatter_do_format(formatter_t* formatter,
                                  char* dest,
                                  const char* msg,
                                  LG_LEVEL lvl)
{
    _formatter_get_time(formatter);

    char* orig_dest = dest;
    char* src = formatter->format;
    char* src_fm_begin = strchr(src, LG_FM_BEGIN_INDIC);
    while (src_fm_begin != NULL)
    {
        /* TODO Optimize */
        while (src != src_fm_begin)
        {
            *(dest++) = *(src++);
        }
        fm_info_t fm = _formatter_recognize_fm(formatter, src_fm_begin);
        if (fm.id != LG_FM_NO_MACRO)
        {
            dest += _formatter_expand_fm(formatter, dest, fm.id, msg, lvl);
            src += fm.len;
        }
        else
        {
            *(dest++) = *(src++);
        }
        src_fm_begin = strchr(src, LG_FM_BEGIN_INDIC);
    }
    while (*src != '\0')
    {
        *(dest++) = *(src++);
    }
    *dest = *src;
    return orig_dest;
}

size_t _formatter_expand_fm(const formatter_t* formatter,
                            char* dest,
                            LG_FM_ID fm,
                            const char* msg,
                            LG_LEVEL lvl)
{
    assert(fm != LG_FM_NO_MACRO);

    char format[8] = "%0*d";

    switch (fm)
    {
        case LG_FM_YEAR:
            return sprintf(dest, format, 4, formatter->time.tm_year + 1900);
        case LG_FM_MONTH:
            return sprintf(dest, format, 2, formatter->time.tm_mon + 1);
        case LG_FM_MDAY:
            return sprintf(dest, format, 2, formatter->time.tm_mday);
        case LG_FM_HOUR:
            return sprintf(dest, format, 2, formatter->time.tm_hour);
        case LG_FM_MIN:
            return sprintf(dest, format, 2, formatter->time.tm_min);
        case LG_FM_SEC:
            return sprintf(dest, format, 2, formatter->time.tm_sec);
    }

    strcpy(format, "%.*s");
    char source[32];
    size_t copy_amount = 0;
    switch (fm)
    {
        case LG_FM_MNAME_S_F:
            _formatter_get_mname(formatter, source, source + 1);
            copy_amount = LG_FM_MNAME_S_EXP_SIZE;
            break;
        case LG_FM_MNAME_S_A:
            _formatter_get_mname(formatter, source, NULL);
            copy_amount = LG_FM_MNAME_S_EXP_SIZE;
            break;
        case LG_FM_MNAME_L_F:
            _formatter_get_mname(formatter, source, source + 1);
            copy_amount = LG_MAX_FM_MNAME_L_EXP_SIZE;
            break;
        case LG_FM_MNAME_L_A:
            _formatter_get_mname(formatter, source, NULL);
            copy_amount = LG_MAX_FM_MNAME_L_EXP_SIZE;
            break;
        case LG_FM_WDAY_S_F:
            _formatter_get_wday(formatter, source, source + 1);
            copy_amount = LG_FM_WDAY_S_EXP_SIZE;
            break;
        case LG_FM_WDAY_S_A:
            _formatter_get_wday(formatter, source, NULL);
            copy_amount = LG_FM_WDAY_S_EXP_SIZE;
            break;
        case LG_FM_WDAY_L_F:
            _formatter_get_wday(formatter, source, source + 1);
            copy_amount = LG_MAX_FM_WDAY_L_EXP_SIZE;
            break;
        case LG_FM_WDAY_L_A:
            _formatter_get_wday(formatter, source, NULL);
            copy_amount = LG_MAX_FM_WDAY_L_EXP_SIZE;
            break;
        case LG_FM_LVL_N:
            _get_lvl(lvl, source, source);
            copy_amount = LG_FM_LVL_MAX_LEN;
            break;
        case LG_FM_LVL_F:
            _get_lvl(lvl, source, source + 1);
            copy_amount = LG_FM_LVL_MAX_LEN;
            break;
        case LG_FM_LVL_A:
            _get_lvl(lvl, source, NULL);
            copy_amount = LG_FM_LVL_MAX_LEN;
            break;
        case LG_FM_MSG:
            return sprintf(dest, format, LG_MAX_MSG_SIZE, msg);
        default:
            assert(0);
    }
    copy_amount = sprintf(dest, format, copy_amount, source);
    return copy_amount;
}

char* _formatter_get_mname(const formatter_t* formatter, char* dest, char* decapitalize_from)
{
    strcpy(dest, MONTHS[formatter->time.tm_mon]);
    if (decapitalize_from)
    {
        LG_str_to_lower(decapitalize_from);
    }
    return dest;
}

char* _formatter_get_wday(const formatter_t* formatter, char* dest, char* decapitalize_from)
{
    strcpy(dest, WEEKDAYS[formatter->time.tm_wday]);
    if (decapitalize_from)
    {
        LG_str_to_lower(decapitalize_from);
    }
    return dest;
}

char* _get_lvl(LG_LEVEL lvl, char* dest, char* decapitalize_from)
{
    strcpy(dest, LG_LEVEL_STRS[lvl]);
    if (decapitalize_from)
    {
        LG_str_to_lower(decapitalize_from);
    }
    return dest;
}

bool _formatter_is_valid_format(const formatter_t* formatter, const char* format)
{
    size_t max_len = 0;

    while (*format != '\0')
    {
        size_t macro_len = 1;
        size_t exp_macro_len = 1;
        if (*format == LG_FM_BEGIN_INDIC)
        {
            fm_info_t fm = _formatter_recognize_fm(formatter, format);
            if (fm.id != LG_FM_NO_MACRO)
            {
                exp_macro_len = _FM_TABLE[fm.id].len;
            }
            if (formatter->flags & LG_FORMAT_PATHS)
            {
                switch (fm.id)
                {
                    case LG_FM_MSG:
                    case LG_FM_LVL_N:
                    case LG_FM_LVL_F:
                    case LG_FM_LVL_A:
                        return false;
                    default:
                        break;
                }
            }
        }
        format += macro_len;
        max_len += exp_macro_len;
    }

    uint16_t a = formatter->flags;

    if (formatter->flags & LG_FORMAT_PATHS
            && max_len < LG_MAX_FNAME_SIZE - 1)
    {
        return true;
    }
    else if (formatter->flags & LG_FORMAT_ENTRIES
                 && max_len < LG_MAX_ENTRY_SIZE - 1)
    {
        return true;
    }

    return false;
}
