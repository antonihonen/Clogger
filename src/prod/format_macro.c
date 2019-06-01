/*
 * File: format_macro.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "format_macro.h"
#include "format_macro_handlers.h"

const _fm_info_t _FM_TABLE[_FM_COUNT] =
{
    {_FM_YEAR_S, _FM_YEAR_MAX_LEN, _fm_year_handler},
    {_FM_MONTH_S, _FM_MONTH_MAX_LEN, _fm_month_handler},
    {_FM_MDAY_S, _FM_MDAY_MAX_LEN, _fm_mday_handler},
    {_FM_HOUR_S, _FM_HOUR_MAX_LEN, _fm_hour_handler},
    {_FM_MIN_S, _FM_MIN_MAX_LEN, _fm_min_handler },
    {_FM_SEC_S, _FM_SEC_MAX_LEN, _fm_sec_handler},
    {_FM_MNAME_S_F_S, _FM_MNAME_S_MAX_LEN, _fm_mname_s_f_handler},
    {_FM_MNAME_S_A_S, _FM_MNAME_S_MAX_LEN, _fm_mname_s_a_handler},
    {_FM_MNAME_L_F_S, _FM_MNAME_L_MAX_LEN, _fm_mname_l_f_handler},
    {_FM_MNAME_L_A_S, _FM_MNAME_L_MAX_LEN, _fm_mname_l_a_handler},
    {_FM_WDAY_S_F_S, _FM_WDAY_S_MAX_LEN, _fm_wday_s_f_handler},
    {_FM_WDAY_S_A_S, _FM_WDAY_S_MAX_LEN, _fm_wday_s_a_handler},
    {_FM_WDAY_L_F_S, _FM_WDAY_L_MAX_LEN, _fm_wday_l_f_handler},
    {_FM_WDAY_L_A_S, _FM_WDAY_L_MAX_LEN, _fm_wday_l_a_handler},
    {_FM_LVL_N_S, _FM_LVL_MAX_LEN, _fm_lvl_n_handler},
    {_FM_LVL_F_S, _FM_LVL_MAX_LEN, _fm_lvl_f_handler},
    {_FM_LVL_A_S, _FM_LVL_MAX_LEN, _fm_lvl_a_handler},
    {_FM_MSG_S, _FM_MSG_MAX_LEN, _fm_msg_handler}
};
