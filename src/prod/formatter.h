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
 *   ef_format(ef, expanded_entry, " test message \n", _L_TRACE);
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

/* Filename formatter. */
typedef struct {
    /* Format string. */
    char _form[_MAX_FN_FORMAT_SIZE];
    /* Time handler responsible for fetching the current date
    and time for the format macros needing those. */
    thandler_t* _th;
} fn_format_t;

/* Entry formatter. */
typedef struct {
    /* As above. */
    char _form[_MAX_E_FORMAT_SIZE];
    /* As above. */
    thandler_t* _th;
} e_format_t;

fn_format_t* fnf_init(const char* format);

bool fnf_set_format(fn_format_t* const fnf, const char* format);

void fnf_format(fn_format_t* fnf, char* dest);

void fnf_close(fn_format_t* fnf);

e_format_t* ef_init(const char* format);

bool ef_set_format(e_format_t* const ef, const char* format);

void ef_format(e_format_t* ef, char* dest, const char* src, LOG_LEVEL lvl);

void ef_close(e_format_t* ef);

#endif /* FORMATTER_H */
