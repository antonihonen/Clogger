/*
 * File: policy.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "policy.h"

const LOG_FILE_MODE _VALID_FILE_POLICIES[_VALID_FILEPOL_COUNT] =
    { REWRITE, ROTATE };

const LOG_BUF_MODE _VALID_BUF_POLICIES[_VALID_BUFPOL_COUNT] =
    { NO_BUFFERING, LINE_BUFFERING, FULL_BUFFERING };
