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
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define _DEF_MAX_FSIZE 102400 /* 100 kiB */
#define _DEF_THRESHOLD L_TRACE
#define _DEF_ENTRY_FORMAT "%(MSG)\n"

/* Log. */
typedef struct
{
    /* The file handler object that will take care of file writes,
    directory and file naming etc. The log object doesn't need to
    know anything about any of that, it only passes the information
    to the file handler. */
    fhandler_t* _fh;

    /* Entry formatter. Required to expand format macros in log entries. */
    format_t* _ef;

    /* The active threshold level. Any entry with a lower level
    than the threshold level will be ignored. */
    LOG_LEVEL _threshold;

    /* Indicates whether the log object accepts any entries -
    if not, all entries are ignored as if their level
    was lower than the entry threshold. */
    bool _is_enabled;

    uint16_t _flags;
} log_t;

log_t* log_init(const char* dname_format,
                const char* fname_format,
                LOG_FILE_MODE file_mode,
                int buf_mode,
                uint16_t flags);

bool log_close(log_t* log);

bool log_enable(log_t* log);

bool log_disable(log_t* log);

bool log_set_threshold(log_t* log, LOG_LEVEL threshold);

LOG_LEVEL log_threshold(log_t* log);

bool log_set_buf_mode(log_t* log, int mode);

int log_buf_mode(log_t* log);

bool log_set_buf_size(log_t* log, size_t buf_size);

bool log_set_file_mode(log_t* log, LOG_FILE_MODE mode);

LOG_FILE_MODE log_file_mode(log_t* log);

bool log_set_dname_format(log_t* log, const char* format);

char* log_curr_dname(log_t* log, char* dest);

bool log_set_fname_format(log_t* log, const char* format);

char* log_curr_fname(log_t* log, char* dest);

char* log_curr_fpath(log_t* log, char* dest);

bool log_set_max_fsize(log_t* log, size_t size);

size_t log_max_fsize(log_t* log);

size_t log_current_fsize(log_t* log);

bool log_set_entry_format(log_t* log, const char* format);

bool log_write(log_t* log, LOG_LEVEL level, const char* msg);

bool log_trace(log_t* log, const char* msg);

bool log_debug(log_t* log, const char* msg);

bool log_info(log_t* log, const char* msg);

bool log_warning(log_t* log, const char* msg);

bool log_error(log_t* log, const char* msg);

bool log_critical(log_t* log, const char* msg);

#endif /* LOG_H */
