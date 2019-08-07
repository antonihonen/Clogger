/*
 * File: log_level.h
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
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
    LG_NO_LEVEL = -2, /* Only intended for internal use. */
    LG_ALL_LEVELS = -1, /* Only intended for internal use. */
    LG_TRACE = 0,
    LG_DEBUG,
    LG_INFO,
    LG_NOTICE,
    LG_WARNING,
    LG_ERROR,
    LG_CRITICAL,
    LG_ALERT,
    LG_EMERGENCY,
    LG_FATAL
} LG_LEVEL;
#define LG_VALID_LVL_COUNT (LG_FATAL + 1)

const LG_LEVEL LG_VALID_LEVELS[LG_VALID_LVL_COUNT];
const char* const LG_LEVEL_STRS[LG_VALID_LVL_COUNT];

#endif /* LOG_LEVEL_H */
