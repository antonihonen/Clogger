/*
 * File: log.h
 * Project: logger
 * Created: 2019-04-15
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines a flexible and efficient logging interface.
 */

#ifndef LOG_H
#define LOG_H

#include "log_macros.h"
#include "log_types.h"
#include <stddef.h>
#include <stdbool.h>

/* Defines the properties of a log object. */
typedef struct
{
	/* Determines whether output is buffered. If it is,
	all log entries are first written into a buffer,
	the contents of which will be written into the log
	file at once when the buffer is about to get full
	if a file policy other than NO_FILE_POLICY
	has been selected. */
	LOG_BUFFERING_POLICY buffering_policy_;
	
	/* The base address of the output buffer. */
	void* buffer_;

	/* The capacity of the buffer in bytes. */
	size_t buffer_capacity_;

	/* The offset of the next byte in the buffer to be written in
	in relation to the buffer base address. */
	size_t buffer_head_;
	
	/* Indicates whether the log object has allocated
	the buffer memory by itself or if it was given
	by the user. */
	bool is_buf_memory_owner_;

	/* Determines what action is taken when the log file
	reaches its maximum size. */
	LOG_FILE_POLICY file_policy_;

	/* Full path of the directory the log file resides in. */
	char file_dir_[LOG_MAX_DIR_SIZE];

	/* The file name format to be used for the log file.
	Macros can be used, for example to make the name include
	the current date. */
	char file_name_[LOG_MAX_FILENAME_SIZE];

	/* The log file extension of the output file. */
	char file_ext_[LOG_MAX_FILE_EXT_SIZE];
	
	/* The maximum size of a single log file.
	When the maximum file size is reached, the
	chosen file policy dictates what action is taken. */
	size_t max_file_size_;

	/* Indicates whether the log object created the file
	it is writing to. */
	bool is_file_creator_;

	/* Indicates whether the log file has been changed by
	the log object. */
	bool has_file_changed_;

	/* The format after which log entries are formatted.
	Macros such as date can be used to determine the format. */
	char entry_format_[LOG_MAX_FORMAT_SIZE];

	/* The active threshold level. Any entry with a lower level
	than the threshold level will be ignored. */
	LOG_LEVEL entry_threshold_;

	/* Indicates whether the log object accepts any entries -
	if not, all entries are ignored as if their level
	was lower than the entry threshold. */
	bool do_allow_entries_;
} log_t;

/* Initializes a log object. The object can be used
immediately after initialization.
@log: A pointer to the log object.
@entry_threshold:
@entry_format:
@buffering_policy:
@buffer_size:
@buffer:
@file_policy:
@dir:
@filename:
@file_ext:
@max_file_size:
@return:
*/
LOG_ERROR
log_init(log_t* log,
	LOG_LEVEL entry_threshold,
	char* entry_format,
	LOG_BUFFERING_POLICY buffering_policy,
	size_t buffer_size,
	void* buffer,
	LOG_FILE_POLICY file_policy,
	char* dir,
	char* filename,
	char* file_ext,
	size_t max_file_size);

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

/* Flushes the output buffer and releases buffer memory if
owned by the log object (memory was allocated by the object
upon the call to log_init).
@log: A pointer to the log object.
@return:
*/
LOG_ERROR
log_close(log_t* log);

/* Sets a LOG_LEVEL threshold which log entries will have
to exceed in order to be accepted to be written into the log
file.
@log: A pointer to the log object.
@new_threshold:
@return:
*/
LOG_ERROR
log_set_threshold(log_t* log, LOG_LEVEL new_threshold);

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
@new_policy:
@return:
*/
LOG_ERROR
log_set_buffering_policy(log_t* log, LOG_BUFFERING_POLICY new_policy);

/* Gets the active buffering policy.
@log: A pointer to the log object.
@policy:
@return:
*/
LOG_ERROR
log_buffering_policy(log_t* log, LOG_BUFFERING_POLICY* policy);

/* Sets a new buffer for the log object. This will replace the
old buffer - only a single buffer can be active at a time. If
the old buffer was allocated by the log object upon the call to
log_init, the buffer memory will be released. Otherwise the user
is responsible for releasing the buffer memory.
@log: A pointer to the log object.
@new_buffer:
@new_buf_size:
@return:
*/
LOG_ERROR
log_set_buffer(log_t* log, void* new_buffer, size_t new_buf_size);

/* Gets a pointer to the output buffer's base address.
@log: A pointer to the log object.
@buffer:
@return:
*/
LOG_ERROR
log_buffer(log_t* log, void** buffer);

/* Gets a pointer to the address in which the
next write to the output buffer will happen.
@log: A pointer to the log object.
@head:
@return:
*/
LOG_ERROR
log_buffer_head(log_t* log, void** head);

/* Flushes the output buffer, writing any data in the
buffer into the log file and emptying the buffer.
@log: A pointer to the log object.
@return:
*/
LOG_ERROR
log_flush_buffer(log_t* log);

/* Discards all data in the output buffer. Not to be
confused with log_flush_buffer.
@log: A pointer to the log object.
@return:
*/
LOG_ERROR
log_clear_buffer(log_t* log);

/* Gets the capacity of the output buffer in bytes.
@log: A pointer to the log object.
@capacity:
@return:
*/
LOG_ERROR
log_buffer_capacity(log_t* log, size_t* capacity);

/* Gets the number of bytes currently in the output
buffer.
@log: A pointer to the log object.
@size:
@return:
*/
LOG_ERROR
log_buffer_size(log_t* log, size_t* size);

/* Gets the current amount of free space in the
output buffer in bytes.
@log: A pointer to the log object.
@free_space:
@return:
*/
LOG_ERROR
log_buffer_space_left(log_t* log, size_t* free_space);

/* Sets the file policy for the log. The file policy
determines what action is taken when the log file reaches
its maximum size.
@log: A pointer to the log object.
@new_policy:
@return:
*/
LOG_ERROR
log_set_file_policy(log_t* log, LOG_FILE_POLICY new_policy);

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
@new_dir:
@return:
*/
LOG_ERROR
log_set_dir(log_t* log, char* new_dir);

/* Gets the full path of the log file directory.
@log: A pointer to the log object.
@dir:
@return:
*/
LOG_ERROR
log_dir(log_t* log, char** dir);

/* Sets the file name format for the log.
@log: A pointer to the log object.
@filename:
@return:
*/
LOG_ERROR
log_set_filename(log_t* log, char* filename);

/* Gets the exact name of the current log file
including the file format but excluding the
directory path.
@log: A pointer to the log object.
@filename:
@return:
*/
LOG_ERROR
log_filename(log_t* log, char** filename);

/* Returns the full path of the current log file.
@log: A pointer to the log object.
@path:
@return:
*/
LOG_ERROR
log_filepath(log_t* log, char** path);

/* Sets the log file extension.
@log: A pointer to the log object.
@new_file_ext:
@return:
*/
LOG_ERROR
log_set_file_ext(log_t* log, char* new_file_ext);

/* Gets the log file extension.
@log: A pointer to the log object.
@file_ext:
@return:
*/
LOG_ERROR
log_file_ext(log_t* log, char** file_ext);

/* Sets the maximum size of a single log file in bytes.
@log: A pointer to the log object.
@new_file_size:
@return:
*/
LOG_ERROR
log_set_max_file_size(log_t* log, size_t new_file_size);

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
@format:
@return:
*/
LOG_ERROR
log_set_entry_format(log_t* log, char* format);

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

#endif // LOG_H
