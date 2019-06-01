/*
 * File: formatter.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "fm_parser.h"
#include "formatter.h"
#include "string_util.h"
#include "time_handler.h"
#include <assert.h>
#include <string.h>

char* _format_str(const char* format,
                  char* dest,
                  thandler_t* th,
                  const char* msg,
                  LOG_LEVEL lvl);

static bool _is_valid_path_format(const char* format);

static bool _is_valid_entry_format(const char* format);

format_t* format_init(const char* format, uint8_t flags)
{
    if (!((flags & FORMAT_PATHS) || (flags & FORMAT_ENTRIES)))
    {
        return NULL;
    }

    format_t* formatter = _log_alloc(sizeof(format_t));
    thandler_t* thandler = th_init();

    if (formatter && thandler)
    {
        formatter->_flags = flags;
        formatter->_thandler = thandler;
        if (format_set(formatter, format))
        {
            return formatter;
        }
    }

    /* Memory allocation failed or format was invalid. Clean up
    and return NULL. */
    if (formatter)
    {
        _log_dealloc(formatter);
    }
    if (thandler)
    {
        _log_dealloc(formatter);
    }
    return NULL;
}

void format_free(format_t* formatter)
{
    th_free(formatter->_thandler);
    _log_dealloc(formatter);
}

bool format_set(format_t* formatter, const char* format)
{
    if (formatter->_flags & FORMAT_PATHS
            && !_is_valid_path_format(format))
    {
        return false;
    }
    else if (formatter->_flags & FORMAT_ENTRIES
                 && !_is_valid_entry_format(format))
    {
        return false;
    }
    
    strcpy(formatter->_format, format);

    return true;
}

char* format_entry(format_t* formatter,
                   char* dest,
                   const char* msg,
                   LOG_LEVEL level)
{
    assert(formatter->_flags & FORMAT_ENTRIES);

    return _format_str(formatter->_format,
                       dest,
                       formatter->_thandler,
                       msg,
                       level);
}

char* format_path(format_t* formatter, char* dest)
{
    assert(formatter->_flags & FORMAT_PATHS);

    _format_str(formatter->_format,
                dest,
                formatter->_thandler,
                NULL,
                _L_NO_LEVEL);
    return dest;
}

/* Helper functions. */

/* Expands all format macros starting from format, writing the expanded
string to dest. Th will be used to expand time-related macros.
Msg contains the log message entered by the user, if any.
Lvl contains the log level of the message, if any.
Msg and lvl may be omitted when this function is used to
format a file name, since they are meaningless in that context. */
char* _format_str(const char* format,
                  char* dest,
                  thandler_t* th,
                  const char* msg,
                  LOG_LEVEL lvl)
{
    /* If message is given, logging level must also be given (this function
    was called by the entry formatter) - if not, logging level must not be
    given either (called by filename formatter). */
    assert((msg && lvl != _L_NO_LEVEL) || (!msg && lvl == _L_NO_LEVEL));

    /* Fetch the local time for time-related macros so they all
    refer to the same point in time. */
    th_fetch_ltime(th);

    while (*format != '\0')
    {
        if (*format != _FM_BEGIN_INDIC)
        {
            /* No macro begin encountered. */
            *dest = *format;
            ++dest;
            ++format;
        }
        else
        {
            /* Macro begin encountered. */

            /* Unexpanded macro length. */
            size_t macro_len = 0;
            /* Expanded macro length. */
            size_t exp_macro_len = 0;
            /* Expand the macro. */
            _expand_fm(format, dest, th, msg, lvl, &macro_len, &exp_macro_len);

            if (macro_len == 0 && exp_macro_len == 0)
            {
                /* False alarm, no valid macro found. */
                *dest = *format;
                macro_len = 1;
                exp_macro_len = 1;
            }
            format += macro_len;
            dest += exp_macro_len;
        }
    }
    /* Add the null terminator which was excluded in the
    while loop. */
    assert(*format == '\0');
    *dest = *format;
    return dest;
}

/* Returns true if format is valid, i.e. contains no illegal
macros and has a maximum length < _MAX_FILENAME_SIZE - 1
when expanded. */
bool _is_valid_path_format(const char* format)
{
    size_t max_len = 0;

    while (*format != '\0')
    {
        size_t macro_len = 1;
        size_t exp_macro_len = 1;
        if (*format == _FM_BEGIN_INDIC)
        {
            _FM_ID id = _identify_fm(format, &macro_len);
            if (id != _FM_NO_MACRO)
            {
                exp_macro_len = _FM_TABLE[id].max_len;
            }
            switch (id)
            {
                case _FM_MSG:
                case _FM_LVL_N:
                case _FM_LVL_F:
                case _FM_LVL_A:
                    return false;
                default:
                    break;
            }
        }
        format += macro_len;
        max_len += exp_macro_len;
    }

    if (max_len < _MAX_FILENAME_SIZE - 1)
    {
        return true;
    }

    return false;
}

/* Returns true if format is valid, i.e. contains no illegal macros and
has a maximum length < _MAX_ENTRY_SIZE - 1 when expanded. */
bool _is_valid_entry_format(const char* format)
{
    size_t max_len = 0;

    while (*format != '\0')
    {
        size_t macro_len = 1;
        size_t exp_macro_len = 1;
        if (*format == _FM_BEGIN_INDIC)
        {
            _FM_ID id = _identify_fm(format, &macro_len);
            if (id != _FM_NO_MACRO)
            {
                exp_macro_len = _FM_TABLE[id].max_len;
            }
        }
        format += macro_len;
        max_len += exp_macro_len;
    }

    if (max_len < _MAX_ENTRY_SIZE - 1)
    {
        return true;
    }

    return false;
}
