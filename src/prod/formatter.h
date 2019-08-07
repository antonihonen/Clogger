/*
 * File: formatter.h
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
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
 *   ef_format(ef, expanded_entry, " test message \n", LG_L_TRACE);
 *   // Expanded_entry now contains, for example,
 *   // "01:52:01 TRACE     test message \n";
 *   ef_close(ef);
 *
 * There are more macros than shown above, the full list can be found in
 * format_macro.h.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LG_FORMATTER_H
#define LG_FORMATTER_H

#include "log_level.h"
#include "macros.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define LG_FORMAT_PATHS (1 << 0)
#define LG_FORMAT_ENTRIES (1 << 1)

typedef struct {
    char      format[LG_MAX_ENTRY_SIZE];
    struct tm time;
    uint16_t  flags;
} formatter_t;

formatter_t* formatter_init(formatter_t* buffer, const char* format, uint16_t flags);

bool formatter_set(formatter_t* formatter, const char* format);

char* formatter_get(formatter_t* formatter, char* dest);

char* formatter_path(formatter_t* formatter, char* dest);

char* formatter_entry(formatter_t* formatter,
                      char* dest,
                      const char* msg,
                      LG_LEVEL level);

void formatter_free(formatter_t* formatter);

#endif /* LG_FORMATTER_H */
