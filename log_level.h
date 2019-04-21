/*
 * File: log_level.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines items related to log levels.
 * Log level indicates the importance of the
 * log write request. If the request level does not
 * exceed the threshold set for the log object,
 * it is ignored.
 */

typedef enum {
	L_TRACE,
	L_DEBUG,
	L_INFO,
	L_WARNING,
	L_ERROR,
	L_CRITICAL
} LOG_LEVEL;
#define __VALID_LVL_COUNT 6
const LOG_LEVEL VALID_LOG_LEVELS[__VALID_LVL_COUNT];
const char* const LOG_LEVEL_STRS[__VALID_LVL_COUNT];
