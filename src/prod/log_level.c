/*
 * File: log_level.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "log_level.h"

const LOG_LEVEL _VALID_LOG_LEVELS[_VALID_LVL_COUNT] =
    { L_TRACE, L_DEBUG, L_INFO, L_NOTICE, L_WARNING, L_ERROR, L_CRITICAL, L_ALERT, L_EMERGENCY };

const char* const _LOG_LEVEL_STRS[_VALID_LVL_COUNT] =
    { "TRACE    ",
      "DEBUG    ",
      "INFO     ",
      "NOTICE   ",
      "WARNING  ",
      "ERROR    ",
      "CRITICAL ",
      "ALERT    ",
      "EMERGENCY"
    };
