/*
 * File: format_macro_handlers.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "format_macro_handlers.h"
#include "macros.h"
#include <assert.h>
#include <string.h>

/* Returns true if the time handler is in a state that is legal,
i.e. thandler_fetch_ltime() has been called for it.
This must be checked because otherwise attempting to get
any date info from it will cause an assertion to fail. */
static bool
__is_thandler_state_legal(thandler_t* thandler)
{
	bool is_th_state_legal = false;
	thandler_is_legal_state(thandler, &is_th_state_legal);
	return is_th_state_legal;
}

void
__fm_year_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char year_str[__FM_YEAR_EXP_SIZE];
	thandler_get_year(thandler, year_str);
	strcpy(dest, year_str);
}

void
__fm_month_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char month_str[__FM_MONTH_EXP_SIZE];
	thandler_get_month(thandler, month_str);
	strcpy(dest, month_str);
}

void
__fm_mday_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char mday_str[__FM_MDAY_EXP_SIZE];
	thandler_get_mday(thandler, mday_str);
	strcpy(dest, mday_str);
}

void
__fm_hour_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char hour_str[__FM_HOUR_EXP_SIZE];
	thandler_get_hours(thandler, hour_str);
	strcpy(dest, hour_str);
}

void
__fm_min_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char min_str[__FM_MIN_EXP_SIZE];
	thandler_get_mins(thandler, min_str);
	strcpy(dest, min_str);
}

void
__fm_sec_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char sec_str[__FM_SEC_EXP_SIZE];
	thandler_get_secs(thandler, sec_str);
	strcpy(dest, sec_str);
}

void
__fm_mname_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char mname_str[__MAX_FM_MNAME_L_EXP_SIZE];
	thandler_get_mname(thandler, mname_str, __MN_SHORT_SMALL);
	strcpy(dest, mname_str);
}

void
__fm_mname_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char mname_str[__MAX_FM_MNAME_L_EXP_SIZE];
	thandler_get_mname(thandler, mname_str, __MN_SHORT_FIRST_CAP);
	strcpy(dest, mname_str);
}

void
__fm_mname_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char mname_str[__MAX_FM_MNAME_L_EXP_SIZE];
	thandler_get_mname(thandler, mname_str, __MN_SHORT_ALL_CAPS);
	strcpy(dest, mname_str);
}

void
__fm_mname_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char mname_str[__MAX_FM_MNAME_L_EXP_SIZE];
	thandler_get_mname(thandler, mname_str, __MN_LONG_SMALL);
	strcpy(dest, mname_str);
}

void
__fm_mname_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char mname_str[__MAX_FM_MNAME_L_EXP_SIZE];
	thandler_get_mname(thandler, mname_str, __MN_LONG_FIRST_CAP);
	strcpy(dest, mname_str);
}

void
__fm_mname_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char mname_str[__MAX_FM_MNAME_L_EXP_SIZE];
	thandler_get_mname(thandler, mname_str, __MN_LONG_ALL_CAPS);
	strcpy(dest, mname_str);
}

void
__fm_wday_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char wday_str[__MAX_FM_WDAY_L_EXP_SIZE];
	thandler_get_wday(thandler, wday_str, __WD_SHORT_SMALL);
	strcpy(dest, wday_str);
}

void
__fm_wday_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char wday_str[__MAX_FM_WDAY_L_EXP_SIZE];
	thandler_get_wday(thandler, wday_str, __WD_SHORT_FIRST_CAP);
	strcpy(dest, wday_str);
}

void
__fm_wday_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char wday_str[__MAX_FM_WDAY_L_EXP_SIZE];
	thandler_get_wday(thandler, wday_str, __WD_SHORT_ALL_CAPS);
	strcpy(dest, wday_str);
}

void
__fm_wday_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char wday_str[__MAX_FM_WDAY_L_EXP_SIZE];
	thandler_get_wday(thandler, wday_str, __WD_LONG_SMALL);
	strcpy(dest, wday_str);
}

void
__fm_wday_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char wday_str[__MAX_FM_WDAY_L_EXP_SIZE];
	thandler_get_wday(thandler, wday_str, __WD_LONG_FIRST_CAP);
	strcpy(dest, wday_str);
}

void
__fm_wday_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler); assert(dest);
	assert(__is_thandler_state_legal(thandler));

	char wday_str[__MAX_FM_WDAY_L_EXP_SIZE];
	thandler_get_wday(thandler, wday_str, __WD_LONG_ALL_CAPS);
	strcpy(dest, wday_str);
}

void
__fm_lvl_n_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __)
{
	assert(dest);
	
	// TODO: Implement.
}

void
__fm_lvl_f_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __)
{
	assert(dest);

	// TODO: Implement.
}

void
__fm_lvl_a_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __)
{
	assert(dest);

	strcpy(dest, __LOG_LEVEL_STRS[level]);
}

void
__fm_msg_handler(thandler_t* _, char* dest, LOG_LEVEL __, char* msg)
{
	assert(dest); assert(msg);

	strcpy(dest, msg);
}
