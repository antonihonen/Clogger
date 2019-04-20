/*
 * File: user_macro_handlers.c
 * Project: logger
 * Created: 2019-04-20
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines functions that are responsible
 * for expanding a certain user macro each.
 */

#include "user_macro_handlers.h"
#include "types.h"

void __um_year_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char year_str[5];
	thandler_get_year(thandler, year_str);
	strcpy(dest, year_str);
}

void __um_month_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char month_str[3];
	thandler_get_month(thandler, month_str);
	strcpy(dest, month_str);
}

void __um_mday_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char mday_str[3];
	thandler_get_mday(thandler, mday_str);
	strcpy(dest, mday_str);
}

void __um_hour_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char hour_str[3];
	thandler_get_hours(thandler, hour_str);
	strcpy(dest, hour_str);
}

void __um_min_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char min_str[3];
	thandler_get_mins(thandler, min_str);
	strcpy(dest, min_str);
}

void __um_sec_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char sec_str[3];
	thandler_get_secs(thandler, sec_str);
	strcpy(dest, sec_str);
}

void __um_mname_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char mname_str[4];
	thandler_get_mname(thandler, mname_str, __MN_SHORT_SMALL);
	strcpy(dest, mname_str);
}

void __um_mname_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char mname_str[4];
	thandler_get_mname(thandler, mname_str, __MN_SHORT_FIRST_CAP);
	strcpy(dest, mname_str);
}

void __um_mname_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char mname_str[4];
	thandler_get_mname(thandler, mname_str, __MN_SHORT_ALL_CAPS);
	strcpy(dest, mname_str);
}

void __um_mname_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char mname_str[16];
	thandler_get_mname(thandler, mname_str, __MN_LONG_SMALL);
	strcpy(dest, mname_str);
}

void __um_mname_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char mname_str[16];
	thandler_get_mname(thandler, mname_str, __MN_LONG_FIRST_CAP);
	strcpy(dest, mname_str);
}

void __um_mname_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char mname_str[16];
	thandler_get_mname(thandler, mname_str, __MN_LONG_ALL_CAPS);
	strcpy(dest, mname_str);
}

void __um_wday_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char wday_str[16];
	thandler_get_wday(thandler, wday_str, __WD_SHORT_SMALL);
	strcpy(dest, wday_str);
}

void __um_wday_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char wday_str[16];
	thandler_get_wday(thandler, wday_str, __WD_SHORT_FIRST_CAP);
	strcpy(dest, wday_str);
}

void __um_wday_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char wday_str[16];
	thandler_get_wday(thandler, wday_str, __WD_SHORT_ALL_CAPS);
	strcpy(dest, wday_str);
}

void __um_wday_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char wday_str[16];
	thandler_get_wday(thandler, wday_str, __WD_LONG_SMALL);
	strcpy(dest, wday_str);
}

void __um_wday_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char wday_str[16];
	thandler_get_wday(thandler, wday_str, __WD_LONG_FIRST_CAP);
	strcpy(dest, wday_str);
}

void __um_wday_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __)
{
	assert(thandler && dest);

	char wday_str[16];
	thandler_get_wday(thandler, wday_str, __WD_LONG_ALL_CAPS);
	strcpy(dest, wday_str);
}

void __um_lvl_n_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __)
{
	assert(dest);
	
	// TODO: Implement.
}

void __um_lvl_f_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __)
{
	// TODO: Implement.

	assert(dest);
}

void __um_lvl_a_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __)
{
	assert(dest);

	strcpy(dest, LOG_LEVEL_STRS[level]);
}

void __um_msg_handler(thandler_t* _, char* dest, LOG_LEVEL __, char* message)
{
	assert(dest);

	strcpy(dest, message);
}
