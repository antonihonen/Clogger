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
#define DEF_BUFFER_POLICY DONT_BUFFER
#define DEF_BUFFER_SIZE 0
#define DEF_FILE_POLICY ITERATIVE
#define DEF_THRESHOLD NOT_SET
#define MAX_DIR_SIZE 512
#define DEF_DIR "logs"
#define MAX_FILENAME_SIZE 256
#define DEF_FILENAME_FORMAT "%(_YYYY_)_%(_DD_)_%(_MM_)_%(_FILE_I_)"
#define DEF_MAX_FILE_SIZE 1048576UL // 2^20 bytes
#define MAX_FILE_EXT_SIZE 16
#define DEF_FILE_EXT "log"
#define MAX_MSG_SIZE 256
#define MAX_FORMAT_SIZE 128
#define DEF_ENTRY_FORMAT "%(_YYYY_)-%(_DD_)-%(_MM_) %(_%hh_):%(_mm_):%(_ss_) %(_LVL_) %(_MSG_)\n"
#define DEF_ENABLE_STATE false

#define NO_FILE_NAME ""
#define NO_DIR ""
#define NO_FILE_EXT ""

/* Macros the user can use to format log entries. */
// Expands to the current year, represented in four digits.
#define YEAR_MACRO "%(_YYYY_)"
// Expands to the current month, represented in two digits.
#define MONTH_MACRO "%(_MM_)"
// Expands to the current day of the month, represented in two digits.
#define DAY_MACRO "%(_DD_)"
// Expands to the current hour of the day, represented in two digits.
#define HOUR_MACRO "%(_hh_)"
// Expands to the current minute of the hour, represented in two digits.
#define MINUTE_MACRO "%(_mm_)"
// Expands to the current second of the minute, represented in two digits.
#define SEC_MACRO "%(_ss_)"
// Expands to the current day of the week, occupying nine characters
// (Wednesday) - spare characters will be .
#define DAY_OF_WEEK_L_MACRO "%(_DOW_L_)"
// Expands to the current day of the week, represented in three characters.
#define DAY_OF_WEEK_S_MACRO "%(_DOW_S_)"
// Expands to the current logging level of the log object in capital letters,
// occupying eight characters (CRITICAL).
#define LEVEL_MACRO "%(_LVL_)"
// Expands to the current logging level of the log object in capital letters,
// occupying eight characters (Critical).
#define LEVEL_FC_MACRO "%(_Lvl_)"
// Expands to the current logging level of the log object in non-capital
// letters, occupying eight characters (critical).
#define LEVEL_NC_MACRO "%(_lvl_)"
// Expands to the log message as inputted by the user in a write call.
#define MSG_MACRO  "%(_MSG_)"

#define FILE_ITER_MACRO "%(_FILE_I_)"

#define MON_L "Monday"
#define MON_L_C "MONDAY"
#define MON_S "Mon"
#define MON_S_C "MON"

#define TUE_L "Tuesday"
#define TUE_L_C "TUESDAY"
#define TUE_S "Tue"
#define TUE_S_C "TUE"

#define WED_L "Wednesday"
#define WED_L_C "WEDNESDAY"
#define WED_S "Wed"
#define WED_S_C "WED"

#define THU_L "Thursday"
#define THU_L_C "THURSDAY"
#define THU_S "Thu"
#define THU_S_C "THU"

#define FRI_L "Friday"
#define FRI_L_C "FRIDAY"
#define FRI_S "Fri"
#define FRI_S_C "FRI"

#define SAT_L "Saturday"
#define SAT_L_C "SATURDAY"
#define SAT_S "Sat"
#define SAT_S_C "SAT"

#define SUN_L "Sunday"
#define SUN_L_C "SUNDAY"
#define SUN_S "Sun"
#define SUN_S_C "SUN"

#define DOW_L_FIELD_SIZE sizeof(WED_L)
#define DOW_S_FIELD_SIZE sizeof(WED_S)

#define DEBUG_STR "Debug"
#define DEBUG_STR_C "DEBUG"
#define INFO_STR "Info"
#define INFO_STR_C "INFO"
#define WARNING_STR "Warning"
#define WARNING_STR_C "WARNING"
#define ERROR_STR "Error"
#define ERROR_STR_C "ERROR"
#define CRITICAL_STR "Critical"
#define CRITICAL_STR_C "CRITICAL"
#define LVL_FIELD_SIZE sizeof(CRITICAL_STR);

#define NEWLINE_CHAR "\n"

#endif // LOG_MACROS_H
