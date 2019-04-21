/*
 * File: policy.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 */

#include "policy.h"

const LOG_FILE_POLICY VALID_FILE_POLICIES[__VALID_FILEPOL_COUNT] =
	{ REWRITE, ROTATE, IGNORE_EXCESS };

const LOG_BUFFERING_POLICY VALID_BUF_POLICIES[__VALID_BUFPOL_COUNT] =
	{ NO_BUFFERING, LINE_BUFFERING, FULL_BUFFERING };
