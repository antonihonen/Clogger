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
#define LOG_VALID_LVL_COUNT 6
static const LOG_LEVEL VALID_LOG_LEVELS[6] =
	{ L_TRACE, L_DEBUG, L_INFO, L_WARNING, L_ERROR, L_CRITICAL };

typedef enum {
	REWRITE,
	ROTATE,
	IGNORE_EXCESS
} LOG_FILE_POLICY;
#define LOG_VALID_FILEPOL_COUNT 3
static const LOG_FILE_POLICY VALID_FILE_POLICIES[LOG_VALID_FILEPOL_COUNT] =
	{ REWRITE, ROTATE, IGNORE_EXCESS };

typedef enum {
	NO_BUFFERING,
	LINE_BUFFERING,
	FULL_BUFFERING
} LOG_BUFFERING_POLICY;
#define LOG_VALID_BUFPOL_COUNT 3
static const LOG_BUFFERING_POLICY VALID_BUF_POLICIES[LOG_VALID_BUFPOL_COUNT] =
	{ NO_BUFFERING, LINE_BUFFERING, FULL_BUFFERING };

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

typedef enum
{
	YEAR_M,
	MONTH_M,
	DAY_M,
	HOUR_M,
	MIN_M,
	SEC_M,
	DOW_3_M,
	DOW_FULL_M,
	LVL_M,
	MSG_M,
	ESC_M,
} LOG_FORMAT_MACRO;
#define LOG_YEAR_MACRO "%(YYYY)"
#define LOG_MONTH_MACRO "%(MM)"
#define LOG_DAY_MACRO "%(DD)"
#define LOG_HOUR_MACRO "%(hh)"
#define LOG_MINUTE_MACRO "%(mm)"
#define LOG_SEC_MACRO "%(ss)"
#define LOG_DOW_3_MACRO "%(DOW_3)"
#define LOG_DOW_FULL_MACRO "%(DOW_FULL)"
#define LOG_LEVEL_MACRO "%(LVL)"
#define LOG_MSG_MACRO  "%(MSG)"
#define LOG_MACRO_BEGIN_ESC "%%"
#define LOG_MACRO_BEGIN '%'
#define LOG_MAX_FORMAT_MACRO_LEN 16

#endif // LOG_ENUMS_H
