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

#define __DEF_BUF_SIZE BUFSIZ

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

	LOG_FILE_MODE _file_mode;
	size_t _max_fsize;
	bool _is_dir_creator;
	bool _is_file_creator;
	bool _has_file_changed;
} fhandler_t;

fhandler_t*
fh_init(const char* const dirn_form,
	const char* const fn_form,
	const size_t max_fsize,
	const LOG_FILE_MODE file_mode,
	const int buf_mode,
	size_t bufsize);

void
fh_close(fhandler_t* const fh);

bool
fh_set_buf_mode(fhandler_t* const fh, const int mode);

int
fh_buf_mode(const fhandler_t* const fh);

bool
fh_set_buf_size(fhandler_t* const fh, const size_t size);

size_t
fh_buf_size(const fhandler_t* const fh);

bool
fh_set_file_mode(fhandler_t* const fh, const LOG_FILE_MODE mode);

LOG_FILE_MODE
fh_file_mode(const fhandler_t* const fh);

bool
fh_set_fn_format(fhandler_t* const fh, const char* const format);

bool
fh_set_max_fsize(fhandler_t* const fh, const size_t size);

size_t
fh_max_fsize(const fhandler_t* const fh);

bool
fh_write(fhandler_t* fh, const char* const data_out);

#endif /* FILE_HANDLER_H */
