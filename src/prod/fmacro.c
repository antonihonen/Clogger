/*
 * File: fmacro.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "fmacro.h"

const _fm_info_t _FM_TABLE[_FM_COUNT] =
{
    { _FM_YEAR_S, _FM_YEAR_MAX_LEN },
    { _FM_MONTH_S, _FM_MONTH_MAX_LEN },
    { _FM_MDAY_S, _FM_MDAY_MAX_LEN },
    { _FM_HOUR_S, _FM_HOUR_MAX_LEN },
    { _FM_MIN_S, _FM_MIN_MAX_LEN },
    { _FM_SEC_S, _FM_SEC_MAX_LEN },
    { _FM_MNAME_S_F_S, _FM_MNAME_S_MAX_LEN },
    { _FM_MNAME_S_A_S, _FM_MNAME_S_MAX_LEN },
    { _FM_MNAME_L_F_S, _FM_MNAME_L_MAX_LEN },
    { _FM_MNAME_L_A_S, _FM_MNAME_L_MAX_LEN },
    { _FM_WDAY_S_F_S, _FM_WDAY_S_MAX_LEN },
    { _FM_WDAY_S_A_S, _FM_WDAY_S_MAX_LEN },
    { _FM_WDAY_L_F_S, _FM_WDAY_L_MAX_LEN },
    { _FM_WDAY_L_A_S, _FM_WDAY_L_MAX_LEN },
    { _FM_LVL_N_S, _FM_LVL_MAX_LEN },
    { _FM_LVL_F_S, _FM_LVL_MAX_LEN },
    { _FM_LVL_A_S, _FM_LVL_MAX_LEN },
    { _FM_MSG_S, _FM_MSG_MAX_LEN }
};
