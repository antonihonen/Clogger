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
	fn_format_t* _dirnf;
	char _cur_fp[__MAX_FILENAME_SIZE];
	char _cur_dirn[__MAX_FILENAME_SIZE];

	char* _buf;
	size_t _buf_cap;
	int _buf_mode;

	LOG_FILE_POLICY _file_mode;
	size_t _max_fsize;
	bool _is_file_creator;
	bool _has_file_changed;
} fhandler_t;

fhandler_t*
fh_init(char* dirn_form,
	char* fn_form,
	size_t max_fsize,
	LOG_FILE_POLICY file_mode,
	int buf_mode,
	size_t bufsize);

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
