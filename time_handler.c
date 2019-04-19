/*
 * File: time_handler.c
 * Project: logger
 * Created: 2019-04-18
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file implements the time handler class defined
 * in time_handler.h.
 */

#include "time_handler.h"
#include "types.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

#define __CAP_A_ASCII_VAL 65
#define __CAP_Z_ASCII_VAL 90
#define __LOW_A_ASCII_VAL 97
#define __LOW_Z_ASCII_VAL 122
#define __ASCII_CHAR_TO_LOWER(c) \
	if (*c >= __CAP_A_ASCII_VAL && *c <= __CAP_Z_ASCII_VAL) { *c += 32; } \
	else {}
#define __ASCII_CHAR_TO_UPPER(c) \
	if (*c >= __LOW_A_ASCII_VAL && *c <= __LOW_Z_ASCII_VAL) { *c -= 32; } \
	else {}

static const char* MONTHS[12] =
	{"JANUARY", "FEBRUARY", "MARC", "APRIL", "MAY", "JUNE",
	"JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};

static const char* WEEKDAYS[7] =
	{ "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY",
	"THURSDAY", "FRIDAY", "SATURDAY" };

static void two_digit_int_to_str(int i, char* str)
{
	assert(i >= 0);
	assert(str);

	char format[4];
	if (i < 10)
	{
		strcpy(format, "0%i");
	}
	else
	{
		strcpy(format, "%i");
	}
	sprintf(str, format, i);
}

static void ascii_str_to_lower(char* str)
{
	assert(str);

	while (*str != '\0')
	{
		__ASCII_CHAR_TO_LOWER(str);
		++str;
	}
}

static void ascii_str_to_upper(char* str)
{
	assert(str);

	while (*str != '\0')
	{
		__ASCII_CHAR_TO_UPPER(str);
		++str;
	}
}

LOG_ERROR
thandler_init(thandler_t* thandler)
{
	assert(thandler);

	thandler->last_fetch_ = NULL;
	return E_NO_ERROR;
}

LOG_ERROR
thandler_close(thandler_t* thandler)
{
	assert(thandler);

	return E_NO_ERROR;
}

LOG_ERROR
thandler_fetch_ltime(thandler_t* thandler)
{
	assert(thandler);

	time_t raw_time;
	time(&raw_time);
	thandler->last_fetch_ = localtime(&raw_time);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_year(thandler_t* thandler, char* year)
{
	assert(thandler);
	assert(year);

	// The year contained by last_fetch_ is counted from 1900.
	sprintf(year, "%i", 1900L + thandler->last_fetch_->tm_year);
	return E_NO_ERROR;
}

LOG_ERROR thandler_get_month(thandler_t* thandler, char* month)
{
	assert(thandler);
	assert(month);

	// The month contained by local time is counted from 0.
	two_digit_int_to_str(thandler->last_fetch_->tm_mon + 1, month);
	return E_NO_ERROR;
}

LOG_ERROR thandler_get_mday(thandler_t* thandler, char* mday)
{
	assert(thandler);
	assert(mday);

	two_digit_int_to_str(thandler->last_fetch_->tm_mday, mday);
	return E_NO_ERROR;
}

LOG_ERROR thandler_get_hours(thandler_t* thandler, char* hours)
{
	assert(thandler);
	assert(hours);

	two_digit_int_to_str(thandler->last_fetch_->tm_hour, hours);
	return E_NO_ERROR;
}

LOG_ERROR thandler_get_mins(thandler_t* thandler, char* mins)
{
	assert(thandler);
	assert(mins);

	two_digit_int_to_str(thandler->last_fetch_->tm_min, mins);
	return E_NO_ERROR;
}

LOG_ERROR thandler_get_secs(thandler_t* thandler, char* secs)
{
	assert(thandler);
	assert(secs);

	two_digit_int_to_str(thandler->last_fetch_->tm_sec, secs);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_mname(thandler_t* thandler, char* mname, __MNAME_FORMAT format)
{
	assert(thandler);
	assert(mname);
	assert(format >= __MN_SHORT_SMALL);
	assert(format <= __MN_LONG_ALL_CAPS);

	char full_name_in_caps[10];
	strcpy(full_name_in_caps, MONTHS[thandler->last_fetch_->tm_mon]);

	if (format >= __MN_SHORT_SMALL && format <= __MN_SHORT_ALL_CAPS)
	{
		full_name_in_caps[3] = '\0';
	}

	if (format == __MN_SHORT_SMALL || format == __MN_LONG_SMALL)
	{
		ascii_str_to_lower(full_name_in_caps);
	}
	else if (format == __MN_SHORT_FIRST_CAP || format == __MN_LONG_FIRST_CAP)
	{
		ascii_str_to_lower(full_name_in_caps + 1);
	}

	sprintf(mname, "%s", full_name_in_caps);
	
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_wday(thandler_t* thandler, char* wday, __WDAY_FORMAT format)
{
	assert(thandler);
	assert(wday);
	assert(format >= __WD_SHORT_SMALL);
	assert(format <= __WD_LONG_ALL_CAPS);

	char full_name_in_caps[10];
	strcpy(full_name_in_caps, WEEKDAYS[thandler->last_fetch_->tm_wday]);

	if (format >= __WD_SHORT_SMALL && format <= __WD_SHORT_ALL_CAPS)
	{
		full_name_in_caps[3] = '\0';
	}

	if (format == __WD_SHORT_SMALL || format == __WD_LONG_SMALL)
	{
		ascii_str_to_lower(full_name_in_caps);
	}
	else if (format == __WD_SHORT_FIRST_CAP || format == __WD_LONG_FIRST_CAP)
	{
		ascii_str_to_lower(full_name_in_caps + 1);
	}

	sprintf(wday, "%s", full_name_in_caps);

	return E_NO_ERROR;
}
