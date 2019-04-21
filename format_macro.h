/*
 * File: format_macro.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains items related to format
 * macro handling. Format macros (for example "%(year)")
 * can be used to format file names or log entries.
 */

#ifndef FORMAT_MACRO_H
#define FORMAT_MACRO_H

#include "format_macro_handlers.h"
#include "types.h"

typedef enum
{
	// Suppose it is Sun 7 April 2019 and the time is
	// 07:09:01 (hh:mm:ss) in the morning. A log message
	// "this is a log message\n" has been requested to be
	// written into the log with the logging level "trace".
	// Below is listed each macro type along with the
	// value it would expand to.
	__FM_NO_MACRO = -1,
	__FM_YEAR = 1, // "2019"
	__FM_MONTH, // "04"
	__FM_MDAY, // "07"
	__FM_HOUR, // "07"
	__FM_MIN, // "08"
	__FM_SEC, // "01"
	__FM_MNAME_S_N, // "apr" (no capitals -> N)
	__FM_MNAME_S_F, // "Apr" (first capitalized -> F)
	__FM_MNAME_S_A, // "APR" (all capitalized -> A)
	__FM_MNAME_L_N, // "april"
	__FM_MNAME_L_F, // "April"
	__FM_MNAME_L_A, // APRIL
	__FM_WDAY_S_N, // "sun"
	__FM_WDAY_S_F, // "Sun"
	__FM_WDAY_S_A, // "SUN"
	__FM_WDAY_L_N, // "sunday"
	__FM_WDAY_L_F, // "Sunday"
	__FM_WDAY_L_A, // "SUNDAY"
	__FM_LVL_N, // "trace"
	__FM_LVL_F, // "Trace"
	__FM_LVL_C, // "TRACE"
	__FM_MSG // "this is a log message\n"
} __FM_ID;
// Because the valid macros values start from 1 (above)
// the last macro in the list gives the number of
// valid format macros.
#define __FM_COUNT __FM_MSG


// Every format macro must begin with this character.
// This character CAN be used normally, however -
// if it is not followed by a valid macro,
// no macro expansion will be done.
#define __FM_BEGIN_INDIC '%'
// In a valid macro, this has to come right after
// __FM_BEGIN_INDIC.
#define __FM_LEFT_DELIM '('
// In a valid macro, this ends the macro sequence
// and must be preceded by the string indicating
// the macro (see below).
#define __FM_RIGHT_DELIM ')'

// The correct spellings of each macro.
#define __FM_YEAR_S "year"
#define __FM_MONTH_S "month"
#define __FM_MDAY_S "mday"
#define __FM_HOUR_S "hour"
#define __FM_MIN_S "min"
#define __FM_SEC_S "sec"
#define __FM_MNAME_S_N_S "mname_s"
#define __FM_MNAME_S_F_S "Mname_s"
#define __FM_MNAME_S_A_S "MNAME_S"
#define __FM_MNAME_L_N_S "mname_l"
#define __FM_MNAME_L_F_S "Mname_l"
#define __FM_MNAME_L_A_S "MNAME_L"
#define __FM_WDAY_S_N_S "wday_s"
#define __FM_WDAY_S_F_S "Wday_s"
#define __FM_WDAY_S_A_S "WDAY_S"
#define __FM_WDAY_L_N_S "wday_l"
#define __FM_WDAY_L_F_S "Wday_l"
#define __FM_WDAY_L_A_S "WDAY_L"
#define __FM_LVL_N_S "lvl"
#define __FM_LVL_F_S "Lvl"
#define __FM_LVL_A_S "LVL"
#define __FM_MSG_S "MSG"

// The maximum length of a format macro
// in the unexpanded form.
#define __MAX_FM_S_LEN 16

// A list of all the valid format macros in the
// string form presented above.
const char* __FORMAT_MACROS[__FM_COUNT];

// A list of format macro handlers. Each valid macro
// is assigned a unique handler.
void (*__FM_HANDLERS[__FM_COUNT])(thandler_t*, char*, LOG_LEVEL, char*);

#endif // FORMAT_MACRO_H
