/*
 * File: formatter.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file defines two formatter classes that are responsible
 * for formatting file names and log entries respectively.
 * These formatters are needed because both file names and
 * log entries can be formatted by the user using format macros that
 * need to be expanded - these classes do that.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef FORMATTER_H
#define FORMATTER_H

#include "format_macro.h"
#include "macros.h"
#include "time_handler.h"

/* Defines the properties of a filename formatter object. */
typedef struct {
	char _form[__MAX_FILENAME_SIZE];
	char _exp_form[__MAX_FILENAME_SIZE];
	thandler_t* _thandler;
} fn_format_t;

/* Defines the properties of an entry formatter object. */
typedef struct {
	char _form[__MAX_MSG_SIZE];
	char _exp_form[__MAX_MSG_SIZE];
	thandler_t* _thandler;
} e_format_t;

/* File name formatter functions. */

fn_format_t*
fnf_init(char* fn_format);

LOG_ERROR
fnf_set_format(fn_format_t* formatter, char* format);

LOG_ERROR
fnf_format(fn_format_t* formatter, char* formatted_filename);

LOG_ERROR
fnf_fn_max_len(fn_format_t* formatter, size_t* size);

LOG_ERROR
fnf_close(fn_format_t* formatter);

/* Entry formatter functions. */

e_format_t*
ef_init(char* format);

LOG_ERROR
ef_set_format(e_format_t* formatter, char* format);

LOG_ERROR
ef_format(e_format_t* formatter, char* message, char* formatted_entry);

LOG_ERROR
ef_close(e_format_t* formatter);

#endif /* FORMATTER_H */
