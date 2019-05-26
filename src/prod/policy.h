/*
 * File: policy.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines file policies
 * and buffering policies supported by the library.
 * File policy determines what happens when
 * the current log file reaches its maximum size.
 * Buffering policy determines how log output is
 * buffered.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef POLICY_H
#define POLICY_H

/* REWRITE: Only use one log file and whenever it gets full,
erase all data in the file and keep writing in the same file.
ROTATE: When the log file gets full, append a sequential
number to the file name.
IGNORE_EXCESS: When the file gets full, no longer accept
log writes until the file has been emptied by an external
process. */
typedef enum {
	REWRITE = 1,
	ROTATE
} LOG_FILE_MODE;
#define __VALID_FILEPOL_COUNT ROTATE
const LOG_FILE_MODE __VALID_FILE_POLICIES[__VALID_FILEPOL_COUNT];

/* These three buffering modes correspond 1:1 with the buffering modes
explained in the documentation of the setvbuf function(stdio.h).*/
typedef enum {
	NO_BUFFERING = 1,
	LINE_BUFFERING,
	FULL_BUFFERING
} LOG_BUF_MODE;
#define __VALID_BUFPOL_COUNT FULL_BUFFERING
const LOG_BUF_MODE __VALID_BUF_POLICIES[__VALID_BUFPOL_COUNT];

#endif /* POLICY_H */
