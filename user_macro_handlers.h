/*
 * File: user_macro_handlers.h
 * Project: logger
 * Created: 2019-04-20
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines functions that are responsible
 * for expanding a certain user macro each.
 */

#ifndef USER_MACRO_HANDLERS_H
#define USER_MACRO_HANDLERS_H

#include "time_handler.h"
#include "types.h"
#include <assert.h>
#include <string.h>

void __um_year_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_month_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_mday_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_hour_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_min_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_sec_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

#endif // USER_MACRO_HANDLERS_H
