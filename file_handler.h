/*
 * File: file_handler.h
 * Project: logger
 * Created: 2019-04-17
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines a file handling interface.
 */

#include "macros.h"
#include "types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Defines the properties of a file handler object. */
typedef struct {
	FILE* fstream_;

	LOG_BUFFERING_POLICY buffering_policy_;
	size_t buffer_capacity_;

	LOG_FILE_POLICY file_policy_;
	char file_dir_[LOG_MAX_DIR_SIZE];
	char filename_format_[LOG_MAX_FILENAME_SIZE];
	char current_filename_[LOG_MAX_FILENAME_SIZE];
	size_t max_file_size_;
	bool is_file_creator_;
	bool has_file_changed_;
	size_t file_iteration_;
} fhandler_t;

LOG_ERROR
fhandler_init(fhandler_t* fhandler,
	LOG_BUFFERING_POLICY buffering_policy,
	size_t buffer_size,
	LOG_FILE_POLICY file_policy,
	char* file_dir,
	char* filename_format,
	size_t max_file_size);

LOG_ERROR
fhandler_close(fhandler_t* fhandler);

LOG_ERROR
fhandler_set_buffering_policy(fhandler_t* fhandler, LOG_BUFFERING_POLICY policy);

LOG_ERROR
fhandler_buffering_policy(fhandler_t* handler, LOG_BUFFERING_POLICY* policy);

LOG_ERROR
fhandler_set_buffer_size(fhandler_t* handler, size_t size);

LOG_ERROR
fhandler_buffer_size(fhandler_t* handler, size_t* size);

LOG_ERROR
fhandler_set_file_policy(fhandler_t* handler, LOG_FILE_POLICY policy);

LOG_ERROR
fhandler_file_policy(fhandler_t* handler, LOG_FILE_POLICY* policy);

LOG_ERROR
fhandler_set_dir(fhandler_t* handler, char* dir);

LOG_ERROR
fhandler_dir(fhandler_t* handler, char* dir);

LOG_ERROR
fhandler_set_filename_format(fhandler_t* handler, char* dir);

LOG_ERROR
fhandler_set_max_file_size(fhandler_t* handler, size_t size);

LOG_ERROR
fhandler_max_file_size(fhandler_t* handler, size_t* size);

LOG_ERROR
fhandler_file_iter(fhandler_t* handler, size_t* iter);

LOG_ERROR
fhandler_write(fhandler_t* handler, char* message);

LOG_ERROR
fhandler_flush_buffer(fhandler_t* handler, char* message);
