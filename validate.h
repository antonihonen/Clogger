/*
 * File: validate.h
 * Project: logger
 * Created: 2019-04-16
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines functions that validate user input.
 */

#include "types.h"
#include "stdbool.h"

bool is_valid_dir(char* dir);

bool is_valid_filename_format(char* filename_format);

bool is_valid_path(char* path);

bool is_valid_log_lvl(LOG_LEVEL level);

bool is_valid_file_policy(LOG_FILE_POLICY policy);

bool is_valid_buf_policy(LOG_BUFFERING_POLICY policy);
