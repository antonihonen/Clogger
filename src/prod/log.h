/*
 * File: log.h
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * This module contains the top-level log class of the library.
 * 
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LG_LOG_H
#define LG_LOG_H

#include "flags.h"
#include "handler.h"
#include "log_level.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Log. */
typedef struct
{
    handler_t   handlers[LG_VALID_LVL_COUNT];
    formatter_t formatters[LG_VALID_LVL_COUNT];

    bool        is_enabled[LG_VALID_LVL_COUNT];
    LG_LEVEL    threshold;
    uint64_t    flags;
    LG_ERRNO    last_error;
    char        error_msg[LG_MAX_ERR_MSG_SIZE];

    bool        is_dynamic;
} log_t;

log_t* log_init(log_t* buffer);

bool log_free(log_t* log);

bool log_enable(log_t* log, LG_LEVEL level);

bool log_disable(log_t* log, LG_LEVEL level);

bool log_enabled(log_t* log, LG_LEVEL level);

bool log_set_user_output(log_t* log, LG_LEVEL level, bool(*user_output)(const char*));

bool log_user_output_enable(log_t* log, LG_LEVEL level);

bool log_user_output_disable(log_t* log, LG_LEVEL level);

bool log_user_output_enabled(log_t* log, LG_LEVEL level);

/* TODO */
bool log_fclose_enable(log_t* log, LG_LEVEL level);

/* TODO */
bool log_fclose_disable(log_t* log, LG_LEVEL level);

/* TODO */
bool log_fclose_enabled(log_t* log, LG_LEVEL level);

/* TODO */
bool log_strict_time_enable(log_t* log, LG_LEVEL level);

/* TODO */
bool log_strict_time_disable(log_t* log, LG_LEVEL level);

/* TODO */
bool log_strict_time_enabled(log_t* log, LG_LEVEL level);

bool log_strict_fsize_enable(log_t* log, LG_LEVEL level);

bool log_strict_fsize_disable(log_t* log, LG_LEVEL level);

bool log_strict_fsize_enabled(log_t* log, LG_LEVEL level);

/* TODO */
bool log_flock_enable(log_t* log, LG_LEVEL level);

/* TODO */
bool log_flock_disable(log_t* log, LG_LEVEL level);

/* TODO */
bool log_flock_enabled(log_t* log, LG_LEVEL level);

bool log_stdout_enable(log_t* log, LG_LEVEL level);

bool log_stdout_disable(log_t* log, LG_LEVEL level);

bool log_stdout_enabled(log_t* log, LG_LEVEL level);

bool log_stderr_enable(log_t* log, LG_LEVEL level);

bool log_stderr_disable(log_t* log, LG_LEVEL level);

bool log_stderr_enabled(log_t* log, LG_LEVEL level);

bool log_file_enable(log_t* log, LG_LEVEL level);

bool log_file_disable(log_t* log, LG_LEVEL level);

bool log_file_enabled(log_t* log, LG_LEVEL level);

bool log_set_error(log_t* log, LG_ERRNO error, const char* message);

LG_ERRNO log_get_error(log_t* log);

bool log_has_error(log_t* log);

bool log_clear_error(log_t* log);

bool log_set_threshold(log_t* log, LG_LEVEL level);

LG_LEVEL log_threshold(log_t* log);

bool log_set_bmode(log_t* log, LG_LEVEL level, int mode);

int log_bmode(log_t* log, LG_LEVEL level);

bool log_set_bsize(log_t* log, LG_LEVEL level, size_t buf_size);

size_t log_bsize(log_t* log, LG_LEVEL level);

bool log_set_fmode(log_t* log, LG_LEVEL level, LG_FMODE mode);

LG_FMODE log_fmode(log_t* log, LG_LEVEL level);

bool log_set_dname_format(log_t* log, LG_LEVEL level, const char* dname_format);

/* TODO */
bool log_set_static_dname(log_t* log, LG_LEVEL level, const char* dname);

char* log_dname_format(log_t* log, LG_LEVEL level, char* dest);

char* log_dname(log_t* log, LG_LEVEL level, char* dest);

bool log_set_fname_format(log_t* log, LG_LEVEL level, const char* fname_format);

/* TODO */
bool log_set_static_fname(log_t* log, LG_LEVEL level, const char* fname);

char* log_fname_format(log_t* log, LG_LEVEL level, char* dest);

char* log_fname(log_t* log, LG_LEVEL level, char* dest);

char* log_fpath_format(log_t* log, LG_LEVEL level, char* dest);

char* log_fpath(log_t* log, LG_LEVEL level, char* dest);

bool log_set_max_fsize(log_t* log, LG_LEVEL level, size_t size);

size_t log_max_fsize(log_t* log, LG_LEVEL level);

size_t log_curr_fsize(log_t* log, LG_LEVEL level);

/* TODO */
bool log_set_max_file_iter(log_t* log, size_t iterations);

/* TODO */
size_t log_get_max_file_iter(log_t* log);

/* TODO */
bool log_set_max_file_age(log_t* log, size_t age);

/* TODO */
size_t log_get_max_file_age(log_t* log);

bool log_set_entry_format(log_t* log, LG_LEVEL level, const char* format);

/* TODO */
bool log_set_static_entry_format(log_t* log, LG_LEVEL level, const char* format);

char* log_entry_format(log_t* log, LG_LEVEL level, const char* dest);

bool log_write(log_t* log, LG_LEVEL level, const char* message);

bool log_fwrite(log_t* log, LG_LEVEL level, const char* message);

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
