/*
 * File: log_macros.h
 * Project: logger
 * Created: 2019-04-15
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file contains macros used in the project.
 */

#ifndef LOG_MACROS_H
#define LOG_MACROS_H

/* Default values for log_t struct members. */
#define LOG_DEF_BUFFER_POLICY FULL_BUFFERING
#define LOG_DEF_BUFFER_SIZE 0
#define LOG_DEF_FILE_POLICY ROTATE
#define LOG_DEF_THRESHOLD L_TRACE
#define LOG_MAX_DIR_SIZE 512
#define LOG_DEF_DIR "logs"
#define LOG_MAX_FILENAME_SIZE 256
#define LOG_DEF_FILENAME_FORMAT "%(_YYYY_)_%(_DD_)_%(_MM_)_%(_FILE_I_)"
#define LOG_DEF_MAX_FILE_SIZE 1048576UL // 2^20 bytes
#define LOG_MAX_FILE_EXT_SIZE 16
#define LOG_DEF_FILE_EXT "log"
#define LOG_MAX_MSG_SIZE 256
#define LOG_MAX_FORMAT_SIZE 128
#define LOG_DEF_ENTRY_FORMAT "%(_YYYY_)-%(_DD_)-%(_MM_) %(_%hh_):%(_mm_):%(_ss_) %(_LVL_) %(_MSG_)\n"
#define LOG_DEF_ENABLE_STATE false

#define LOG_NO_FILE_NAME ""
#define LOG_NO_DIR ""
#define LOG_NO_FILE_EXT ""

#define LOG_MON_L "Monday"
#define LOG_MON_L_C "MONDAY"
#define LOG_MON_S "Mon"
#define LOG_MON_S_C "MON"

#define LOG_TUE_L "Tuesday"
#define LOG_TUE_L_C "TUESDAY"
#define LOG_TUE_S "Tue"
#define LOG_TUE_S_C "TUE"

#define LOG_WED_L "Wednesday"
#define LOG_WED_L_C "WEDNESDAY"
#define LOG_WED_S "Wed"
#define LOG_WED_S_C "WED"

#define LOG_THU_L "Thursday"
#define LOG_THU_L_C "THURSDAY"
#define LOG_THU_S "Thu"
#define LOG_THU_S_C "THU"

#define LOG_FRI_L "Friday"
#define LOG_FRI_L_C "FRIDAY"
#define LOG_FRI_S "Fri"
#define LOG_FRI_S_C "FRI"

#define LOG_SAT_L "Saturday"
#define LOG_SAT_L_C "SATURDAY"
#define LOG_SAT_S "Sat"
#define LOG_SAT_S_C "SAT"

#define LOG_SUN_L "Sunday"
#define LOG_SUN_L_C "SUNDAY"
#define LOG_SUN_S "Sun"
#define LOG_SUN_S_C "SUN"

#define LOG_DOW_L_FIELD_SIZE (sizeof(LOG_WED_L) - 1)
#define LOG_DOW_S_FIELD_SIZE (sizeof(LOG_WED_S) - 1)

#define LOG_DEBUG_STR "Debug"
#define LOG_DEBUG_STR_C "DEBUG"
#define LOG_INFO_STR "Info"
#define LOG_INFO_STR_C "INFO"
#define LOG_WARNING_STR "Warning"
#define LOG_WARNING_STR_C "WARNING"
#define LOG_ERROR_STR "Error"
#define LOG_ERROR_STR_C "ERROR"
#define LOG_CRITICAL_STR "Critical"
#define LOG_CRITICAL_STR_C "CRITICAL"
#define LOG_LVL_FIELD_SIZE (sizeof(LOG_CRITICAL_STR) - 1);

#define LOG_NEWLINE_CHAR "\n"

#define LOG_DEF_FORMAT "%(_MSG_)"

#endif // LOG_MACROS_H
