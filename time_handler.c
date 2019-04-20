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
#include <string.h>
#include <time.h>

#define __UPP_A_ASCII_VAL 65 // uppercase A
#define __UPP_Z_ASCII_VAL 90 // uppercase Z
#define __LOW_A_ASCII_VAL 97 // lowercase a
#define __LOW_Z_ASCII_VAL 122 // lowercase z
// Converts an alphabetical ASCII character to lowercase.
#define __ASCII_CHAR_TO_LOWER(c) \
	if (*c >= __UPP_A_ASCII_VAL && *c <= __UPP_Z_ASCII_VAL) { *c += 32; } \
	else {}

// Used for easy implementation of thandler_get_mname().
static const char* const MONTHS[12] =
	{ "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
	"JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };

// Used for easy implementation of thandler_get_wday().
// Starts from Sunday because in the tm struct returned by localtime()
// tm_day value of 0 equals Sunday.
static const char* const WEEKDAYS[7] =
	{ "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY",
	"THURSDAY", "FRIDAY", "SATURDAY" };

/* Writes the value of i to str with two digits.
Zero is used as prefix for i < 10. */
static void
two_digit_int_to_str(int i, char* str)
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

/* Converts alphabetical characters in str to lowercase. */
static void
ascii_str_to_lower(char* str)
{
	assert(str);

	while (*str != '\0')
	{
		__ASCII_CHAR_TO_LOWER(str);
		++str;
	}
}

LOG_ERROR
thandler_init(thandler_t* thandler)
{
	assert(thandler);

	thandler->_last_fetch = NULL;
	thandler->_is_testing = false;
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

	if (thandler->_is_testing) { return; }
	
	time_t raw_time;
	time(&raw_time);
	thandler->_last_fetch = localtime(&raw_time);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_year(thandler_t* thandler, char* year)
{
	assert(thandler);
	assert(year);
	assert(thandler->_last_fetch);

	// The year contained by _last_fetch is counted from 1900.
	sprintf(year, "%i", 1900L + thandler->_last_fetch->tm_year);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_month(thandler_t* thandler, char* month)
{
	assert(thandler);
	assert(month);
	assert(thandler->_last_fetch);

	// The month contained by local time is counted from 0.
	two_digit_int_to_str(thandler->_last_fetch->tm_mon + 1, month);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_mday(thandler_t* thandler, char* mday)
{
	assert(thandler);
	assert(mday);
	assert(thandler->_last_fetch);

	two_digit_int_to_str(thandler->_last_fetch->tm_mday, mday);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_hours(thandler_t* thandler, char* hours)
{
	assert(thandler);
	assert(hours);
	assert(thandler->_last_fetch);

	two_digit_int_to_str(thandler->_last_fetch->tm_hour, hours);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_mins(thandler_t* thandler, char* mins)
{
	assert(thandler);
	assert(mins);
	assert(thandler->_last_fetch);

	two_digit_int_to_str(thandler->_last_fetch->tm_min, mins);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_secs(thandler_t* thandler, char* secs)
{
	assert(thandler);
	assert(secs);
	assert(thandler->_last_fetch);

	two_digit_int_to_str(thandler->_last_fetch->tm_sec, secs);
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_mname(thandler_t* thandler, char* mname, __MNAME_FORMAT format)
{
	assert(thandler);
	assert(thandler->_last_fetch);
	assert(mname);
	assert(format >= __MN_SHORT_SMALL);
	assert(format <= __MN_LONG_ALL_CAPS);

	// Allocate enough space to accommodate the longest month name.
	char full_name_in_caps[10];
	strcpy(full_name_in_caps, MONTHS[thandler->_last_fetch->tm_mon]);

	if (format >= __MN_SHORT_SMALL && format <= __MN_SHORT_ALL_CAPS)
	{
		// The format is short so cut the full name after 3 chars.
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

	// At this point full_name_in_caps may no longer be the full name
	// or in caps.
	strcpy(mname, full_name_in_caps);
	
	return E_NO_ERROR;
}

LOG_ERROR
thandler_get_wday(thandler_t* thandler, char* wday, __WDAY_FORMAT format)
{
	assert(thandler);
	assert(thandler->_last_fetch);
	assert(wday);
	assert(format >= __WD_SHORT_SMALL);
	assert(format <= __WD_LONG_ALL_CAPS);

	// Allocate enough space to accommodate the longest weekday name.
	char full_name_in_caps[10];
	strcpy(full_name_in_caps, WEEKDAYS[thandler->_last_fetch->tm_wday]);

	if (format >= __WD_SHORT_SMALL && format <= __WD_SHORT_ALL_CAPS)
	{
		// The format is short so cut the full name after 3 chars.
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
	strcpy(wday, full_name_in_caps);

	return E_NO_ERROR;
}
