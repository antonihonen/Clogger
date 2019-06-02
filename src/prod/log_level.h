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

#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

typedef enum {
    L_NO_LEVEL = -1, /* Only intended for internal use. */
    L_TRACE = 0,
    L_DEBUG,
    L_INFO,
    L_WARNING,
    L_ERROR,
    L_CRITICAL
} LOG_LEVEL;
#define _VALID_LVL_COUNT (L_CRITICAL + 1)

const LOG_LEVEL _VALID_LOG_LEVELS[_VALID_LVL_COUNT];
const char* const _LOG_LEVEL_STRS[_VALID_LVL_COUNT];

#endif /* LOG_LEVEL_H */
