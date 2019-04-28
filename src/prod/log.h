/*
 * File: log.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains the main class of the library,
 * the logger type log_t.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LOG_H
#define LOG_H

#include "error.h"
#include "log_level.h"
#include "macros.h"
#include "policy.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Defines the properties of a log object. */
typedef struct
{
	/* Determines whether output is buffered. If it is,
	all log entries are first written into a buffer,
	the contents of which will be written into the log
	file at once when the buffer is about to get full
	if a file policy other than NO_FILE_POLICY
	has been selected. */
	LOG_BUFFERING_POLICY _buffering_policy;

	/* The capacity of the buffer in bytes. */
	size_t _buffer_capacity_;

	/* Determines what action is taken when the log file
	reaches its maximum size. */
	LOG_FILE_POLICY _file_policy;

	/* Full path of the directory the log file resides in. */
	char _file_dir[__MAX_DIR_SIZE];

	/* The file name format to be used for the log file. Includes
	file extension.
	Macros can be used, for example to make the name include
	the current date. */
	char _filename_format[__MAX_FILENAME_SIZE];
	
	/* The maximum size of a single log file.
	When the maximum file size is reached, the
	chosen file policy dictates what action is taken. */
	size_t _max_file_size;

	/* A handle to the currently active file stream. */
	FILE* _file;

	/* Indicates whether the log object created the file
	it is writing to. */
	bool _is_file_creator;

	/* Indicates whether the log file has been changed by
	the log object. */
	bool _has_file_changed;

	/* The format after which log entries are formatted.
	Macros such as date can be used to determine the format. */
	char _entry_format[__MAX_E_FORMAT_SIZE];

	/* The active threshold level. Any entry with a lower level
	than the threshold level will be ignored. */
	LOG_LEVEL _entry_threshold;

	/* Indicates whether the log object accepts any entries -
	if not, all entries are ignored as if their level
	was lower than the entry threshold. */
	bool _do_allow_entries;
} log_t;

/* Initializes a log object. The object can be used
immediately after initialization.
@log: A pointer to the log object.
@dir:
@filename_format:
@max_file_size:
@file_policy:
@output_buffer_size:
@output_buffer:
@buffering_policy:
@return:
*/
LOG_ERROR
log_init(log_t* log,
	char* dir,
	char* filename_format,
	size_t max_file_size,
	LOG_FILE_POLICY file_policy,
	LOG_BUFFERING_POLICY buffering_policy);

/* Enables writing to the log. When writing is enabled,
entries that exceed the active entry threshold will be
accepted.
@log: A pointer to the log object.
@return:
*/
LOG_ERROR
log_enable(log_t* log);

/* Disables writing to the log. When writing is disabled,
all entries will be ignored.
@log: A pointer to the log object.
@return:
*/
LOG_ERROR
log_disable(log_t* log);

/* Flushes the output buffer and releases memory.
@log: A pointer to the log object.
@return:
*/
LOG_ERROR
log_close(log_t* log);

/* Sets a log level threshold which log entries will have
to exceed in order to be accepted to be written into the log
file. Accepted values are: TRACE < DEBUG < INFO < WARNING
< ERROR < CRITICAL.
@log: A pointer to the log object.
@threshold:
@return:
*/
LOG_ERROR
log_set_threshold(log_t* log, LOG_LEVEL threshold);

/* Gets the active log entry threshold.
@log: A pointer to the log object.
@threshold:
@return:
*/
LOG_ERROR
log_threshold(log_t* log, LOG_LEVEL* threshold);

/* Sets the buffering policy for the log. If buffering is
enabled, entries will first be written in a buffer rather
than the log file. When the buffer gets full, all data in
the buffer are written into the file at once.
@log: A pointer to the log object.
@policy:
@return:
*/
LOG_ERROR
log_set_buffering_policy(log_t* log, LOG_BUFFERING_POLICY policy);

/* Gets the active buffering policy.
@log: A pointer to the log object.
@policy:
@return:
*/
LOG_ERROR
log_buffering_policy(log_t* log, LOG_BUFFERING_POLICY* policy);

/* Sets a new size for the output buffer. The old buffer is
discarded - the user must flush the old buffer first if
data must not be lost.
@log: A pointer to the log object.
@buffer_size:
@return:
*/
LOG_ERROR
log_set_buffer_size(log_t* log, size_t buffer_size);

/* Flushes the output buffer, writing any data in the
buffer into the log file and emptying the buffer.
@log: A pointer to the log object.
@return:
*/
LOG_ERROR
log_flush_buffer(log_t* log);

/* Sets the file policy for the log. The file policy
determines what action is taken when the log file reaches
its maximum size.
@log: A pointer to the log object.
@policy:
@return:
*/
LOG_ERROR
log_set_file_policy(log_t* log, LOG_FILE_POLICY policy);

/* Gets the active file policy.
@log: A pointer to the log object.
@policy:
@return:
*/
LOG_ERROR
log_file_policy(log_t* log, LOG_FILE_POLICY* policy);

/* Sets the directory in which the log file will be found.
Full path to the directory is expected.
@log: A pointer to the log object.
@dir:
@return:
*/
LOG_ERROR
log_set_dir(log_t* log, char* dir);

/* Gets the full path of the log file directory.
@log: A pointer to the log object.
@dir:
@return:
*/
LOG_ERROR
log_dir(log_t* log, char* dir);

/* Sets the file name format for the log.
@log: A pointer to the log object.
@filename_format:
@return:
*/
LOG_ERROR
log_set_filename_format(log_t* log, char* filename_format);

/* Gets the exact name of the current log file
including the file format but excluding the
directory path.
@log: A pointer to the log object.
@filename:
@return:
*/
LOG_ERROR
log_current_file_name(log_t* log, char* filename);

/* Returns the full path of the current log file.
@log: A pointer to the log object.
@path:
@return:
*/
LOG_ERROR
log_filepath(log_t* log, char* path);

/* Sets the maximum size of a single log file in bytes.
@log: A pointer to the log object.
@file_size:
@return:
*/
LOG_ERROR
log_set_max_file_size(log_t* log, size_t file_size);

/* Gets the maximum size of a single log file in bytes.
@log: A pointer to the log object.
@file_size:
@return:
*/
LOG_ERROR
log_max_file_size(log_t* log, size_t* file_size);

/* Gets the current size of the current log file in bytes.
@log: A pointer to the log object.
@file_size:
@return:
*/
LOG_ERROR
log_current_file_size(log_t* log, size_t* file_size);

/* Sets the entry format that all new entries will be formatted
after.
@log: A pointer to the log object.
@entry_format:
@return:
*/
LOG_ERROR
log_set_entry_format(log_t* log, char* entry_format);

/* Formats a log message according to the active entry
format and writes it to the buffer if buffering is enabled
or directly to the log file if buffering is disabled. The
message will be ignored if the logging level of the message
doesn't exceed the active entry threshold of the log object.
@log: A pointer to the log object.
@message:
@return:
*/
LOG_ERROR
log_write(log_t* log, LOG_LEVEL level, char* message);

/* The same as log_write but with logging level set to TRACE.
@log: A pointer to the log object.
@message:
@return:
*/
LOG_ERROR
log_trace(log_t* log, char* message);

/* The same as log_write but with logging level set to DEBUG.
@log: A pointer to the log object.
@message:
@return:
*/
LOG_ERROR
log_debug(log_t* log, char* message);

/* The same as log_write but with logging level set to INFO.
@log: A pointer to the log object.
@message:
@return:
*/
LOG_ERROR
log_info(log_t* log, char* message);

/* The same as log_write but with logging level set to WARNING.
@log: A pointer to the log object.
@message:
@return:
*/
LOG_ERROR
log_warning(log_t* log, char* message);

/* The same as log_write but with logging level set to ERROR.
@log: A pointer to the log object.
@message:
@return:
*/
LOG_ERROR
log_error(log_t* log, char* message);

/* The same as log_write but with logging level set to CRITICAL.
@log: A pointer to the log object.
@message:
@return:
*/
LOG_ERROR
log_critical(log_t* log, char* message);

#endif /* LOG_H */
