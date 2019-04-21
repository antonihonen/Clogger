/*
 * File: format_macro.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 */

#include "format_macro.h"
#include "format_macro_handlers.h"

const char* __FORMAT_MACROS[__FM_COUNT] =
	{ __FM_YEAR_S, __FM_MONTH_S, __FM_MDAY_S,
	__FM_HOUR_S, __FM_MIN_S, __FM_SEC_S,
	__FM_MNAME_S_N_S, __FM_MNAME_S_F_S, __FM_MNAME_S_A_S,
	__FM_MNAME_L_N_S, __FM_MNAME_L_F_S, __FM_MNAME_L_A_S,
	__FM_WDAY_S_N_S, __FM_WDAY_S_F_S, __FM_WDAY_S_A_S,
	__FM_WDAY_L_N_S, __FM_WDAY_L_F_S, __FM_WDAY_L_A_S,
	__FM_LVL_N_S, __FM_LVL_F_S, __FM_LVL_A_S, __FM_MSG_S
	};

void(*__FM_HANDLERS[__FM_COUNT])(thandler_t*, char*, LOG_LEVEL, char*) =
	{ __fm_year_handler, __fm_month_handler, __fm_mday_handler,
	__fm_hour_handler, __fm_min_handler, __fm_sec_handler,
	__fm_mname_s_n_handler, __fm_mname_s_f_handler, __fm_mname_s_a_handler,
	__fm_mname_l_n_handler, __fm_mname_l_f_handler, __fm_mname_l_a_handler,
	__fm_wday_s_n_handler, __fm_wday_s_f_handler, __fm_wday_s_a_handler,
	__fm_wday_l_n_handler, __fm_wday_l_f_handler, __fm_wday_l_a_handler,
	__fm_lvl_a_handler, __fm_lvl_f_handler, __fm_lvl_a_handler,
	__fm_msg_handler
	};
