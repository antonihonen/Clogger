/*
 * File: error.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines error codes used in the project.
 * These error codes may be returned to the user of
 * the library or used internally within the library.
 */

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
