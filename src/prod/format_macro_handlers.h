/*
 * File: format_macro_handlers.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains the format macro handlers.
 * Each handler is responsible for expanding a
 * certain macro.
 *
 * The definition of each macro can be found in format_macro.h.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef FORMAT_MACRO_HANDLERS_H
#define FORMAT_MACRO_HANDLERS_H

#include "log_level.h"
#include "time_handler.h"

/* In the functions below,
-thandler is a pointer to the thandler_t that contains the time
 and date information that time-related macros are going to use.
 thandler_fetch_ltime() must have been called for the thandler
 object prior to the call to the handler.
-dest is a pointer that indicates where the expanded macro will
 be written.
-level indicates the logging level of the log write request if any
 (macros making use of it must only be used when formatting log entries)
-msg is the log message given by the user if any
 (macros making use of it must only be used when formatting log entries)
*/

 /* Handler for __FM_YEAR format macro. */
void
__fm_year_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MONTH format macro. */
void
__fm_month_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MDAY format macro. */
void
__fm_mday_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_HOUR format macro. */
void
__fm_hour_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MIN format macro. */
void
__fm_min_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_SEC format macro. */
void
__fm_sec_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MNAME_S_N format macro. */
void
__fm_mname_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MNAME_S_F format macro. */
void
__fm_mname_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MNAME_S_A format macro. */
void
__fm_mname_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MNAME_L_N format macro. */
void
__fm_mname_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MNAME_L_F format macro. */
void
__fm_mname_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_MNAME_L_A format macro. */
void
__fm_mname_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_WDAY_S_N format macro. */
void
__fm_wday_s_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_WDAY_S_F format macro. */
void
__fm_wday_s_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_WDAY_S_A format macro. */
void
__fm_wday_s_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_WDAY_L_N format macro. */
void
__fm_wday_l_n_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_WDAY_L_F format macro. */
void
__fm_wday_l_f_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_WDAY_L_A format macro. */
void
__fm_wday_l_a_handler(thandler_t* thandler, char* dest, LOG_LEVEL _, char* __, size_t* exp_macro_len);

/* Handler for __FM_LVL_N format macro. */
void
__fm_lvl_n_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __, size_t* exp_macro_len);

/* Handler for __LVL_F format macro. */
void
__fm_lvl_f_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __, size_t* exp_macro_len);

/* Handler for __FM_LVL_A format macro. */
void
__fm_lvl_a_handler(thandler_t* _, char* dest, LOG_LEVEL level, char* __, size_t* exp_macro_len);

/* Handler for __FM_MSG format macro. */
void
__fm_msg_handler(thandler_t* _, char* dest, LOG_LEVEL __, char* msg, size_t* exp_macro_len);

#endif /* FORMAT_MACRO_HANDLERS_H */
