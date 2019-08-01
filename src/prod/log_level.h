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
    LG_L_NO_LEVEL = -1, /* Only intended for internal use. */
    LG_L_TRACE = 0,
    LG_L_DEBUG,
    LG_L_INFO,
    LG_L_NOTICE,
    LG_L_WARNING,
    LG_L_ERROR,
    LG_L_CRITICAL,
    LG_L_ALERT,
    LG_L_EMERGENCY
} LG_LEVEL;
#define LG_VALID_LVL_COUNT (LG_L_EMERGENCY + 1)

const LG_LEVEL LG_VALID_LOG_LEVELS[LG_VALID_LVL_COUNT];
const char* const LG_LOG_LEVEL_STRS[LG_VALID_LVL_COUNT];

#endif /* LOG_LEVEL_H */
