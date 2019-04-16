/*
 * File: log_types.h
 * Project: logger
 * Created: 2019-04-15
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines various supporting data types and
 * related values used in the project.
 */

#ifndef LOG_ENUMS_H
#define LOG_ENUMS_H

typedef enum {
	NOT_SET,
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
} LOG_LEVEL;
#define LOG_NO_VALID_LEVELS 6
static const LOG_LEVEL LOG_LEVELS[6] =
	{ TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL };

typedef enum {
	NO_FILE_POLICY,
	REWRITE,
	ITERATIVE,
	IGNORE_EXCESS
} LOG_FILE_POLICY;
#define LOG_NO_FILE_POLICIES 4
static const LOG_FILE_POLICY LOG_FILE_POLICIES[LOG_NO_FILE_POLICIES] =
	{ NO_FILE_POLICY, REWRITE, ITERATIVE, IGNORE_EXCESS };

typedef enum {
	DO_BUFFER,
	DONT_BUFFER
} LOG_BUFFERING_POLICY;
#define LOG_NO_BUF_POLICIES 2
static const LOG_BUFFERING_POLICY LOG_BUF_POLICIES[LOG_NO_BUF_POLICIES] =
	{ DO_BUFFER, DONT_BUFFER };

typedef enum {
	BAD_LOG,
	BAD_LOG_LEVEL,
	BAD_BUF_POLICY,
	BAD_BUF_SIZE,
	BAD_BUFFER,
	BAD_FILE_POLICY,
	BAD_DIR,
	BAD_FILENAME,
	BAD_FILE_EXT,
	BAD_USER_BUFFER,
	BAD_ENTRY_FORMAT,
	BAD_ENTRY
} LOG_ERROR;

#endif // LOG_ENUMS_H
