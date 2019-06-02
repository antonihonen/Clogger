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

static log_t* _log_t_alloc(const char* dname_format,
                           const char* fname_format,
                           LOG_FILE_MODE file_mode,
                           int buf_mode,
                           uint16_t flags);

log_t* log_init(const char* dname_format,
                const char* fname_format,
                LOG_FILE_MODE file_mode,
                int buf_mode,
                uint16_t flags)
{
    assert(file_mode == ROTATE || file_mode == REWRITE);
    assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);

    log_t* log = _log_t_alloc(dname_format,
                              fname_format,
                              file_mode,
                              buf_mode,
                              flags);
    if (!log)
    {
        return NULL;
    }

    log->flags = flags;
    log->is_enabled = true;
    log->threshold = _DEF_THRESHOLD;

    return log;
}

bool log_close(log_t* log)
{
    if (log->fh) { fh_free(log->fh);     }
    if (log->ef) { format_free(log->ef); }
    _log_dealloc(log);
    return true;
}

bool log_enable(log_t* log)
{
    log->is_enabled = true;
    return true;
}

bool log_disable(log_t* log)
{
    log->is_enabled = false;
    return true;
}

bool log_set_threshold(log_t* log, LOG_LEVEL threshold)
{
    assert(threshold >= 0 && threshold <= _VALID_LVL_COUNT - 1);
    log->threshold = threshold;
    return true;
}

LOG_LEVEL log_threshold(log_t* log)
{
    return log->threshold;
}

bool log_set_buf_mode(log_t* log, int mode)
{
    assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
    if (!log->fh)
    {
        return false;
    }
    return fh_set_buf_mode(log->fh, mode);
}

int log_buf_mode(log_t* log)
{
    if (!log->fh)
    {
        return _IONBF;
    }
    return fh_buf_mode(log->fh);
}

bool log_set_buf_size(log_t* log, size_t buf_size)
{
    if (!log->fh)
    {
        return false;
    }
    return fh_set_buf_size(log->fh, buf_size);
}

bool log_set_file_mode(log_t* log, LOG_FILE_MODE mode)
{
    if (!log->fh)
    {
        return false;
    }
    return fh_set_file_mode(log->fh, mode);
}

LOG_FILE_MODE log_file_mode(log_t* log)
{
    if (!log->fh)
    {
        return NO_FILE_MODE;
    }
    return fh_file_mode(log->fh);
}

bool log_set_dname_format(log_t* log, const char* format)
{
    if (!log->fh)
    {
        return false;
    }
    return fh_set_dname_format(log->fh, format);
}

char* log_curr_dname(log_t* log, char* dir)
{
    if (!log)
    {
        return false;
    }
    return fh_curr_dname(log->fh, dir);
}

bool log_set_fname_format(log_t* log, const char* format)
{
    if (!log)
    {
        return false;
    }
    return fh_set_fname_format(log->fh, format);
}

char* log_curr_fname(log_t* log, char* filename)
{
    if (!log)
    {
        strcpy(filename, "");
        return filename;
    }
    return fh_curr_fname(log->fh, filename);
}

char* log_curr_fpath(log_t* log, char* filepath)
{
    if (!log)
    {
        strcpy(filepath, "");
        return filepath;
    }
    return fh_curr_fpath(log->fh, filepath);
}

bool log_set_max_fsize(log_t* log, size_t size)
{
    if (!log)
    {
        return false;
    }
    return fh_set_max_fsize(log->fh, size);
}

size_t log_max_fsize(log_t* log)
{
    if (!log)
    {
        return 0;
    }
    return fh_max_fsize(log->fh);
}

size_t log_current_fsize(log_t* log)
{
    if (!log)
    {
        return 0;
    }
    return fh_current_fsize(log->fh);
}

bool log_set_entry_format(log_t* log, const char* format)
{
    format_set(log->ef, format);
    return true;
}

bool log_write(log_t* log, LOG_LEVEL level, const char* message)
{
    char formatted_msg[_MAX_MSG_SIZE];
    format_entry(log->ef, formatted_msg, message, level);

    if (level >= log->threshold && log->is_enabled)
    {
        if (log->flags & _PRINT)
        {
            printf(formatted_msg);
        }
        if (log->fh)
        {
            return fh_fwrite(log->fh, formatted_msg);
        }
    }

    return false;
}

bool log_trace(log_t* log, const char* message)
{
    return log_write(log, L_TRACE, message);
}

bool log_debug(log_t* log, const char* message)
{
    return log_write(log, L_DEBUG, message);
}

bool log_info(log_t* log, const char* message)
{
    return log_write(log, L_INFO, message);
}

bool log_warning(log_t* log, const char* message)
{
    return log_write(log, L_WARNING, message);
}

bool log_error(log_t* log, const char* message)
{
    return log_write(log, L_ERROR, message);
}

bool log_critical(log_t* log, const char* message)
{
    return log_write(log, L_CRITICAL, message);
}

log_t* _log_t_alloc(const char* dname_format,
                    const char* fname_format,
                    LOG_FILE_MODE file_mode,
                    int buf_mode,
                    uint16_t flags)
{
    log_t* log = _log_alloc(sizeof(log_t));
    if (!log)
    {
        return NULL;
    }
    if (!(flags & _PRINT_ONLY))
    {
        log->fh = fh_init(dname_format,
            fname_format,
            _DEF_MAX_FSIZE,
            file_mode,
            buf_mode,
            BUFSIZ,
            flags);
    }
    else
    {
        log->fh = NULL;
    }
    log->ef = format_init(_DEF_ENTRY_FORMAT, _FORMAT_ENTRIES);
    if ((!log->fh && (flags & _PRINT_ONLY)) || !log->ef)
    {
        log_close(log);
        return NULL;
    }

    return log;
}
