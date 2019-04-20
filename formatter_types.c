/*
 * File: formatter_types.c
 * Project: logger
 * Created: 2019-04-20
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 */

#include "formatter_types.h"

const char* __USER_MACROS[__UM_COUNT] =
{ __UM_YEAR_S, __UM_MONTH_S, __UM_MDAY_S,
__UM_HOUR_S, __UM_MIN_S, __UM_SEC_S,
__UM_MNAME_S_N_S, __UM_MNAME_S_F_S, __UM_MNAME_S_A_S,
__UM_MNAME_L_N_S, __UM_MNAME_L_F_S, __UM_MNAME_L_A_S,
__UM_WDAY_S_N_S, __UM_WDAY_S_F_S, __UM_WDAY_S_A_S,
__UM_WDAY_L_N_S, __UM_WDAY_L_F_S, __UM_WDAY_L_A_S,
__UM_LVL_N_S, __UM_LVL_N_S, __UM_LVL_A_S, __UM_MSG_S };

void(*__UM_HANDLERS[50])(thandler_t*, char*, LOG_LEVEL, char*) =
{ __um_year_handler, __um_month_handler, __um_mday_handler,
__um_hour_handler, __um_min_handler, __um_sec_handler };
