/*
 * File: time_handler.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains a time handler class
 * that can be used to fetch information about
 * the current time.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include "error.h"
#include <stdbool.h>
#include <time.h>

/* Determines whether thandler_get_wday gets the day of the week as
mon, Mon, MON, monday, Monday or MONDAY. */
typedef enum { __WD_SHORT_SMALL, __WD_SHORT_FIRST_CAP, __WD_SHORT_ALL_CAPS,
	__WD_LONG_SMALL, __WD_LONG_FIRST_CAP, __WD_LONG_ALL_CAPS } __WDAY_FORMAT;

/* Determines whether thandler_get_mname gets the month name as
jan, Jan, JAN, january, January or JANUARY. */
typedef enum { __MN_SHORT_SMALL, __MN_SHORT_FIRST_CAP, __MN_SHORT_ALL_CAPS,
	__MN_LONG_SMALL, __MN_LONG_FIRST_CAP, __MN_LONG_ALL_CAPS} __MNAME_FORMAT;

/* Defines the properties of a time handler object. */
typedef struct
{
	/* Contains the result of the last call to localtime()
	received upon the last call to th_fetch_ltime(). Note that this
	is a COPY of the struct tm returned by localtime() at the time
	it was called - this allows having multiple instances of thandler_t
	without their time fetches interfering with each other. It's important
	that the values in this struct stay the same until the user is done
	with their time fetching, so that the time values are consistent
	with each other. */
	struct tm* _ltime;
	/* For testing purposes: */
	bool _is_fetch_allowed;
} thandler_t;

thandler_t*
th_init();

void
th_close(thandler_t* th);

void
th_fetch_ltime(thandler_t* th);

extern inline bool
th_has_legal_state(thandler_t* th);

void
th_get_year(thandler_t* th, char* year);

void
th_get_month(thandler_t* th, char* month);

void
th_get_mday(thandler_t* th, char* mday);

void
th_get_hour(thandler_t* th, char* hours);

void
th_get_min(thandler_t* th, char* mins);

void
th_get_sec(thandler_t* th, char* secs);

void
th_get_mname(thandler_t* th, char* mname, __MNAME_FORMAT format);

void
th_get_wday(thandler_t* th, char* wday, __WDAY_FORMAT format);

#endif /* TIME_HANDLER_H */
