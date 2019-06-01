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
#include <stdbool.h>
#include <string.h>

void _format_str(const char* format,
                 char* dest,
                 thandler_t* th,
                 const char* msg,
                 LOG_LEVEL lvl);

static bool _is_valid_fn_form(const char* format);

static bool _is_valid_e_form(const char* format);

/* File name formatter functions. */

fn_format_t* fnf_init(const char* format)
{
    fn_format_t* new_fnf = _log_alloc(sizeof(fn_format_t));
    thandler_t* new_th = th_init();

    if (new_fnf && new_th
        && fnf_set_format(new_fnf, format))
    {
        new_fnf->_th = new_th;
        return new_fnf;
    }

    /* Memory allocation failed or format was invalid. Clean up
    and return NULL. */
    if (new_fnf)
    {
        _log_dealloc(new_fnf);
    }
    return NULL;
}

bool fnf_set_format(fn_format_t* const fnf, const char* format)
{
    if (!_is_valid_fn_form(format))
    {
        return false;
    }

    strcpy(fnf->_form, format);

    return true;
}

void fnf_format(fn_format_t* fnf, char* dest)
{
    _format_str(fnf->_form, dest,
        fnf->_th, NULL, _L_NO_LEVEL);
}

void fnf_close(fn_format_t* fnf)
{
    th_close(fnf->_th);
    _log_dealloc(fnf);
}

/* Entry formatter functions. */

e_format_t* ef_init(const char* format)
{
    e_format_t* new_ef = _log_alloc(sizeof(e_format_t));
    thandler_t* new_th = th_init();

    if (new_ef && new_th && ef_set_format(new_ef, format))
    {
        new_ef->_th = new_th;
        return new_ef;
    }

    /* Memory allocation failed or format was invalid. Clean up
    and return NULL. */
    if (new_ef)
    {
        _log_dealloc(new_ef);
    }
    return NULL;
}

bool ef_set_format(e_format_t* const ef, const char* format)
{
    if (!_is_valid_e_form(format))
    {
        return false;
    }

    strcpy(ef->_form, format);
    return true;
}

void ef_format(e_format_t* ef, char* dest, const char* src, LOG_LEVEL lvl)
{
    _format_str(ef->_form, dest,
        ef->_th, src, lvl);
}

void ef_close(e_format_t* ef)
{
    th_close(ef->_th);
    _log_dealloc(ef);
}

/* Helper functions. */

/* Expands all format macros starting from format, writing the expanded
string to dest. Th will be used to expand time-related macros.
Msg contains the log message entered by the user, if any.
Lvl contains the log level of the message, if any.
Msg and lvl may be omitted when this function is used to
format a file name, since they are meaningless in that context. */
void _format_str(const char* format,
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
}

/* Returns true if format is valid, i.e. contains no illegal
macros and has a maximum length < _MAX_FILENAME_SIZE - 1
when expanded. */
bool _is_valid_fn_form(const char* format)
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
bool _is_valid_e_form(const char* format)
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
