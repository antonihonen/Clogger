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
        handler_init(&log->handlers[level], level);
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
        handler_free(&log->handlers[level]);
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

bool log_set_user_output(log_t* log, LG_LEVEL level, bool(*user_output)(const char*))
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_user_output_register(&log->handlers[level], user_output);
        }
    }
    else
    {
        handler_user_output_register(&log->handlers[level], user_output);
    }

    return true;
}

bool log_user_output_enable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_user_output_enable(&log->handlers[level]);
        }
    }
    else
    {
        handler_user_output_enable(&log->handlers[level]);
    }

    return true;
}

bool log_user_output_disable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_user_output_disable(&log->handlers[level]);
        }
    }
    else
    {
        handler_user_output_disable(&log->handlers[level]);
    }

    return true;
}

bool log_user_output_enabled(log_t* log, LG_LEVEL level)
{
    if (level == LG_ALL_LEVELS)
    {
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            if (!handler_user_output_enabled(&log->handlers[level]))
            {
                return false;
            }
        }
    }
    else
    {
        return handler_user_output_enabled(&log->handlers[level]);
    }
    return true;
}

bool log_strict_fsize_enable(log_t* log, LG_LEVEL level)
{
    handler_strict_fsize_enable(&log->handlers[level]);
    return true;
}

bool log_strict_fsize_disable(log_t* log, LG_LEVEL level)
{
    handler_strict_fsize_disable(&log->handlers[level]);
    return true;
}

bool log_strict_fsize_enabled(log_t* log, LG_LEVEL level)
{
    return handler_strict_fsize_enabled(&log->handlers[level]);;
}

bool log_stdout_enable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_stdout_enable(&log->handlers[level]);
        }
    }
    else
    {
        handler_stdout_enable(&log->handlers[level]);
    }
    return true;
}

bool log_stdout_disable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_stdout_disable(&log->handlers[level]);
        }
    }
    else
    {
        handler_stdout_disable(&log->handlers[level]);
    }
    return true;
}

bool log_stdout_enabled(log_t* log, LG_LEVEL level)
{
    return handler_stdout_enabled(&log->handlers[level]);
}

bool log_stderr_enable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_stderr_enable(&log->handlers[level]);
        }
    }
    else
    {
        handler_stderr_enable(&log->handlers[level]);
    }
    return true;
}

bool log_stderr_disable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_stderr_disable(&log->handlers[level]);
        }
        return true;
    }
    else
    {
        handler_stderr_disable(&log->handlers[level]);
        return true;
    }
}

bool log_stderr_enabled(log_t* log, LG_LEVEL level)
{
    return handler_stderr_enabled(&log->handlers[level]);
}

bool log_file_enable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_file_enable(&log->handlers[level]);
        }
    }
    else
    {
        handler_file_enable(&log->handlers[level]);
    }
    return true;
}

bool log_file_disable(log_t* log, LG_LEVEL level)
{
    bool success = false;
    bool failed = false;
    if (level == LG_ALL_LEVELS)
    {
        success = true;
        for (level = 0; level < LG_VALID_LVL_COUNT; ++level)
        {
            handler_file_disable(&log->handlers[level]);
        }
        return true;
    }
    else
    {
        handler_file_disable(&log->handlers[level]);
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
            success = handler_file_enabled(&log->handlers[level]);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return handler_file_enabled(&log->handlers[level]);
    }

    return !failed;
}

bool log_set_error(log_t* log, LG_ERRNO error, const char* message)
{
    log->last_error = error;
    strcpy(log->error_msg, message);
}

LG_ERRNO log_get_error(log_t* log)
{
    return log->last_error;
}

bool log_clear_error(log_t* log)
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
            success = handler_set_bmode(&log->handlers[level], mode);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return handler_set_bmode(&log->handlers[level], mode);
    }

    return !failed;
}

int log_bmode(log_t* log, LG_LEVEL level)
{
    return handler_bmode(&log->handlers[level]);
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
            success = handler_set_bsize(&log->handlers[level], buf_size);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return success = handler_set_bsize(&log->handlers[level], buf_size);
    }

    return !failed;
}

size_t log_bsize(log_t* log, LG_LEVEL level)
{
    return handler_bsize(&log->handlers[level]);
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
            success = handler_set_fmode(&log->handlers[level], mode);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return handler_set_fmode(&log->handlers[level], mode);
    }

    return !failed;
}

LG_FMODE log_fmode(log_t* log, LG_LEVEL level)
{
    return handler_fmode(&log->handlers[level]);
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
            success = handler_set_dname_format(&log->handlers[level], format);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return handler_set_dname_format(&log->handlers[level], format);
    }

    return !failed;
}

char* log_dname_format(log_t* log, LG_LEVEL level, char* dest)
{
    if (!log)
    {
        return false;
    }
    return handler_curr_dname(&log->handlers[level], dest);
}

char* log_dname(log_t* log, LG_LEVEL level, char* dest)
{
    return handler_curr_dname(&log->handlers[level], dest);
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
            success = handler_set_fname_format(&log->handlers[level], format);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        handler_set_fname_format(&log->handlers[level], format);
    }

    return !failed;
}

char* log_fname_format(log_t* log, LG_LEVEL level, char* dest)
{
    return handler_curr_fname(&log->handlers[level], dest);
}

char* log_fname(log_t* log, LG_LEVEL level, char* dest)
{
    return handler_curr_fname(&log->handlers[level], dest);
}

char* log_fpath_format(log_t* log, LG_LEVEL level, char* dest)
{
    handler_dname_format(&log->handlers[level], dest);
    strcat(dest, "\\");
    strcat(dest, handler_fname_format(&log->handlers[level], dest + strlen(dest)));
    return dest;
}

char* log_fpath(log_t* log, LG_LEVEL level, char* dest)
{
    return handler_curr_fpath(&log->handlers[level], dest);
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
            success = handler_set_max_fsize(&log->handlers[level], size);
            if (!failed)
            {
                failed = !success;
            }
        }
    }
    else
    {
        return handler_set_max_fsize(&log->handlers[level], size);
    }

    return !failed;
}

size_t log_max_fsize(log_t* log, LG_LEVEL level)
{
    return handler_max_fsize(&log->handlers[level]);
}

size_t log_curr_fsize(log_t* log, LG_LEVEL level)
{
    return handler_current_fsize(&log->handlers[level]);
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
    
    return handler_send(&log->handlers[level], formatted_message);
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
