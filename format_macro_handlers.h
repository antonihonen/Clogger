/*
 * File: format_macro_handlers.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains the format macro handlers.
 * Each handler is responsible for expanding a
 * certain macro.
 */

#ifndef FORMAT_MACRO_HANDLERS_H
#define FORMAT_MACRO_HANDLERS_H

#include "log_level.h"
#include "time_handler.h"
#include <assert.h>
#include <string.h>

void __fm_year_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_month_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_mday_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_hour_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_min_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_sec_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_mname_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_mname_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_mname_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_mname_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_mname_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_mname_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_wday_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_wday_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_wday_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_wday_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_wday_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_wday_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __);

void __fm_lvl_n_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __);

void __fm_lvl_f_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __);

void __fm_lvl_a_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __);

void __fm_msg_handler(thandler_t* _, char* dest, LOG_LEVEL __, char* message);

#endif // FORMAT_MACRO_HANDLERS_H
