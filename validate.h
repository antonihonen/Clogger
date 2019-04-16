/*
 * File: validate.h
 * Project: logger
 * Created: 2019-04-16
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file contains functions that validate user input.
 */

#include "types.h"

static bool is_valid_log_lvl(LOG_LEVEL level)
{
	for (size_t i = 0; i < LOG_VALID_LVL_COUNT; ++i)
	{
		if (level == VALID_LOG_LEVELS[i])
		{
			return true;
		}
	}
	return false;
}

static bool is_valid_file_policy(LOG_FILE_POLICY policy)
{
	for (size_t i = 0; i < LOG_VALID_FILEPOL_COUNT; ++i)
	{
		if (policy == GOOD_FILE_POLICIES[i])
		{
			return true;
		}
	}
	return false;
}
