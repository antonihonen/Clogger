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
