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

void __um_mname_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_mname_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_mname_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_mname_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_mname_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_mname_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_wday_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_wday_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_wday_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_wday_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_wday_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_wday_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __um_lvl_n_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __);

void __um_lvl_f_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __);

void __um_lvl_a_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __);

void __um_msg_handler(thandler_t* _, char* dest, LOG_LEVEL __, char* message);

#endif // USER_MACRO_HANDLERS_H
