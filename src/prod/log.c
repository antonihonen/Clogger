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

static log_t* _log_t_alloc(const char* dname_format,
                           const char* fname_format,
                           LOG_FILE_MODE file_mode,
                           int buf_mode);

log_t* log_init(const char* dname_format,
                const char* fname_format,
                LOG_FILE_MODE file_mode,
                int buf_mode)
{
    assert(file_mode == ROTATE || file_mode == REWRITE);
    assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);

    log_t* log = _log_t_alloc(dname_format, fname_format, file_mode, buf_mode);
    if (!log)
    {
        return NULL;
    }

    log->_fh = fh_init(dname_format, fname_format, _DEF_MAX_FSIZE, file_mode,
        buf_mode, BUFSIZ);
    log->_is_enabled = true;
    log->_threshold = _DEF_THRESHOLD;

    return log;
}

bool log_close(log_t* log)
{
    if (log->_fh) { fh_close(log->_fh); }
    if (log->_ef) { ef_close(log->_ef); }
    _log_dealloc(log);
    return true;
}

bool log_enable(log_t* log)
{
    log->_is_enabled = true;
    return true;
}

bool log_disable(log_t* log)
{
    log->_is_enabled = false;
    return true;
}

bool log_set_threshold(log_t* log, LOG_LEVEL threshold)
{
    assert(threshold >= 0 && threshold <= _VALID_LVL_COUNT - 1);
    log->_threshold = threshold;
    return true;
}

LOG_LEVEL log_threshold(log_t* log)
{
    return log->_threshold;
}

bool log_set_buf_mode(log_t* log, int mode)
{
    assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
    return fh_set_buf_mode(log->_fh, mode);
}

int log_buf_mode(log_t* log)
{
    return fh_buf_mode(log->_fh);
}

bool log_set_buf_size(log_t* log, size_t buf_size)
{
    return fh_set_buf_size(log->_fh, buf_size);
}

bool log_set_file_mode(log_t* log, LOG_FILE_MODE mode)
{
    return fh_set_file_mode(log->_fh, mode);
}

LOG_FILE_MODE log_file_mode(log_t* log)
{
    return fh_file_mode(log->_fh);
}

bool log_set_dname_format(log_t* log, const char* format)
{
    return fh_set_dname_format(log->_fh, format);
}

char* log_curr_dname(log_t* log, char* dir)
{
    return fh_curr_dname(log->_fh, dir);
}

bool log_set_fname_format(log_t* log, const char* format)
{
    return fh_set_fname_format(log->_fh, format);
}

char* log_curr_fname(log_t* log, char* filename)
{
    return fh_curr_fname(log->_fh, filename);
}

char* log_curr_fpath(log_t* log, char* filepath)
{
    return fh_curr_fpath(log->_fh, filepath);
}

bool log_set_max_fsize(log_t* log, size_t size)
{
    return fh_set_max_fsize(log->_fh, size);
}

size_t log_max_fsize(log_t* log)
{
    return fh_max_fsize(log->_fh);
}

size_t log_current_fsize(log_t* log)
{
    return 0;
}

bool log_set_entry_format(log_t* log, const char* format)
{
    ef_set_format(log->_ef, format);
    return true;
}

bool log_write(log_t* log, LOG_LEVEL level, const char* message)
{
    char formatted_msg[_MAX_MSG_SIZE];
    ef_format(log->_ef, formatted_msg, message, level);

    if (level >= log->_threshold && log->_is_enabled)
    {
        return fh_fwrite(log->_fh, formatted_msg);
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
                    int buf_mode)
{
    log_t* log = _log_alloc(sizeof(log_t));
    if (!log)
    {
        return NULL;
    }

    log->_fh = fh_init(dname_format,
                       fname_format,
                       _DEF_MAX_FSIZE,
                       file_mode,
                       buf_mode,
                       BUFSIZ);
    log->_ef = ef_init(_DEF_ENTRY_FORMAT);
    if (!log->_fh || !log->_ef)
    {
        log_close(log);
        return NULL;
    }

    return log;
}
