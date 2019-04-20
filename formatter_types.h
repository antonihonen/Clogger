/*
 * File: formatter_types.h
 * Project: logger
 * Created: 2019-04-20
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines macros, enums and constants used by the
 * formatter module. Private 
 */

#ifndef FORMATTER_TYPES_H
#define FORMATTER_TYPES_H

#include "user_macro_handlers.h"
#include "types.h"

/* User macro-related types. */

typedef enum
{
	__UM_NO_MACRO = -1,
	__UM_YEAR = 1,
	__UM_MONTH,
	__UM_DAY,
	__UM_HOUR,
	__UM_MIN,
	__UM_SEC,
	__UM_MNAME_S_N,
	__UM_MNAME_S_F,
	__UM_MNAME_S_A,
	__UM_MNAME_L_N,
	__UM_MNAME_L_F,
	__UM_MNAME_L_A,
	__UM_WDAY_S_N,
	__UM_WDAY_S_F,
	__UM_WDAY_S_A,
	__UM_WDAY_L_N,
	__UM_WDAY_L_F,
	__UM_WDAY_L_A,
	__UM_LVL_N,
	__UM_LVL_F,
	__UM_LVL_C,
	__UM_MSG
} __UM_ID;
#define __UM_COUNT __UM_MSG

#define __UM_BEGIN_INDIC '%'
#define __UM_LEFT_DELIM '('
#define __UM_RIGHT_DELIM ')'
#define __UM_YEAR_S "year"
#define __UM_MONTH_S "month"
#define __UM_MDAY_S "mday"
#define __UM_HOUR_S "hour"
#define __UM_MIN_S "min"
#define __UM_SEC_S "sec"
#define __UM_MNAME_S_N_S "mname_s"
#define __UM_MNAME_S_F_S "Mname_s"
#define __UM_MNAME_S_A_S "MNAME_S"
#define __UM_MNAME_L_N_S "mname_l"
#define __UM_MNAME_L_F_S "Mname_l"
#define __UM_MNAME_L_A_S "MNAME_L"
#define __UM_WDAY_S_N_S "wday_s"
#define __UM_WDAY_S_F_S "Wday_s"
#define __UM_WDAY_S_A_S "WDAY_S"
#define __UM_WDAY_L_N_S "wday_l"
#define __UM_WDAY_L_F_S "Wday_l"
#define __UM_WDAY_L_A_S "WDAY_L"
#define __UM_LVL_N_S "lvl"
#define __UM_LVL_F_S "Lvl"
#define __UM_LVL_A_S "LVL"
#define __UM_MSG_S "MSG"

#define __MAX_UM_S_LEN 16 // superfluous

const char* __USER_MACROS[__UM_COUNT];

void (*__UM_HANDLERS[__UM_COUNT])(thandler_t*, char*, LOG_LEVEL, char*);

#endif // FORMATTER_TYPES_H
