/*
 * File: log.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "log.h"
#include <assert.h>
#include <string.h>

/* A macro that implements the common part of those setter functions that
make use of the file handler setters. */
#define APPLY_FH_SETTING(log,                                                 \
                         lvl,                                                 \
                         setting_func,                                        \
                         val_type,                                            \
                         setting_val,                                         \
                         success)                                             \
{                                                                             \
    if (log->flags & _PRINT_ONLY)                                             \
    {                                                                         \
        success = false;                                                      \
    }                                                                         \
    else                                                                      \
    {                                                                         \
        if (!_log_create_fhandler_if_none(log, lvl))                          \
        {                                                                     \
            success = false;                                                  \
        }                                                                     \
        else                                                                  \
        {                                                                     \
            setting_func(log->fhandlers[lvl], (val_type)setting_val);         \
            success = true;                                                   \
        }                                                                     \
    }                                                                         \
}

static bool _log_create_formatter_if_none(log_t* log, LOG_LEVEL level);

static bool _log_create_fhandler_if_none(log_t* log, LOG_LEVEL level);

static bool _log_create_formatter(log_t* log, LOG_LEVEL level);

static bool _log_create_fhandler(log_t* log, LOG_LEVEL level);

static inline bool _is_valid_level(LOG_LEVEL level);

static inline bool _is_valid_buf_mode(int mode);

static inline bool _is_valid_file_mode(LOG_FILE_MODE mode);



log_t* log_init(const char* dname_format,
                const char* fname_format,
                LOG_FILE_MODE file_mode,
                int buf_mode,
                uint16_t flags)
{
    assert(_is_valid_file_mode(file_mode));
    assert(_is_valid_buf_mode(buf_mode));

    log_t* log = _log_alloc(sizeof(log_t));
    if (!log)
    {
        return NULL;
    }

    if (!(flags & _PRINT_ONLY))
    {
        /* Create the default file handler. This will be used for all
        request levels until he user asks us to do otherwise. */
        log->def_fhandler = fh_init(dname_format ? dname_format : "",
                                    fname_format ? fname_format : "",
                                    _DEF_MAX_FSIZE,
                                    file_mode,
                                    buf_mode,
                                    BUFSIZ,
                                    flags);
    }
    else
    {
        log->def_fhandler = NULL;
    }

    log->def_formatter = format_init(_DEF_ENTRY_FORMAT, _FORMAT_ENTRIES);

    /* Memory allocation for either the default file handler or the
    entry formatter failed. Release memory. */
    if ((!log->def_fhandler && (flags & _PRINT_ONLY))
         || !log->def_formatter)
    {
        log_close(log);
        return NULL;
    }

    /* Tie each logging level to the default file handler and formatter
    at first. */
    for (size_t i = 0; i < _VALID_LVL_COUNT; ++i)
    {
        log->fhandlers[i] = log->def_fhandler;
        log->formatters[i] = log->def_formatter;
    }

    log->flags = flags;
    log->is_enabled = true;
    log->threshold = _DEF_THRESHOLD;

    return log;
}

bool log_close(log_t* log)
{
    assert(log);

    if (log->def_fhandler)
    {
        fh_free(log->def_fhandler);
    }

    for (size_t i = 0; i < _VALID_LVL_COUNT; ++i)
    {
        if (log->fhandlers[i] != NULL
            && log->fhandlers[i] != log->def_fhandler)
        {
            _log_dealloc(log->fhandlers[i]);
        }
    }

    if (log->def_formatter)
    {
        format_free(log->def_formatter);
    }

    _log_dealloc(log);
    return true;
}

bool log_enable(log_t* log)
{
    assert(log);

    log->is_enabled = true;
    return true;
}

bool log_disable(log_t* log)
{
    assert(log);

    log->is_enabled = false;
    return true;
}

void _log_set_error(log_t* log, LOG_ERROR error)
{
    log->last_error = error;
}

LOG_ERROR log_last_error(log_t* log)
{
    return log->last_error;
}

void log_clear_error(log_t* log)
{
    log->last_error = E_NO_ERROR;
}

bool log_has_error(log_t* log)
{
    if (log->last_error != E_NO_ERROR)
    {
        return true;
    }
}

bool log_set_threshold(log_t* log, LOG_LEVEL threshold)
{
    assert(log);
    assert(_is_valid_level(threshold));

    log->threshold = threshold;
    return true;
}

LOG_LEVEL log_threshold(log_t* log)
{
    assert(log);
    return log->threshold;
}

bool log_set_buf_mode(log_t* log, LOG_LEVEL level, int mode)
{
    assert(log);
    assert(_is_valid_level(level));
    assert(_is_valid_buf_mode(level));

    bool success = false;
    APPLY_FH_SETTING(log, level, fh_set_buf_mode, int, mode, success);
    return success;
}

int log_buf_mode(log_t* log, LOG_LEVEL level)
{
    assert(log);
    assert(_is_valid_level(level));

    if (!log->def_fhandler)
    {
        return _IONBF;
    }

    return fh_buf_mode(log->fhandlers[level]);
}

bool log_set_buf_size(log_t* log, LOG_LEVEL level, size_t buf_size)
{
    assert(log);
    assert(_is_valid_level(level));

    bool success = false;
    APPLY_FH_SETTING(log, level, fh_set_buf_size, size_t, buf_size, success);
    return success;
}

bool log_set_file_mode(log_t* log, LOG_LEVEL level, LOG_FILE_MODE mode)
{
    assert(log);
    assert(_is_valid_level(level));
    assert(_is_valid_file_mode(mode));

    bool success = false;
    APPLY_FH_SETTING(log, level, fh_set_file_mode, LOG_FILE_MODE, mode, success);
    return success;
}

LOG_FILE_MODE log_file_mode(log_t* log, LOG_LEVEL level)
{
    assert(log);
    assert(_is_valid_level(level));

    if (!log->def_fhandler)
    {
        return NO_FILE_MODE;
    }

    return fh_file_mode(log->fhandlers[level]);
}

bool log_set_dname_format(log_t* log, LOG_LEVEL level, const char* format)
{
    assert(log);
    assert(format);
    assert(_is_valid_level(level));

    bool success = false;
    APPLY_FH_SETTING(log, level, fh_set_dname_format, const char*, format, success);
    return success;
}

char* log_curr_dname(log_t* log, LOG_LEVEL level, char* dest)
{
    assert(log);
    assert(dest);
    assert(_is_valid_level(level));

    if (!log)
    {
        return false;
    }
    return fh_curr_dname(log->fhandlers[level], dest);
}

bool log_set_fname_format(log_t* log, LOG_LEVEL level, const char* format)
{
    assert(log);
    assert(format);
    assert(_is_valid_level(level));

    bool success = false;
    APPLY_FH_SETTING(log, level, fh_set_fname_format, const char*, format, success);
    return success;
}

char* log_curr_fname(log_t* log, LOG_LEVEL level, char* dest)
{
    assert(log);
    assert(dest);
    assert(_is_valid_level(level));

    return fh_curr_fname(log->fhandlers[level], dest);
}

char* log_curr_fpath(log_t* log, LOG_LEVEL level, char* dest)
{
    assert(log);
    assert(_is_valid_level(level));
    assert(dest);

    return fh_curr_fpath(log->fhandlers[level], dest);
}

bool log_set_max_fsize(log_t* log, LOG_LEVEL level, size_t size)
{
    assert(log);
    assert(_is_valid_level(level));

    bool success = false;
    APPLY_FH_SETTING(log, level, fh_set_max_fsize, size_t, size, success);
    return success;
}

size_t log_max_fsize(log_t* log, LOG_LEVEL level)
{
    assert(log);
    assert(_is_valid_level(level));

    return fh_max_fsize(log->fhandlers[level]);
}

size_t log_current_fsize(log_t* log, LOG_LEVEL level)
{
    assert(log);
    assert(_is_valid_level(level));

    return fh_current_fsize(log->fhandlers[level]);
}

bool log_set_entry_format(log_t* log, LOG_LEVEL level, const char* format)
{
    assert(log);
    assert(format);
    assert(_is_valid_level(level));

    return format_set(log->formatters[level], format);
}

bool log_write(log_t* log, LOG_LEVEL level, const char* message)
{
    assert(log);
    assert(message);
    assert(_is_valid_level(level));

    char formatted_message[_MAX_MSG_SIZE];
    format_entry(log->formatters[level], formatted_message, message, level);

    if (level >= log->threshold && log->is_enabled)
    {
        if (log->flags & _PRINT || log->flags & _PRINT_ONLY)
        {
            printf(formatted_message);
        }
        if (log->def_fhandler)
        {
            return fh_fwrite(log->fhandlers[level], formatted_message);
        }
    }

    return false;
}

bool log_trace(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_TRACE, message);
}

bool log_debug(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_DEBUG, message);
}

bool log_info(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_INFO, message);
}

bool log_notice(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_NOTICE, message);
}

bool log_warning(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_WARNING, message);
}

bool log_error(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_ERROR, message);
}

bool log_critical(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_CRITICAL, message);
}

bool log_alert(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_ALERT, message);
}

bool log_emergency(log_t* log, const char* message)
{
    assert(log);
    assert(message);

    return log_write(log, L_EMERGENCY, message);
}


/* A helper function that creates a separate formatter
for the request level indicated by lvl if it doesn't have one already. */
bool _log_create_formatter_if_none(log_t* log, LOG_LEVEL level)
{
    if (log->formatters[level] == log->def_formatter)
    {
        return _log_create_fhandler(log, level);
    }
    return true;
}

/* A helper function that creates a separate formatter
for the request level indicated by lvl. */
bool _log_create_formatter(log_t* log, LOG_LEVEL level)
{
    char format[_MAX_E_FORMAT_SIZE];
    log->formatters[level] = format_init(format_get(log->def_formatter,
                                                  format),
                                                  log->flags);
    if (!log->formatters[level])
    {
        log->formatters[level] = log->def_formatter;
        return false;
    }
    return true;
}

/* A helper function that creates a separate file handler
for the request level indicated by lvl if it doesn't have one already. */
bool _log_create_fhandler_if_none(log_t* log, LOG_LEVEL level)
{
    if (log->fhandlers[level] == log->def_fhandler)
    {
        return _log_create_fhandler(log, level);
    }
    return true;
}

/* A helper function that creates a separate file handler
for the request level indicated by lvl. */
bool _log_create_fhandler(log_t* log, LOG_LEVEL level)
{
    char fname_format[_MAX_FILENAME_SIZE];
    char dname_format[_MAX_FILENAME_SIZE];

    /* Create a copy of the default file handler. */
    log->fhandlers[level] = fh_init(fh_dname_format(log->def_fhandler, dname_format),
                                  fh_fname_format(log->def_fhandler, fname_format),
                                  fh_max_fsize(log->def_fhandler),
                                  fh_file_mode(log->def_fhandler),
                                  fh_buf_mode(log->def_fhandler),
                                  fh_buf_size(log->def_fhandler),
                                  log->flags);

    /* Memory allocation failed. Reset to original value. */
    if (!log->fhandlers[level])
    {
        log->fhandlers[level] = log->def_fhandler;
        return false;
    }
    return true;
}

bool _is_valid_level(LOG_LEVEL level)
{
    return (level >= 0) && (level <= _VALID_LVL_COUNT - 1);
}

bool _is_valid_file_mode(LOG_FILE_MODE mode)
{
    return mode == REWRITE || mode == ROTATE;
}

bool _is_valid_buf_mode(int mode)
{
    return mode == _IOFBF || mode == _IOLBF || mode == _IONBF;
}
