/*
 * File: log_level.c
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "log_level.h"

const LG_LEVEL LG_VALID_LEVELS[LG_VALID_LVL_COUNT] =
    {
      LG_TRACE,
      LG_DEBUG,
      LG_INFO,
      LG_NOTICE,
      LG_WARNING,
      LG_ERROR,
      LG_CRITICAL,
      LG_ALERT,
      LG_EMERGENCY,
      LG_FATAL
    };

const char* const LG_LEVEL_STRS[LG_VALID_LVL_COUNT] =
    { "TRACE    ",
      "DEBUG    ",
      "INFO     ",
      "NOTICE   ",
      "WARNING  ",
      "ERROR    ",
      "CRITICAL ",
      "ALERT    ",
      "EMERGENCY",
      "FATAL    "
    };
