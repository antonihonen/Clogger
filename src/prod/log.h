/*
 * File: log.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains the top-level log class of the library.
 * 
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LOG_H
#define LOG_H

#include "flags.h"
#include "file_handler.h"
#include "log_level.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define _DEF_MAX_FSIZE 102400 /* 100 kiB */
#define _DEF_THRESHOLD L_TRACE
#define _DEF_ENTRY_FORMAT "%(MSG)\n"

/* Log. */
typedef struct
{
    fhandler_t* def_fhandler;
    fhandler_t* fhandlers[_VALID_LVL_COUNT];

    format_t* def_formatter;
    format_t* formatters[_VALID_LVL_COUNT];

    LOG_LEVEL threshold;
    bool is_enabled;
    uint16_t flags;
    LOG_ERROR last_error;
} log_t;

log_t* log_init(const char* dname_format,
                const char* fname_format,
                LOG_FILE_MODE file_mode,
                int buf_mode,
                uint16_t flags);

bool log_close(log_t* log);

bool log_enable(log_t* log);

bool log_disable(log_t* log);

void _log_set_error(log_t* log, LOG_ERROR error);

LOG_ERROR log_last_error(log_t* log);

void log_clear_error(log_t* log);

bool log_has_error(log_t* log);

bool log_set_threshold(log_t* log, LOG_LEVEL threshold);

LOG_LEVEL log_threshold(log_t* log);

bool log_set_buf_mode(log_t* log, LOG_LEVEL level, int mode);

int log_buf_mode(log_t* log, LOG_LEVEL level);

bool log_set_buf_size(log_t* log, LOG_LEVEL level, size_t buf_size);

bool log_set_file_mode(log_t* log, LOG_LEVEL level, LOG_FILE_MODE mode);

LOG_FILE_MODE log_file_mode(log_t* log, LOG_LEVEL level);

bool log_set_dname_format(log_t* log, LOG_LEVEL level, const char* format);

char* log_curr_dname(log_t* log, LOG_LEVEL level, char* dest);

bool log_set_fname_format(log_t* log, LOG_LEVEL level, const char* format);

char* log_curr_fname(log_t* log, LOG_LEVEL level, char* dest);

char* log_curr_fpath(log_t* log, LOG_LEVEL level, char* dest);

bool log_set_max_fsize(log_t* log, LOG_LEVEL level, size_t size);

size_t log_max_fsize(log_t* log, LOG_LEVEL level);

size_t log_current_fsize(log_t* log, LOG_LEVEL level);

bool log_set_entry_format(log_t* log, LOG_LEVEL level, const char* format);

bool log_write(log_t* log, LOG_LEVEL level, const char* message);

bool log_trace(log_t* log, const char* message);

bool log_debug(log_t* log, const char* message);

bool log_info(log_t* log, const char* message);

bool log_notice(log_t* log, const char* message);

bool log_warning(log_t* log, const char* message);

bool log_error(log_t* log, const char* message);

bool log_critical(log_t* log, const char* message);

bool log_alert(log_t* log, const char* message);

bool log_emergency(log_t* log, const char* message);

#endif /* LOG_H */
