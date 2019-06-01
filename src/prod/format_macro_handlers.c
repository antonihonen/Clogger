/*
 * File: format_macro_handlers.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "format_macro.h"
#include "format_macro_handlers.h"
#include "macros.h"
#include "string_util.h"
#include <assert.h>
#include <string.h>

/* TODO: Make the handlers not to add the null terminator
to the char buffers they write in.*/

/* Writes src to dest and adds spaces until dest is target_len chars long. */
static size_t
_write_and_pad(char* dest, char* src, size_t target_len)
{
    strcpy(dest, src);
    size_t len = strlen(src);
    dest += len;

    while (len < target_len)
    {
        *dest = ' ';
        ++dest;
        ++len;
    }
    *dest = '\0';

    return len;
}

void _fm_year_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char year_str[_FM_YEAR_EXP_SIZE];
    th_get_year(thandler, year_str);
    strcpy(dest, year_str);
    *exp_macro_len = strlen(dest);
}

void _fm_month_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char month_str[_FM_MONTH_EXP_SIZE];
    th_get_month(thandler, month_str);
    strcpy(dest, month_str);
    *exp_macro_len = strlen(dest);
}

void _fm_mday_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char mday_str[_FM_MDAY_EXP_SIZE];
    th_get_mday(thandler, mday_str);
    strcpy(dest, mday_str);
    *exp_macro_len = strlen(dest);
}

void _fm_hour_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char hour_str[_FM_HOUR_EXP_SIZE];
    th_get_hour(thandler, hour_str);
    strcpy(dest, hour_str);
    *exp_macro_len = strlen(dest);
}

void _fm_min_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char min_str[_FM_MIN_EXP_SIZE];
    th_get_min(thandler, min_str);
    strcpy(dest, min_str);
    *exp_macro_len = strlen(dest);
}

void _fm_sec_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char sec_str[_FM_SEC_EXP_SIZE];
    th_get_sec(thandler, sec_str);
    strcpy(dest, sec_str);
    *exp_macro_len = strlen(dest);
}

void _fm_mname_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char mname_str[_MAX_FM_MNAME_L_EXP_SIZE];
    th_get_mname(thandler, mname_str, _MN_SHORT_FIRST_CAP);
    strcpy(dest, mname_str);
    *exp_macro_len = strlen(dest);
}

void _fm_mname_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char mname_str[_MAX_FM_MNAME_L_EXP_SIZE];
    th_get_mname(thandler, mname_str, _MN_SHORT_ALL_CAPS);
    strcpy(dest, mname_str);
    *exp_macro_len = strlen(dest);
}

void _fm_mname_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char mname_str[_MAX_FM_MNAME_L_EXP_SIZE];
    th_get_mname(thandler, mname_str, _MN_LONG_FIRST_CAP);
    strcpy(dest, mname_str);
    *exp_macro_len = strlen(dest);
}

void _fm_mname_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char mname_str[_MAX_FM_MNAME_L_EXP_SIZE];
    th_get_mname(thandler, mname_str, _MN_LONG_ALL_CAPS);
    strcpy(dest, mname_str);
    *exp_macro_len = strlen(dest);
}

void _fm_wday_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char wday_str[_MAX_FM_WDAY_L_EXP_SIZE];
    th_get_wday(thandler, wday_str, _WD_SHORT_FIRST_CAP);
    strcpy(dest, wday_str);
    *exp_macro_len = strlen(dest);
}

void _fm_wday_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char wday_str[_MAX_FM_WDAY_L_EXP_SIZE];
    th_get_wday(thandler, wday_str, _WD_SHORT_ALL_CAPS);
    strcpy(dest, wday_str);
    *exp_macro_len = strlen(dest);
}

void _fm_wday_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char wday_str[_MAX_FM_WDAY_L_EXP_SIZE];
    th_get_wday(thandler, wday_str, _WD_LONG_FIRST_CAP);
    
    strcpy(dest, wday_str);
    *exp_macro_len = strlen(dest);
}

void _fm_wday_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len)
{
    assert(thandler); assert(dest); assert(exp_macro_len);
    assert(th_has_legal_state(thandler));

    char wday_str[_MAX_FM_WDAY_L_EXP_SIZE];
    th_get_wday(thandler, wday_str, _WD_LONG_ALL_CAPS);
    
    strcpy(dest, wday_str);

    *exp_macro_len = strlen(dest);
}

void _fm_lvl_n_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __, size_t* exp_macro_len)
{
    assert(dest); assert(exp_macro_len);

    char* exp_macro = _LOG_LEVEL_STRS[level];
    _ascii_str_to_lower(exp_macro);
    *exp_macro_len = _write_and_pad(dest, exp_macro, _FM_LVL_MAX_LEN);
}

void _fm_lvl_f_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __, size_t* exp_macro_len)
{
    assert(dest); assert(exp_macro_len);

    char* const exp_macro = _LOG_LEVEL_STRS[level];
    _ascii_str_to_lower(exp_macro + 1);
    *exp_macro_len = _write_and_pad(dest, exp_macro, _FM_LVL_MAX_LEN);
}

void _fm_lvl_a_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __, size_t* exp_macro_len)
{
    assert(dest); assert(exp_macro_len);
    
    *exp_macro_len = _write_and_pad(dest, _LOG_LEVEL_STRS[level], _FM_LVL_MAX_LEN);
}

void _fm_msg_handler(thandler_t* _, char* dest, LOG_LEVEL __, char* msg, size_t* exp_macro_len)
{
    assert(dest); assert(msg); assert(exp_macro_len);

    strcpy(dest, msg);
    *exp_macro_len = strlen(dest);
}
