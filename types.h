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
	L_TRACE,
	L_DEBUG,
	L_INFO,
	L_WARNING,
	L_ERROR,
	L_CRITICAL
} LOG_LEVEL;
#define __VALID_LVL_COUNT 6
const LOG_LEVEL VALID_LOG_LEVELS[__VALID_LVL_COUNT];

typedef enum {
	REWRITE,
	ROTATE,
	IGNORE_EXCESS
} LOG_FILE_POLICY;
#define __VALID_FILEPOL_COUNT 3
const LOG_FILE_POLICY VALID_FILE_POLICIES[__VALID_FILEPOL_COUNT];

typedef enum {
	NO_BUFFERING,
	LINE_BUFFERING,
	FULL_BUFFERING
} LOG_BUFFERING_POLICY;
#define __VALID_BUFPOL_COUNT 3
const LOG_BUFFERING_POLICY VALID_BUF_POLICIES[__VALID_BUFPOL_COUNT];

typedef enum {
	E_NO_ERROR,
	E_BAD_LOG,
	E_BAD_LOG_LEVEL,
	E_BAD_BUF_POLICY,
	E_BAD_BUF_SIZE,
	E_BAD_BUFFER,
	E_BAD_FILE_POLICY,
	E_BAD_DIR,
	E_BAD_FILENAME,
	E_BAD_FILE_EXT,
	E_BAD_USER_BUFFER,
	E_BAD_ENTRY_FORMAT,
	E_BAD_ENTRY,
	E_BAD_PATH
} LOG_ERROR;

#endif // LOG_ENUMS_H
