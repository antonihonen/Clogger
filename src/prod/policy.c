/*
 * File: policy.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "policy.h"

const LOG_FILE_MODE __VALID_FILE_POLICIES[__VALID_FILEPOL_COUNT] =
	{ REWRITE, ROTATE, IGNORE_EXCESS };

const LOG_BUF_MODE __VALID_BUF_POLICIES[__VALID_BUFPOL_COUNT] =
	{ NO_BUFFERING, LINE_BUFFERING, FULL_BUFFERING };
