/*
 * File: log.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains the top-level log class of the library.
 * 
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LG_LOG_H
#define LG_LOG_H

#include "flags.h"
#include "file_handler.h"
#include "log_level.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Log. */
typedef struct
{
    fhandler_t* def_fhandler;
    fhandler_t* fhandlers[LG_VALID_LVL_COUNT];

    format_t*   def_formatter;
    format_t*   formatters[LG_VALID_LVL_COUNT];

    LG_LEVEL    threshold;
    bool        is_enabled;
    uint64_t    flags;
    LG_ERRNO    last_error;
} log_t;

log_t* log_init(const char* dname_format,
                const char* fname_format,
                LG_FMODE file_mode,
                int buf_mode,
                uint64_t flags);

bool log_close(log_t* log);

bool log_enable(log_t* log);

bool log_disable(log_t* log);

void log_set_error(log_t* log, LG_ERRNO error);

LG_ERRNO log_get_error(log_t* log);

bool log_has_error(log_t* log);

void log_clear_error(log_t* log);

bool log_set_threshold(log_t* log, LG_LEVEL level);

LG_LEVEL log_threshold(log_t* log);

bool log_set_bmode(log_t* log, LG_LEVEL level, int mode);

int log_bmode(log_t* log, LG_LEVEL level);

bool log_set_bsize(log_t* log, LG_LEVEL level, size_t buf_size);

bool log_set_fmode(log_t* log, LG_LEVEL level, LG_FMODE mode);

LG_FMODE log_fmode(log_t* log, LG_LEVEL level);

bool log_set_dname(log_t* log, LG_LEVEL level, const char* format);

char* log_curr_dname(log_t* log, LG_LEVEL level, char* dest);

bool log_set_fname(log_t* log, LG_LEVEL level, const char* format);

char* log_curr_fname(log_t* log, LG_LEVEL level, char* dest);

char* log_curr_fpath(log_t* log, LG_LEVEL level, char* dest);

bool log_set_max_fsize(log_t* log, LG_LEVEL level, size_t size);

size_t log_max_fsize(log_t* log, LG_LEVEL level);

size_t log_curr_fsize(log_t* log, LG_LEVEL level);

bool log_set_format(log_t* log, LG_LEVEL level, const char* format);

bool log_write(log_t* log, LG_LEVEL level, const char* message);

bool log_trace(log_t* log, const char* message);

bool log_debug(log_t* log, const char* message);

bool log_info(log_t* log, const char* message);

bool log_notice(log_t* log, const char* message);

bool log_warning(log_t* log, const char* message);

bool log_error(log_t* log, const char* message);

bool log_critical(log_t* log, const char* message);

bool log_alert(log_t* log, const char* message);

bool log_emergency(log_t* log, const char* message);

bool log_fatal(log_t* log, const char* message);

#endif /* LG_LOG_H */
