/*
 * File: fmacro.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "fmacro.h"

const fm_info_t _FM_TABLE[LG_FM_COUNT] =
{
    { LG_FM_YEAR_S, LG_FM_YEAR_MAX_LEN },
    { LG_FM_MONTH_S, LG_FM_MONTH_MAX_LEN },
    { LG_FM_MDAY_S, LG_FM_MDAY_MAX_LEN },
    { LG_FM_HOUR_S, LG_FM_HOUR_MAX_LEN },
    { LG_FM_MIN_S, LG_FM_MIN_MAX_LEN },
    { LG_FM_SEC_S, LG_FM_SEC_MAX_LEN },
    { LG_FM_MNAME_S_F_S, LG_FM_MNAME_S_MAX_LEN },
    { LG_FM_MNAME_S_A_S, LG_FM_MNAME_S_MAX_LEN },
    { LG_FM_MNAME_L_F_S, LG_FM_MNAME_L_MAX_LEN },
    { LG_FM_MNAME_L_A_S, LG_FM_MNAME_L_MAX_LEN },
    { LG_FM_WDAY_S_F_S, LG_FM_WDAY_S_MAX_LEN },
    { LG_FM_WDAY_S_A_S, LG_FM_WDAY_S_MAX_LEN },
    { LG_FM_WDAY_L_F_S, LG_FM_WDAY_L_MAX_LEN },
    { LG_FM_WDAY_L_A_S, LG_FM_WDAY_L_MAX_LEN },
    { LG_FM_LVL_N_S, LG_FM_LVL_MAX_LEN },
    { LG_FM_LVL_F_S, LG_FM_LVL_MAX_LEN },
    { LG_FM_LVL_A_S, LG_FM_LVL_MAX_LEN },
    { LG_FM_MSG_S, LG_FM_MSG_MAX_LEN }
};
