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
 * Example: Creating file names that contain the current date.
 *
 *   fn_formatter_t* fnf = fnf_init("D:\\logs\\log_%(year)_%(month)_%(mday).log");
 *   char expanded_filename[128];
 *   fnf_format(fnf, expanded_filename);
 *   // Expanded_filename now contains, for example,
 *   // "D:\\logs\\log_2020_05_01.log".
 *   fnf_close(fnf);
 *
 * Example: Formatting log entries.
 *
 *   e_formatter_t* ef = ef_init("%(hour):%(min):%(sec) %(LVL) %(msg)");
 *   char expanded_entry[128];
 *   ef_format(ef, expanded_entry, " test message \n", __L_TRACE);
 *   // Expanded_entry now contains, for example,
 *   // "01:52:01 TRACE     test message \n";
 *   ef_close(ef);
 *
 * There are more macros than shown above, the full list can be found in
 * format_macro.h.
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
	/* Format string. */
	char _form[__MAX_FN_FORMAT_SIZE];
	/* Time handler responsible for fetching the current date
	and time for the format macros needing those. */
	thandler_t* _th;
} fn_format_t;

/* Defines the properties of an entry formatter object. */
typedef struct {
	/* as above. */
	char _form[__MAX_E_FORMAT_SIZE];
	/* As above. */
	thandler_t* _th;
} e_format_t;

/* File name formatter functions. */

/* Allocates and initializes a filename formatter with format
as the format string and returns a pointer to the formatter.
Returns NULL if memory allocation fails or if the format string
is too long. */
fn_format_t*
fnf_init(const char* const format);

/* Sets a new format string for the formatter. Returns true if
the format string was valid, false otherwise (contained illegal
macros and/or was too long). */
bool
fnf_set_format(fn_format_t* const fnf, const char* const format);

/* Updates the file name according to the format string
contained by fnf and writes it to formatted_filename. */
void
fnf_format(fn_format_t* const fnf, char* formatted_filename);

/* Deallocates all memory reserved by the formatter.
Must always be called when discarding a formatter.*/
void
fnf_close(fn_format_t* const fnf);

/* Entry formatter functions. */

/* These work in exactly the same way as the fnf
functions above. */

e_format_t*
ef_init(const char* const format);

bool
ef_set_format(e_format_t* const ef, const char* const format);

/* Msg and lvl indicate the message requested to be written and the
level of the request. These are needed here because only an entry
format string is allowed to contain the macros corresponding with
these two. */
void
ef_format(e_format_t* const ef, char* formatted_entry, const char* const msg,
	const LOG_LEVEL lvl);

void
ef_close(e_format_t* const ef);

#endif /* FORMATTER_H */
