/*
 * File: file_handler.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains a file handler class
 * that can be used to manipulate files.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "error.h"
#include "formatter.h"
#include "macros.h"
#include "policy.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Defines the properties of a file handler object. */
typedef struct {
	FILE* _fstream;
	fn_format_t* _fnf;

	char* _buf;
	size_t _buf_cap;
	int _buf_mode;

	LOG_FILE_POLICY _file_policy;
	size_t _max_file_size;
	bool _is_file_creator;
	bool _has_file_changed;
	size_t _file_iter;
} fhandler_t;

fhandler_t*
fh_init(LOG_BUF_POLICY buf_policy,
	size_t buf_size,
	LOG_FILE_POLICY file_policy,
	char* fn_format,
	size_t max_file_size);

void
fh_close(fhandler_t* fh);

bool
fh_set_buf_policy(fhandler_t* fh, LOG_BUF_POLICY policy);

LOG_BUF_POLICY
fh_buf_policy(fhandler_t* fh);

bool
fh_set_buf_size(fhandler_t* fh, size_t size);

size_t
fh_buf_size(fhandler_t* fh);

bool
fh_set_file_policy(fhandler_t* fh, LOG_FILE_POLICY policy);

LOG_FILE_POLICY
fh_file_policy(fhandler_t* fh);

bool
fh_set_fn_format(fhandler_t* fh, char* format);

bool
fh_set_file_size(fhandler_t* fh, size_t size);

size_t
fh_max_file_size(fhandler_t* fh);

size_t
fh_file_iter(fhandler_t* fh);

bool
fh_write(fhandler_t* fh, char* str);

void
fh_flush_buffer(fhandler_t* fh);

#endif /* FILE_HANDLER_H */
