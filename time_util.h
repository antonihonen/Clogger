/*
 * File: time_util.h
 * Project: logger
 * Created: 2019-04-18
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines functions responsible
 * for handling time.
 */

#include "types.h"
#include <stdio.h>
#include <time.h>

LOG_ERROR get_year(char* year, struct tm* local_time);

LOG_ERROR get_month(char* month, struct tm* local_time);

LOG_ERROR get_mday(char* mday, struct tm* local_time);

LOG_ERROR get_hours(char* hours, struct tm* local_time);

LOG_ERROR get_mins(char* mins, struct tm* local_time);

LOG_ERROR get_secs(char* secs, struct tm* local_time);

LOG_ERROR get_wday_3(char* wday_3, struct tm* local_time);

LOG_ERROR get_wday_full(char* wday_full, struct tm* local_time);
