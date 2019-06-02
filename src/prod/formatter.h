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

#include "log_level.h"
#include "macros.h"
#include "time_handler.h"
#include <stdint.h>

#define _FORMAT_PATHS 0x01
#define _FORMAT_ENTRIES 0x02

typedef struct {
    char        _format[_MAX_ENTRY_SIZE];
    thandler_t* _thandler;
    uint8_t     _flags;
    struct tm   _time;
} format_t;

format_t* format_init(const char* format, uint8_t flags);

bool format_set(format_t* formatter, const char* format);

char* format_path(format_t* formatter, char* dest);

char* format_entry(format_t* formatter,
                   char* dest,
                   const char* msg,
                   LOG_LEVEL level);

void format_free(format_t* formatter);

#endif /* FORMATTER_H */
