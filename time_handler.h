/*
 * File: time_handler.h
 * Project: logger
 * Created: 2019-04-18
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines a time handler that is responsible
 * for fetching information about the current time.
 */

#include "types.h"
#include <time.h>

typedef enum { __WD_SHORT_SMALL, __WD_SHORT_FIRST_CAP, __WD_SHORT_ALL_CAPS,
	__WD_LONG_SMALL, __WD_LONG_FIRST_CAP, __WD_LONG_ALL_CAPS } __WDAY_FORMAT;

typedef enum { __MN_SHORT_SMALL, __MN_SHORT_FIRST_CAP, __MN_SHORT_ALL_CAPS,
	__MN_LONG_SMALL, __MN_LONG_FIRST_CAP, __MN_LONG_ALL_CAPS} __MNAME_FORMAT;

typedef struct
{
	struct tm* last_fetch_;
} thandler_t;

LOG_ERROR
thandler_init(thandler_t* thandler);

LOG_ERROR
thandler_close(thandler_t* thandler);

LOG_ERROR
thandler_fetch_ltime(thandler_t* thandler);

LOG_ERROR
thandler_get_year(thandler_t* thandler, char* year);

LOG_ERROR
thandler_get_month(thandler_t* thandler, char* month);

LOG_ERROR
thandler_get_mday(thandler_t* thandler, char* mday);

LOG_ERROR
thandler_get_hours(thandler_t* thandler, char* hours);

LOG_ERROR
thandler_get_mins(thandler_t* thandler, char* mins);

LOG_ERROR
thandler_get_secs(thandler_t* thandler, char* secs);

LOG_ERROR
thandler_get_mname(thandler_t* thandler, char* mname, __MNAME_FORMAT format);

LOG_ERROR
thandler_get_wday(thandler_t* thandler, char* wday, __WDAY_FORMAT format);