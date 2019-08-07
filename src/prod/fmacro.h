/*
 * File: fmacro.h
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * This module contains items related to format
 * macros. Format macros can be used
 * to format file names and log entries. A valid
 * format macro is a sequence of characters that
 * conforms to the form "<1><2><3><4>",
 * where
 *
 * 1 = LG__FM_BEGIN_INDIC (begin indicator)
 * 2 = LG__FM_LEFT_DELIM (left delimiter)
 * 3 = a valid macro body (one of the values in the LG_FORMAT_MACROS array)
 * 4 = LG__FM_RIGHT_DELIM (right delimiter)
 * 
 * All of the values presented above have been defined in this module.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LG_FORMAT_MACRO_H
#define LG_FORMAT_MACRO_H

#include "macros.h"
#include <stddef.h>

typedef enum
{
    /* Suppose it is Sun 7 April 2019 and the time is
    07:09:01 (hh:mm:ss) in the morning. A log message
    "\nThis Is Some Weird Log_message\n\n" has been requested to be
    written into the log with the logging level "trace".
    Below is listed each macro type along with the
    value it would expand to. */
    LG_FM_NO_MACRO = -1,
    LG_FM_YEAR = 1, /* "2019" */
    LG_FM_MONTH, /* "04" */
    LG_FM_MDAY, /* "07" */
    LG_FM_HOUR, /* "07" */
    LG_FM_MIN, /* "08" */
    LG_FM_SEC, /* "01" */
    LG_FM_MNAME_S_F, /* "Apr" (short form -> S, first capitalized -> F) */
    LG_FM_MNAME_S_A, /* "APR" (all capitalized -> A) */
    LG_FM_MNAME_L_F, /* "April" (long form -> L) */
    LG_FM_MNAME_L_A, /* APRIL */
    LG_FM_WDAY_S_F, /* "Sun" */
    LG_FM_WDAY_S_A, /* "SUN" */
    LG_FM_WDAY_L_F, /* "Sunday" */
    LG_FM_WDAY_L_A, /* "SUNDAY" */
    LG_FM_LVL_N, /* "trace" */
    LG_FM_LVL_F, /* "Trace" */
    LG_FM_LVL_A, /* "TRACE" */
    LG_FM_MSG /* "\nThis Is Some Weird Log_message\n\n" */
} LG_FM_ID;
/* Because the valid macros values start from 1 (above)
the last macro in the list gives the number of
valid format macros. */
#define LG_FM_COUNT LG_FM_MSG

/* Every format macro must begin with this character.
This character CAN be used normally, however -
it is only interpreted to be the macro beginning
when it is followed by a valid macro. */
#define LG_FM_BEGIN_INDIC '%'
/* In a valid macro, this has to come right after
_FM_BEGIN_INDIC. */
#define LG_FM_LEFT_DELIM '('
/* In a valid macro, this ends the macro sequence
and must be preceded by the macro body
(see below). */
#define LG_FM_RIGHT_DELIM ')'

typedef struct
{
    char*       str;
    size_t      len;
    LG_FM_ID    id;
} fm_info_t;

const fm_info_t _FM_TABLE[LG_FM_COUNT];

/* The body of each macro. */
#define LG_FM_YEAR_S "year"
#define LG_FM_YEAR_MAX_LEN 4
#define LG_FM_MONTH_S "month"
#define LG_FM_MONTH_MAX_LEN 2
#define LG_FM_MDAY_S "mday"
#define LG_FM_MDAY_MAX_LEN 2
#define LG_FM_HOUR_S "hour"
#define LG_FM_HOUR_MAX_LEN 2
#define LG_FM_MIN_S "min"
#define LG_FM_MIN_MAX_LEN 2
#define LG_FM_SEC_S "sec"
#define LG_FM_SEC_MAX_LEN 2
#define LG_FM_MNAME_S_F_S "Mname_s"
#define LG_FM_MNAME_S_A_S "MNAME_S"
#define LG_FM_MNAME_S_MAX_LEN 3
#define LG_FM_MNAME_L_F_S "Mname_l"
#define LG_FM_MNAME_L_A_S "MNAME_L"
#define LG_FM_MNAME_L_MAX_LEN 9 /* strlen("SEPTEMBER") */
#define LG_FM_WDAY_S_F_S "Wday_s"
#define LG_FM_WDAY_S_A_S "WDAY_S"
#define LG_FM_WDAY_S_MAX_LEN 3
#define LG_FM_WDAY_L_F_S "Wday_l"
#define LG_FM_WDAY_L_A_S "WDAY_L"
#define LG_FM_WDAY_L_MAX_LEN 9 /*strlen("WEDNESDAY")*/
#define LG_FM_LVL_N_S "lvl"
#define LG_FM_LVL_F_S "Lvl"
#define LG_FM_LVL_A_S "LVL"
#define LG_FM_LVL_MAX_LEN 9 /* strlen("EMERGENCY") */
#define LG_FM_MSG_S "MSG"
#define LG_FM_MSG_MAX_LEN LG_MAX_MSG_SIZE

/* The maximum length of a format macro
in the unexpanded form. */
#define LG_MAX_FM_S_LEN 16

#endif /* LG_FORMAT_MACRO_H */
