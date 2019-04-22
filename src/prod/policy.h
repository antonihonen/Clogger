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
	REWRITE,
	ROTATE,
	IGNORE_EXCESS
} LOG_FILE_POLICY;
#define __VALID_FILEPOL_COUNT 3
const LOG_FILE_POLICY __VALID_FILE_POLICIES[__VALID_FILEPOL_COUNT];

/* These three buffering modes correspond 1:1 with the buffering modes
explained in the documentation of the setbuf function from stdio.h.*/
typedef enum {
	NO_BUFFERING,
	LINE_BUFFERING,
	FULL_BUFFERING
} LOG_BUFFERING_POLICY;
#define __VALID_BUFPOL_COUNT 3
const LOG_BUFFERING_POLICY __VALID_BUF_POLICIES[__VALID_BUFPOL_COUNT];

#endif /* POLICY_H */