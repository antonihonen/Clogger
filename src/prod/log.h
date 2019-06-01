/*
 * File: log.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains the top-level log class of the library.
 * 
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LOG_H
#define LOG_H

#include "file_handler.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define __DEF_MAX_FSIZE 102400 /* 100 kiB */
#define __DEF_THRESHOLD L_TRACE
#define __DEF_ENTRY_FORMAT "%(MSG)\n"

/* Log. */
typedef struct
{
	/* The file handler object that will take care of file writes,
	directory and file naming etc. The log object doesn't need to
	know anything about any of that, it only passes the information
	to the file handler. */
	fhandler_t* _fh;

	/* Entry formatter. Required to expand format macros in log entries. */
	e_format_t* _ef;

	/* The active threshold level. Any entry with a lower level
	than the threshold level will be ignored. */
	LOG_LEVEL _threshold;

	/* Indicates whether the log object accepts any entries -
	if not, all entries are ignored as if their level
	was lower than the entry threshold. */
	bool _is_enabled;
} log_t;

/* Initializes a log object. The object can be used
immediately after initialization. */
log_t*
log_init(char* dirn_format,
	char* fn_format,
	LOG_FILE_MODE file_mode,
	int buf_mode);

/* Enables writing to the log. When writing is enabled,
entries that exceed the active entry threshold will be
accepted. */
bool
log_enable(log_t* log);

/* Disables writing to the log. When writing is disabled,
all entries will be ignored. */
bool
log_disable(log_t* log);

/* Releases all resources occupied by the log object.
Flushes log output buffer if any. */
bool
log_close(log_t* log);

/* Sets a log level threshold which log entries will have
to exceed in order to be accepted to be written into the log
file. Accepted values are: TRACE < DEBUG < INFO < WARNING
< ERROR < CRITICAL. */
bool
log_set_threshold(log_t* log, LOG_LEVEL threshold);

/* Gets the active log entry threshold. */
LOG_LEVEL
log_threshold(log_t* log);

bool
log_set_buf_mode(log_t* log, int mode);

int
log_buf_mode(log_t* log);

bool
log_set_buf_size(log_t* log, size_t size);

/* Sets the file mode for the log. The file mode
determines what action is taken when the log file reaches
its maximum size. */
bool
log_set_file_mode(log_t* log, LOG_FILE_MODE mode);

/* Gets the active file mode. */
LOG_FILE_MODE
log_file_mode(log_t* log);

bool
log_set_dirn_format(log_t* log, char* format);

/* Gets the absolute path of the log file directory. */
char*
log_curr_dirname(log_t* log, char* dir);

/* Sets the file name format for the log. */
bool
log_set_fname_format(log_t* log, char* format);

char*
log_curr_fname(log_t* log, char* filename);

/* Returns the full path of the current log file. */
char*
log_curr_fpath(log_t* log, char* filepath);

/* Sets the maximum size of a single log file in bytes. */
bool
log_set_max_fsize(log_t* log, size_t size);

/* Gets the maximum size of a single log file in bytes. */
size_t
log_max_fsize(log_t* log);

/* Gets the current size of the current log file in bytes. */
size_t
log_current_fsize(log_t* log);

/* Sets the entry format that all new entries will be formatted
after. */
bool
log_set_entry_format(log_t* log, char* format);

/* Formats a log message according to the active entry
format and writes it to the buffer if buffering is enabled
or directly to the log file if buffering is disabled. The
message will be ignored if the logging level of the message
doesn't exceed the active entry threshold of the log object.
*/
bool
log_write(log_t* log, LOG_LEVEL level, char* message);

/* The same as log_write but with logging level implicitly set to TRACE. */
bool
log_trace(log_t* log, char* message);

/* The same as log_write but with logging level implicitly set to DEBUG. */
bool
log_debug(log_t* log, char* message);

/* The same as log_write but with logging level implicitly set to INFO. */
bool
log_info(log_t* log, char* message);

/* The same as log_write but with logging level implicitly set to WARNING. */
bool
log_warning(log_t* log, char* message);

/* The same as log_write but with logging level implicitly set to ERROR. */
bool
log_error(log_t* log, char* message);

/* The same as log_write but with logging level implicitly set to CRITICAL. */
bool
log_critical(log_t* log, char* message);

#endif /* LOG_H */
