/*
 * File: log_level.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 */

#include "log_level.h"

const LOG_LEVEL VALID_LOG_LEVELS[6] =
{ L_TRACE, L_DEBUG, L_INFO, L_WARNING, L_ERROR, L_CRITICAL };

const char* const LOG_LEVEL_STRS[__VALID_LVL_COUNT] =
{ "TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL" };
