/*
 * File: file_handler.h
 * Project: logger
 * Created: 2019-04-17
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines a file handling interface.
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "macros.h"
#include "types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Defines the properties of a file handler object. */
typedef struct {
	FILE* _fstream;

	LOG_BUFFERING_POLICY _buffering_policy;
	size_t _buffer_capacity;

	LOG_FILE_POLICY _file_policy;
	char _file_dir[__MAX_DIR_SIZE];
	char _filename_format[__MAX_FILENAME_SIZE];
	char _current_filename[__MAX_FILENAME_SIZE];
	size_t _max_file_size;
	bool _is_file_creator;
	bool _has_file_changed;
	size_t _file_iteration;
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

#endif
