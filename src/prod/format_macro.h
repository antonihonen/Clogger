/*
 * File: format_macro.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains items related to format
 * macros. Format macros can be used
 * to format file names and log entries. A valid
 * format macro is a sequence of characters that
 * conforms to the form "<1><2><3><4>",
 * where
 *
 * 1 = _FM_BEGIN_INDIC (begin indicator)
 * 2 = _FM_LEFT_DELIM (left delimiter)
 * 3 = a valid macro body (one of the values in the _FORMAT_MACROS array)
 * 4 = _FM_RIGHT_DELIM (right delimiter)
 * 
 * All of the values presented above have been defined in this module.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef FORMAT_MACRO_H
#define FORMAT_MACRO_H

#include "format_macro_handlers.h"
#include "macros.h"

typedef enum
{
    /* Suppose it is Sun 7 April 2019 and the time is
    07:09:01 (hh:mm:ss) in the morning. A log message
    "\nThis Is Some Weird Log_message\n\n" has been requested to be
    written into the log with the logging level "trace".
    Below is listed each macro type along with the
    value it would expand to. */
    _FM_NO_MACRO = -1,
    _FM_YEAR = 1, /* "2019" */
    _FM_MONTH, /* "04" */
    _FM_MDAY, /* "07" */
    _FM_HOUR, /* "07" */
    _FM_MIN, /* "08" */
    _FM_SEC, /* "01" */
    _FM_MNAME_S_F, /* "Apr" (short form -> S, first capitalized -> F) */
    _FM_MNAME_S_A, /* "APR" (all capitalized -> A) */
    _FM_MNAME_L_F, /* "April" (long form -> L) */
    _FM_MNAME_L_A, /* APRIL */
    _FM_WDAY_S_F, /* "Sun" */
    _FM_WDAY_S_A, /* "SUN" */
    _FM_WDAY_L_F, /* "Sunday" */
    _FM_WDAY_L_A, /* "SUNDAY" */
    _FM_LVL_N, /* "trace" */
    _FM_LVL_F, /* "Trace" */
    _FM_LVL_A, /* "TRACE" */
    _FM_MSG /* "\nThis Is Some Weird Log_message\n\n" */
} _FM_ID;
/* Because the valid macros values start from 1 (above)
the last macro in the list gives the number of
valid format macros. */
#define _FM_COUNT _FM_MSG

/* Every format macro must begin with this character.
This character CAN be used normally, however -
it is only interpreted to be the macro beginning
when it is followed by a valid macro. */
#define _FM_BEGIN_INDIC '%'
/* In a valid macro, this has to come right after
_FM_BEGIN_INDIC. */
#define _FM_LEFT_DELIM '('
/* In a valid macro, this ends the macro sequence
and must be preceded by the macro body
(see below). */
#define _FM_RIGHT_DELIM ')'

typedef struct
{
    char*       str;
    size_t      max_len;
    _FM_HANDLER handler;
} _fm_info_t;

const _fm_info_t _FM_TABLE[_FM_COUNT];

/* The body of each macro. */
#define _FM_YEAR_S "year"
#define _FM_YEAR_MAX_LEN 4
#define _FM_MONTH_S "month"
#define _FM_MONTH_MAX_LEN 2
#define _FM_MDAY_S "mday"
#define _FM_MDAY_MAX_LEN 2
#define _FM_HOUR_S "hour"
#define _FM_HOUR_MAX_LEN 2
#define _FM_MIN_S "min"
#define _FM_MIN_MAX_LEN 2
#define _FM_SEC_S "sec"
#define _FM_SEC_MAX_LEN 2
#define _FM_MNAME_S_F_S "Mname_s"
#define _FM_MNAME_S_A_S "MNAME_S"
#define _FM_MNAME_S_MAX_LEN 3
#define _FM_MNAME_L_F_S "Mname_l"
#define _FM_MNAME_L_A_S "MNAME_L"
#define _FM_MNAME_L_MAX_LEN 9 /* strlen("SEPTEMBER") */
#define _FM_WDAY_S_F_S "Wday_s"
#define _FM_WDAY_S_A_S "WDAY_S"
#define _FM_WDAY_S_MAX_LEN 3
#define _FM_WDAY_L_F_S "Wday_l"
#define _FM_WDAY_L_A_S "WDAY_L"
#define _FM_WDAY_L_MAX_LEN 9 /*strlen("WEDNESDAY")*/
#define _FM_LVL_N_S "lvl"
#define _FM_LVL_F_S "Lvl"
#define _FM_LVL_A_S "LVL"
#define _FM_LVL_MAX_LEN 8 /* strlen("CRITICAL") */
#define _FM_MSG_S "MSG"
#define _FM_MSG_MAX_LEN _MAX_MSG_SIZE

/* The maximum length of a format macro
in the unexpanded form. */
#define _MAX_FM_S_LEN 16

#endif /* FORMAT_MACRO_H */
