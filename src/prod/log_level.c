/*
 * File: log_level.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "log_level.h"

const LG_LEVEL LG_VALID_LOG_LEVELS[LG_VALID_LVL_COUNT] =
    { LG_L_TRACE, LG_L_DEBUG, LG_L_INFO, LG_L_NOTICE, LG_L_WARNING, LG_L_ERROR, LG_L_CRITICAL, LG_L_ALERT, LG_L_EMERGENCY };

const char* const LG_LOG_LEVEL_STRS[LG_VALID_LVL_COUNT] =
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
