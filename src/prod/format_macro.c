/*
 * File: format_macro.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "format_macro.h"
#include "format_macro_handlers.h"

const __fm_info_t __FM_TABLE[__FM_COUNT] =
{
	{__FM_YEAR_S, __FM_YEAR_MAX_LEN, __fm_year_handler},
	{__FM_MONTH_S, __FM_MONTH_MAX_LEN, __fm_month_handler},
	{__FM_MDAY_S, __FM_MDAY_MAX_LEN, __fm_mday_handler},
	{__FM_HOUR_S, __FM_HOUR_MAX_LEN, __fm_hour_handler},
	{__FM_MIN_S, __FM_MIN_MAX_LEN, __fm_min_handler },
	{__FM_SEC_S, __FM_SEC_MAX_LEN, __fm_sec_handler},
	{__FM_MNAME_S_F_S, __FM_MNAME_S_MAX_LEN, __fm_mname_s_f_handler},
	{__FM_MNAME_S_A_S, __FM_MNAME_S_MAX_LEN, __fm_mname_s_a_handler},
	{__FM_MNAME_L_F_S, __FM_MNAME_L_MAX_LEN, __fm_mname_l_f_handler},
	{__FM_MNAME_L_A_S, __FM_MNAME_L_MAX_LEN, __fm_mname_l_a_handler},
	{__FM_WDAY_S_F_S, __FM_WDAY_S_MAX_LEN, __fm_wday_s_f_handler},
	{__FM_WDAY_S_A_S, __FM_WDAY_S_MAX_LEN, __fm_wday_s_a_handler},
	{__FM_WDAY_L_F_S, __FM_WDAY_L_MAX_LEN, __fm_wday_l_f_handler},
	{__FM_WDAY_L_A_S, __FM_WDAY_L_MAX_LEN, __fm_wday_l_a_handler},
	{__FM_LVL_N_S, __FM_LVL_MAX_LEN, __fm_lvl_n_handler},
	{__FM_LVL_F_S, __FM_LVL_MAX_LEN, __fm_lvl_f_handler},
	{__FM_LVL_A_S, __FM_LVL_MAX_LEN, __fm_lvl_a_handler},
	{__FM_MSG_S, __FM_MSG_MAX_LEN, __fm_msg_handler}
};
