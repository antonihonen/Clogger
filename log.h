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

typedef struct
{
	LOG_BUFFERING_POLICY buffering_policy_;
	void* buffer_;
	size_t buffer_capacity_;
	size_t buffer_head_;
	bool is_buf_memory_owner_;

	LOG_FILE_POLICY file_policy_;
	char file_dir_[LOG_MAX_DIR_SIZE];
	char file_name_[LOG_MAX_FILENAME_SIZE];
	char file_ext_[LOG_MAX_FILE_EXT_SIZE];
	size_t max_file_size_;
	bool is_file_creator_;
	bool has_file_changed_;

	char entry_format_[LOG_MAX_FORMAT_SIZE];
	LOG_LEVEL entry_threshold_;
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
