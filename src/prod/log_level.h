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
 *
 * Copyright (C) 2019. Anton Ihonen
 */

typedef enum {
	L_NO_LEVEL = -1,
	L_TRACE = 0,
	L_DEBUG,
	L_INFO,
	L_WARNING,
	L_ERROR,
	L_CRITICAL
} LOG_LEVEL;
#define __VALID_LVL_COUNT L_CRITICAL + 1

const LOG_LEVEL __VALID_LOG_LEVELS[__VALID_LVL_COUNT];
const char* const __LOG_LEVEL_STRS[__VALID_LVL_COUNT];
