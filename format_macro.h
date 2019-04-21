/*
 * File: format_macro.h
 * Project: logger
 * Created: 2019-04-20
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines macros, enums and constants used by the
 * formatter module. Private 
 */

#ifndef FORMAT_MACRO_H
#define FORMAT_MACRO_H

#include "format_macro_handlers.h"
#include "types.h"

/* Format macro-related types. */

typedef enum
{
	__FM_NO_MACRO = -1,
	__FM_YEAR = 1,
	__FM_MONTH,
	__FM_DAY,
	__FM_HOUR,
	__FM_MIN,
	__FM_SEC,
	__FM_MNAME_S_N,
	__FM_MNAME_S_F,
	__FM_MNAME_S_A,
	__FM_MNAME_L_N,
	__FM_MNAME_L_F,
	__FM_MNAME_L_A,
	__FM_WDAY_S_N,
	__FM_WDAY_S_F,
	__FM_WDAY_S_A,
	__FM_WDAY_L_N,
	__FM_WDAY_L_F,
	__FM_WDAY_L_A,
	__FM_LVL_N,
	__FM_LVL_F,
	__FM_LVL_C,
	__FM_MSG
} __FM_ID;
#define __FM_COUNT __FM_MSG

#define __FM_BEGIN_INDIC '%'
#define __FM_LEFT_DELIM '('
#define __FM_RIGHT_DELIM ')'
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

#define __MAX_UM_S_LEN 16 // superfluous

const char* __FORMAT_MACROS[__FM_COUNT];

void (*__FM_HANDLERS[__FM_COUNT])(thandler_t*, char*, LOG_LEVEL, char*);

#endif // FORMAT_MACRO_H
