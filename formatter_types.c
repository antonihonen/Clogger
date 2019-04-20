/*
 * File: formatter_types.c
 * Project: logger
 * Created: 2019-04-20
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 */

#include "formatter_types.h"

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

const char* __USER_MACROS[__UM_COUNT] =
{ __UM_YEAR_S, __UM_MONTH_S, __UM_MDAY_S,
__UM_HOUR_S, __UM_MIN_S, __UM_SEC_S,
__UM_MNAME_S_N_S, __UM_MNAME_S_F_S, __UM_MNAME_S_A_S,
__UM_MNAME_L_N_S, __UM_MNAME_L_F_S, __UM_MNAME_L_A_S,
__UM_WDAY_S_N_S, __UM_WDAY_S_F_S, __UM_WDAY_S_A_S,
__UM_WDAY_L_N_S, __UM_WDAY_L_F_S, __UM_WDAY_L_A_S,
__UM_LVL_N_S, __UM_LVL_F_S, __UM_LVL_A_S, __UM_MSG_S };

void(*__UM_HANDLERS[50])(thandler_t*, char*, LOG_LEVEL, char*) =
{ __um_year_handler, __um_month_handler, __um_mday_handler,
__um_hour_handler, __um_min_handler, __um_sec_handler,
__um_mname_s_n_handler, __um_mname_s_f_handler, __um_mname_s_a_handler,
__um_mname_l_n_handler, __um_mname_l_f_handler, __um_mname_l_a_handler,
__um_wday_s_n_handler, __um_wday_s_f_handler, __um_wday_s_a_handler,
__um_wday_l_n_handler, __um_wday_l_f_handler, __um_wday_l_a_handler,
__um_lvl_a_handler, __um_lvl_f_handler, __um_lvl_a_handler, __um_msg_handler
};
