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
	// Determines whether output is buffered. If it is,
	// all log entries are first written into a buffer,
	// the contents of which will be written into the log
	// file at once when the buffer is about to get full
	// if a file policy other than NO_FILE_POLICY
	// has been selected. 
	LOG_BUFFERING_POLICY buffering_policy_;
	
	// The base address of the output buffer.
	void* buffer_;

	// The capacity of the buffer in bytes.
	size_t buffer_capacity_;

	// The offset of the next byte in the buffer to be written in
	// in relation to the buffer base address.
	size_t buffer_head_;
	
	// Indicates whether the log object has allocated
	// the buffer memory by itself or if it was given
	// by the user.
	bool is_buf_memory_owner_;

	// Determines what action is taken when the log file
	// reaches its maximum size.
	LOG_FILE_POLICY file_policy_;

	// Full path of the directory the log file resides in.
	char file_dir_[LOG_MAX_DIR_SIZE];

	// The file name format to be used for the log file.
	// Macros can be used for example to make the name include
	// the current date.
	char file_name_[LOG_MAX_FILENAME_SIZE];

	// The log file extension of the output file.
	char file_ext_[LOG_MAX_FILE_EXT_SIZE];
	
	// The maximum size of a single log file.
	// When the maximum file size is reached, the
	// chosen file policy dictates what action is taken.
	size_t max_file_size_;

	// Indicates whether the log object created the file
	// it is writing to.
	bool is_file_creator_;

	// Indicates whether the log file has been changed by
	// the log object.
	bool has_file_changed_;

	// The format after which log entries are formatted.
	// Macros such as date can be used to determine the format.
	char entry_format_[LOG_MAX_FORMAT_SIZE];

	// The active threshold level. Any entry with a lower level
	// than the threshold level will be ignored.
	LOG_LEVEL entry_threshold_;

	// Indicates whether the log object accepts any entries -
	// if not, all entries are ignored as if their level
	// was lower than the entry threshold.
	bool do_allow_entries_;
} log_t;

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

LOG_ERROR
log_enable(log_t* log);

LOG_ERROR
log_disable(log_t* log);

LOG_ERROR
log_close(log_t* log);

LOG_ERROR
log_set_threshold(log_t* log, LOG_LEVEL new_threshold);

LOG_ERROR
log_threshold(log_t* log, LOG_LEVEL* threshold);

LOG_ERROR
log_set_buffering_policy(log_t* log);

LOG_ERROR
log_buffering_policy(log_t* log, LOG_BUFFERING_POLICY* policy);

LOG_ERROR
log_set_buffer(log_t* log, void* buffer, size_t size);

LOG_ERROR
log_buffer(log_t* log, void** buffer);

LOG_ERROR
log_buffer_head(log_t* log, void** head);

LOG_ERROR
log_flush_buffer(log_t* log);

LOG_ERROR
log_clear_buffer(log_t* log);

LOG_ERROR
log_buffer_capacity(log_t* log, size_t* capacity);

LOG_ERROR
log_buffer_size(log_t* log, size_t* size);

LOG_ERROR
log_buffer_space_left(log_t* log, size_t* free_space);

LOG_ERROR
log_set_file_policy(log_t* log, LOG_FILE_POLICY new_policy);

LOG_ERROR
log_file_policy(log_t* log, LOG_FILE_POLICY* policy);

LOG_ERROR
log_set_dir(log_t* log, char* new_dir);

LOG_ERROR
log_dir(log_t* log, char** dir);

LOG_ERROR
log_set_filename(log_t* log, char* filename);

LOG_ERROR
log_filename(log_t* log, char** filename);

LOG_ERROR
log_filepath(log_t* log, char** path);

LOG_ERROR
log_set_file_ext(log_t* log, char* new_file_ext);

LOG_ERROR
log_file_ext(log_t* log, char** file_ext);

LOG_ERROR
log_set_max_file_size(log_t* log, size_t new_file_size);

LOG_ERROR
log_max_file_size(log_t* log, size_t* file_size);

LOG_ERROR
log_current_file_size(log_t* log, size_t* file_size);

LOG_ERROR
log_set_entry_format(log_t* log, char* format);

LOG_ERROR
log_write(log_t* log, LOG_LEVEL level, char* message);

LOG_ERROR
log_debug(log_t* log, char* message);

LOG_ERROR
log_info(log_t* log, char* message);

LOG_ERROR
log_warning(log_t* log, char* message);

LOG_ERROR
log_error(log_t* log, char* message);

LOG_ERROR
log_critical(log_t* log, char* message);

#endif // LOG_H
