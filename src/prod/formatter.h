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
	char _form[__MAX_FN_FORMAT_SIZE];
	char _exp_form[__MAX_FILENAME_SIZE];
	thandler_t* _th;
} fn_format_t;

/* Defines the properties of an entry formatter object. */
typedef struct {
	char _form[__MAX_E_FORMAT_SIZE];
	char _exp_form[__MAX_ENTRY_SIZE];
	thandler_t* _th;
} e_format_t;

/* File name formatter functions. */

fn_format_t*
fnf_init(char* format);

bool
fnf_set_format(fn_format_t* fnf, char* format);

void
fnf_format(fn_format_t* fnf, char* formatted_filename);

size_t
fnf_fn_max_len(fn_format_t* fnf);

void
fnf_close(fn_format_t* fnf);

/* Entry formatter functions. */

e_format_t*
ef_init(char* format);

bool
ef_set_format(e_format_t* ef, char* format);

void
ef_format(e_format_t* ef, char* msg, LOG_LEVEL lvl, char* formatted_entry);

void
ef_close(e_format_t* ef);

#endif /* FORMATTER_H */
