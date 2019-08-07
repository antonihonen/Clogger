/*
 * File: log.c
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "log.h"
#include <assert.h>
#include <string.h>

log_t * log_init(log_t* buffer)
{
    log_t* log = buffer;

    if (!log)
    {
        log = LG_alloc(sizeof(log_t));
        if (!log)
        {
            return NULL;
        }
        log->is_dynamic = true;
    }
    else
    {
        log->is_dynamic = false;
    }

    for (size_t level = 0; level < LG_VALID_LVL_COUNT; ++level)
    {
        fh_init(&log->fhandlers[level], level);
        formatter_init(&log->formatters[level], LG_DEF_ENTRY_FORMAT, LG_FORMAT_ENTRIES);
        log->is_enabled[level] = true;
    }

    log->threshold = LG_DEF_THRESHOLD;
    log->flags = 0;
    log->last_error = LG_E_NO_ERROR;
    log->error_msg[0] = '\0';

    return log;
}

bool log_free(log_t* log)
{
    for (size_t level = 0; level < LG_VALID_LVL_COUNT; ++level)
    {
        fh_free(&log->fhandlers[level]);
        formatter_free(&log->formatters[level]);
    }

    if (log->is_dynamic)
    {
        LG_dealloc(log);
    }

    return true;
}

bool log_enable(log_t* log, LG_LEVEL level)
{
    if (level == LG_ALL_LEVELS)
    {
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            log->is_enabled[level] = true;
        }
    }
    else
    {
        log->is_enabled[level] = true;
    }
    return true;
}

bool log_disable(log_t* log, LG_LEVEL level)
{
    if (level == LG_ALL_LEVELS)
    {
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            log->is_enabled[level] = false;
        }
    }
    else
    {
        log->is_enabled[level] = false;
    }
    return true;
}

bool log_enabled(log_t* log, LG_LEVEL level)
{
    if (level == LG_ALL_LEVELS)
    {
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            if (!log->is_enabled[level])
            {
                return false;
            }
        }
    }
    else
    {
        return log->is_enabled[level];
    }
    return true;
}

bool log_enable_stdout(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            fh_enable_stdout(&log->fhandlers[level]);
        }
    }
    else
    {
        fh_enable_stdout(&log->fhandlers[level]);
    }
    return true;
}

bool log_disable_stdout(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            fh_disable_stdout(&log->fhandlers[level]);
        }
    }
    else
    {
        fh_disable_stdout(&log->fhandlers[level]);
    }
    return true;
}

bool log_stdout_enabled(log_t* log, LG_LEVEL level)
{
    return fh_stdout_enabled(&log->fhandlers[level]);
}

bool log_enable_stderr(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            fh_enable_stderr(&log->fhandlers[level]);
        }
    }
    else
    {
        fh_enable_stderr(&log->fhandlers[level]);
    }
    return true;
}

bool log_disable_stderr(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            fh_disable_stderr(&log->fhandlers[level]);
        }
        return true;
    }
    else
    {
        fh_disable_stderr(&log->fhandlers[level]);
        return true;
    }
}

bool log_stderr_enabled(log_t* log, LG_LEVEL level)
{
    return fh_stderr_enabled(&log->fhandlers[level]);
}

bool log_enable_file(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            fh_enable_file(&log->fhandlers[level]);
        }
    }
    else
    {
        fh_enable_file(&log->fhandlers[level]);
    }
    return true;
}

bool log_disable_file(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            fh_disable_file(&log->fhandlers[level]);
        }
        return true;
    }
    else
    {
        fh_disable_file(&log->fhandlers[level]);
        return true;
    }

    return !failed;
}

bool log_file_enabled(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = fh_file_enabled(&log->fhandlers[level]);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return fh_file_enabled(&log->fhandlers[level]);
    }

    return !failed;
}

void log_set_error(log_t* log, LG_ERRNO error, const char* message)
{
    log->last_error = error;
    strcpy(log->error_msg, message);
}

LG_ERRNO log_get_error(log_t* log)
{
    return log->last_error;
}

void log_clear_error(log_t* log)
{
    log->last_error = LG_E_NO_ERROR;
}

bool log_has_error(log_t* log)
{
    return log->last_error != LG_E_NO_ERROR;
}

bool log_set_threshold(log_t* log, LG_LEVEL threshold)
{
    log->threshold = threshold;
    return true;
}

LG_LEVEL log_threshold(log_t* log)
{
    return log->threshold;
}

bool log_set_bmode(log_t* log, LG_LEVEL level, int mode)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = fh_set_bmode(&log->fhandlers[level], mode);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return fh_set_bmode(&log->fhandlers[level], mode);
    }

    return !failed;
}

int log_bmode(log_t* log, LG_LEVEL level)
{
    return fh_bmode(&log->fhandlers[level]);
}

bool log_set_bsize(log_t* log, LG_LEVEL level, size_t buf_size)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = fh_set_bsize(&log->fhandlers[level], buf_size);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return success = fh_set_bsize(&log->fhandlers[level], buf_size);
    }

    return !failed;
}

size_t log_bsize(log_t* log, LG_LEVEL level)
{
    return fh_bsize(&log->fhandlers[level]);
}

bool log_set_fmode(log_t* log, LG_LEVEL level, LG_FMODE mode)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = fh_set_fmode(&log->fhandlers[level], mode);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return fh_set_fmode(&log->fhandlers[level], mode);
    }

    return !failed;
}

LG_FMODE log_fmode(log_t* log, LG_LEVEL level)
{
    return fh_fmode(&log->fhandlers[level]);
}

bool log_set_dname_format(log_t* log, LG_LEVEL level, const char* format)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = fh_set_dname_format(&log->fhandlers[level], format);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return fh_set_dname_format(&log->fhandlers[level], format);
    }

    return !failed;
}

char* log_dname_format(log_t* log, LG_LEVEL level, char* dest)
{
    if (!log)
    {
        return false;
    }
    return fh_curr_dname(&log->fhandlers[level], dest);
}

char* log_dname(log_t* log, LG_LEVEL level, char* dest)
{
    return fh_curr_dname(&log->fhandlers[level], dest);
}

bool log_set_fname_format(log_t* log, LG_LEVEL level, const char* format)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = fh_set_fname_format(&log->fhandlers[level], format);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        fh_set_fname_format(&log->fhandlers[level], format);
    }

    return !failed;
}

char* log_fname_format(log_t* log, LG_LEVEL level, char* dest)
{
    return fh_curr_fname(&log->fhandlers[level], dest);
}

char* log_fname(log_t* log, LG_LEVEL level, char* dest)
{
    return fh_curr_fname(&log->fhandlers[level], dest);
}

char* log_fpath_format(log_t* log, LG_LEVEL level, char* dest)
{
    fh_dname_format(&log->fhandlers[level], dest);
    strcat(dest, "\\");
    strcat(dest, fh_fname_format(&log->fhandlers[level], dest + strlen(dest)));
    return dest;
}

char* log_fpath(log_t* log, LG_LEVEL level, char* dest)
{
    return fh_curr_fpath(&log->fhandlers[level], dest);
}

bool log_set_max_fsize(log_t* log, LG_LEVEL level, size_t size)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = fh_set_max_fsize(&log->fhandlers[level], size);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return fh_set_max_fsize(&log->fhandlers[level], size);
    }

    return !failed;
}

size_t log_max_fsize(log_t* log, LG_LEVEL level)
{
    return fh_max_fsize(&log->fhandlers[level]);
}

size_t log_curr_fsize(log_t* log, LG_LEVEL level)
{
    return fh_current_fsize(&log->fhandlers[level]);
}

bool log_set_entry_format(log_t* log, LG_LEVEL level, const char* format)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            success = formatter_set(&log->formatters[level], format);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        failed = !formatter_set(&log->formatters[level], format);
    }

    return !failed;
}

char* log_entry_format(log_t* log, LG_LEVEL level, const char* dest)
{
    return formatter_get(&log->formatters[level], dest);
}

bool log_write(log_t* log, LG_LEVEL level, const char* message)
{
    if (level >= log->threshold && log->is_enabled[level])
    {
        return log_fwrite(log, level, message);
    }

    return false;
}

bool log_fwrite(log_t* log, LG_LEVEL level, const char* message)
{
    char formatted_message[LG_MAX_MSG_SIZE];
    formatter_entry(&log->formatters[level], formatted_message, message, level);
    printf(formatted_message);
    return fh_fwrite(&log->fhandlers[level], formatted_message);
}

bool log_trace(log_t* log, const char* message)
{
    return log_write(log, LG_TRACE, message);
}

bool log_debug(log_t* log, const char* message)
{
    return log_write(log, LG_DEBUG, message);
}

bool log_info(log_t* log, const char* message)
{
    return log_write(log, LG_INFO, message);
}

bool log_notice(log_t* log, const char* message)
{
    return log_write(log, LG_NOTICE, message);
}

bool log_warning(log_t* log, const char* message)
{
    return log_write(log, LG_WARNING, message);
}

bool log_error(log_t* log, const char* message)
{
    return log_write(log, LG_ERROR, message);
}

bool log_critical(log_t* log, const char* message)
{
    return log_write(log, LG_CRITICAL, message);
}

bool log_alert(log_t* log, const char* message)
{
    return log_write(log, LG_ALERT, message);
}

bool log_emergency(log_t* log, const char* message)
{
    return log_write(log, LG_EMERGENCY, message);
}

bool log_fatal(log_t* log, const char* message)
{
    return log_write(log, LG_FATAL, message);
}
