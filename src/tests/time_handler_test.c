/*
 * File: time_handler_test.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "time_handler_test.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define __YEAR_MAX_CHARS 4
#define __MNAME_MAX_CHARS 9
#define __WDAY_MAX_CHARS 9

/* Global for convenience. */
static thandler_t* t = NULL;

void test_get_year_single_pass(int tm_year, char* correct_result)
{
	char result[__YEAR_MAX_CHARS + 1];
	t->_last_fetch->tm_year = tm_year;
	thandler_get_year(t, result);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_year(void)
{
	printf("  test_get_year\n");
	test_get_year_single_pass(75, "1975");
	test_get_year_single_pass(100, "2000");
	printf("  test_get_year passed\n");
}

void test_get_month_single_pass(int tm_mon, char* correct_result)
{
	char result[3];
	t->_last_fetch->tm_mon = tm_mon;
	thandler_get_month(t, result);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_month(void)
{
	printf("  test_get_month\n");
	test_get_month_single_pass(0, "01");
	test_get_month_single_pass(8, "09");
	test_get_month_single_pass(9, "10");
	test_get_month_single_pass(11, "12");
	printf("  test_get_month passed\n");
}

void test_get_mday_single_pass(int tm_mday, char* correct_result)
{
	char result[3];
	t->_last_fetch->tm_mday = tm_mday;
	thandler_get_mday(t, result);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_mday(void)
{
	printf("  test_get_mday\n");
	test_get_mday_single_pass(1, "01");
	test_get_mday_single_pass(9, "09");
	test_get_mday_single_pass(10, "10");
	test_get_mday_single_pass(31, "31");
	printf("  test_get_mday passed\n");
}

void test_get_hours_single_pass(int tm_hour, char* correct_result)
{
	char result[3];
	t->_last_fetch->tm_hour = tm_hour;
	thandler_get_hours(t, result);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_hours(void)
{
	printf("  test_get_hours\n");
	test_get_hours_single_pass(0, "00");
	test_get_hours_single_pass(1, "01");
	test_get_hours_single_pass(9, "09");
	test_get_hours_single_pass(10, "10");
	test_get_hours_single_pass(24, "24");
	printf("  test_get_hours passed\n");
}

void test_get_minutes_single_pass(int tm_min, char* correct_result)
{
	char result[3];
	t->_last_fetch->tm_min = tm_min;
	thandler_get_mins(t, result);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_minutes(void)
{
	printf("  test_get_minutes\n");
	test_get_minutes_single_pass(0, "00");
	test_get_minutes_single_pass(1, "01");
	test_get_minutes_single_pass(9, "09");
	test_get_minutes_single_pass(10, "10");
	test_get_minutes_single_pass(24, "24");
	test_get_minutes_single_pass(33, "33");
	test_get_minutes_single_pass(49, "49");
	test_get_minutes_single_pass(51, "51");
	test_get_minutes_single_pass(60, "60");
	printf("  test_get_minutes passed\n");
}

void test_get_seconds_single_pass(int tm_sec, char* correct_result)
{
	char result[3];
	t->_last_fetch->tm_sec = tm_sec;
	thandler_get_secs(t, result);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_seconds(void)
{
	printf("  test_get_seconds\n");
	test_get_seconds_single_pass(0, "00");
	test_get_seconds_single_pass(1, "01");
	test_get_seconds_single_pass(9, "09");
	test_get_seconds_single_pass(10, "10");
	test_get_seconds_single_pass(24, "24");
	test_get_seconds_single_pass(33, "33");
	test_get_seconds_single_pass(49, "49");
	test_get_seconds_single_pass(51, "51");
	test_get_seconds_single_pass(60, "60");
	printf("  test_get_seconds passed\n");
}

void test_get_mname_single_pass(int tm_mon, __MNAME_FORMAT format,
	char* correct_result)
{
	t->_last_fetch->tm_mon = tm_mon;
	char result[__MNAME_MAX_CHARS];
	thandler_get_mname(t, result, format);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_mname(void)
{
	printf("  test_get_mname\n");

	test_get_mname_single_pass(0, __MN_SHORT_SMALL, "jan");
	test_get_mname_single_pass(0, __MN_SHORT_FIRST_CAP, "Jan");
	test_get_mname_single_pass(0, __MN_SHORT_ALL_CAPS, "JAN");
	test_get_mname_single_pass(0, __MN_LONG_SMALL, "january");
	test_get_mname_single_pass(0, __MN_LONG_FIRST_CAP, "January");
	test_get_mname_single_pass(0, __MN_LONG_ALL_CAPS, "JANUARY");

	test_get_mname_single_pass(7, __MN_SHORT_SMALL, "aug");
	test_get_mname_single_pass(7, __MN_SHORT_FIRST_CAP, "Aug");
	test_get_mname_single_pass(7, __MN_SHORT_ALL_CAPS, "AUG");
	test_get_mname_single_pass(7, __MN_LONG_SMALL, "august");
	test_get_mname_single_pass(7, __MN_LONG_FIRST_CAP, "August");
	test_get_mname_single_pass(7, __MN_LONG_ALL_CAPS, "AUGUST");

	test_get_mname_single_pass(11, __MN_SHORT_SMALL, "dec");
	test_get_mname_single_pass(11, __MN_SHORT_FIRST_CAP, "Dec");
	test_get_mname_single_pass(11, __MN_SHORT_ALL_CAPS, "DEC");
	test_get_mname_single_pass(11, __MN_LONG_SMALL, "december");
	test_get_mname_single_pass(11, __MN_LONG_FIRST_CAP, "December");
	test_get_mname_single_pass(11, __MN_LONG_ALL_CAPS, "DECEMBER");

	printf("  test_get_mname passed\n");
}

void test_get_wday_single_pass(int tm_wday, __WDAY_FORMAT format,
	char* correct_result)
{
	t->_last_fetch->tm_wday = tm_wday;
	char result[__WDAY_MAX_CHARS];
	thandler_get_wday(t, result, format);
	assert(strcmp(result, correct_result) == 0);
}

void test_get_wday(void)
{
	printf("  test_get_wday\n");

	test_get_wday_single_pass(0, __WD_SHORT_SMALL, "sun");
	test_get_wday_single_pass(0, __WD_SHORT_FIRST_CAP, "Sun");
	test_get_wday_single_pass(0, __WD_SHORT_ALL_CAPS, "SUN");
	test_get_wday_single_pass(0, __WD_LONG_SMALL, "sunday");
	test_get_wday_single_pass(0, __WD_LONG_FIRST_CAP, "Sunday");
	test_get_wday_single_pass(0, __WD_LONG_ALL_CAPS, "SUNDAY");

	test_get_wday_single_pass(1, __WD_SHORT_SMALL, "mon");
	test_get_wday_single_pass(1, __WD_SHORT_FIRST_CAP, "Mon");
	test_get_wday_single_pass(1, __WD_SHORT_ALL_CAPS, "MON");
	test_get_wday_single_pass(1, __WD_LONG_SMALL, "monday");
	test_get_wday_single_pass(1, __WD_LONG_FIRST_CAP, "Monday");
	test_get_wday_single_pass(1, __WD_LONG_ALL_CAPS, "MONDAY");

	test_get_wday_single_pass(6, __WD_SHORT_SMALL, "sat");
	test_get_wday_single_pass(6, __WD_SHORT_FIRST_CAP, "Sat");
	test_get_wday_single_pass(6, __WD_SHORT_ALL_CAPS, "SAT");
	test_get_wday_single_pass(6, __WD_LONG_SMALL, "saturday");
	test_get_wday_single_pass(6, __WD_LONG_FIRST_CAP, "Saturday");
	test_get_wday_single_pass(6, __WD_LONG_ALL_CAPS, "SATURDAY");

	printf("  test_get_wday passed\n");
}

void run_time_handler_tests(char* test_set_title)
{
	printf(test_set_title);
	t = malloc(sizeof(thandler_t));
	thandler_init(t);
	thandler_fetch_ltime(t);
	test_get_year();
	test_get_month();
	test_get_mday();
	test_get_hours();
	test_get_minutes();
	test_get_seconds();
	test_get_mname();
	test_get_wday();
	thandler_close(t);
	free(t);
}
