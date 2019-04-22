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
	char _fn_format[__MAX_FILENAME_SIZE];
	char _expanded_fn[__MAX_FILENAME_SIZE];
	thandler_t* thandler;
} fn_formatter_t;

/* Defines the properties of an entry formatter object. */
typedef struct {
	char _e_format[__MAX_MSG_SIZE];
	char _e_expanded_format[__MAX_MSG_SIZE];
	thandler_t* thandler;
} e_formatter_t;

/* File name formatter functions. */

LOG_ERROR
fn_formatter_init(fn_formatter_t* formatter, char* fn_format);

LOG_ERROR
fn_formatter_set_format(fn_formatter_t* formatter, char* format);

LOG_ERROR
fn_formatter_format(fn_formatter_t* formatter, char* formatted_filename);

LOG_ERROR
fn_formatter_fn_max_len(fn_formatter_t* formatter, size_t* size);

LOG_ERROR
fn_formatter_close(fn_formatter_t* formatter);

/* Entry formatter functions. */

LOG_ERROR
e_formatter_init(e_formatter_t* formatter, char* format);

LOG_ERROR
e_formatter_set_format(e_formatter_t* formatter, char* format);

LOG_ERROR
e_formatter_format(e_formatter_t* formatter, char* message, char* formatted_entry);

LOG_ERROR
e_formatter_close(e_formatter_t* formatter);

#endif /* FORMATTER_H */
