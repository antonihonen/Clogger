/*
 * File: file_handler.c
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "flags.h"
#include "handler.h"
#include "macros.h"
#include "os.h"
#include "string_util.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool   _handler_stdout_write(handler_t* handler, const char* data_out);
static bool   _handler_stderr_write(handler_t* handler, const char* data_out);
static bool   _handler_file_write  (handler_t* handler, const char* data_out);
static void   _handler_refresh_path(handler_t* handler);
static bool   _rotate_files        (const char* abs_filepath);
static void   _handler_deploy_file (handler_t* handler);
static void   _handler_close_file  (handler_t* handler);
static fpos_t _handler_file_size   (handler_t* handler);

/* Allocates and initializes a new handler_t object and returns
a pointer to it. */
handler_t* handler_init(handler_t* buffer, LG_LEVEL level)
{
    handler_t* handler = buffer;
    if (!handler)
    {
        /* Allocate memory. */
        handler = handler = LG_alloc(sizeof(handler_t));
        if (!handler)
        {
            return NULL;
        }
        handler->is_dynamic = true;
    }
    else
    {
        handler->is_dynamic = false;
    }

    /* Finish initialization. */
    formatter_init(&handler->dname_formatter, "", LG_FORMAT_PATHS);
    formatter_init(&handler->fname_formatter, "", LG_FORMAT_PATHS);

    handler->bmode = _IOFBF;
    handler->fstream = NULL;
    handler->bsize = LG_DEF_BSIZE;
    handler->fmode = LG_FMODE_NONE;
    handler->has_file_changed = false;
    handler->is_file_creator = false;
    handler->is_dir_creator = false;
    handler->has_dir_changed = false;
    handler->max_fsize = LG_DEF_MAX_FSIZE;
    handler->curr_fsize = 0;
    handler->flags = 0;
    handler->is_enabled = true;
    handler->is_strict_time_enabled = false;
    handler->is_flock_enabled = false;
    handler->is_file_enabled = false;
    handler->is_stdout_enabled = false;
    handler->is_stderr_enabled = false;
    handler->curr_fname[0] = '\0';
    handler->curr_dname[0] = '\0';
    handler->curr_fpath[0] = '\0';

    setvbuf(stdout, handler->stdout_buf, handler->bmode, handler->bsize);

    return handler;
}

/* Frees the memory reserved for handler and its sub-objects. */
void handler_free(handler_t* handler)
{
    formatter_free(&handler->dname_formatter);
    formatter_free(&handler->fname_formatter);
    if (handler->fstream) { fclose(handler->fstream); }

    if (handler->is_dynamic)
    {
        LG_dealloc(handler);
    }
}

void handler_enable(handler_t* handler)
{
    handler->is_enabled = true;
}

void handler_disable(handler_t* handler)
{
    handler->is_enabled = false;
}

bool handler_enabled(handler_t* handler)
{
    return handler->is_enabled;
}

bool handler_user_output_register(handler_t* handler,
                                  bool (*user_output)(const char*))
{
    handler->user_output = user_output;
    return true;
}

void handler_user_output_enable(handler_t* handler)
{
    handler->is_user_output_enabled = true;
}

void handler_user_output_disable(handler_t* handler)
{
    handler->is_user_output_enabled = false;
}

bool handler_user_output_enabled(handler_t* handler)
{
    return handler->is_user_output_enabled;
}

void handler_strict_fsize_enable(handler_t* handler)
{
    handler->is_strict_fsize_enabled = true;
}

void handler_strict_fsize_disable(handler_t* handler)
{
    handler->is_strict_fsize_enabled = false;
}

bool handler_strict_fsize_enabled(handler_t* handler)
{
    return handler->is_strict_fsize_enabled;
}

void handler_strict_time_enable(handler_t* handler)
{
    handler->is_strict_time_enabled = true;
}

void handler_strict_time_disable(handler_t* handler)
{
    handler->is_strict_time_enabled = false;
}

bool handler_strict_time_enabled(handler_t* handler)
{
    return handler->is_strict_time_enabled;
}

void handler_flock_enable(handler_t* handler)
{
    handler->is_flock_enabled = true;
}

void handler_flock_disable(handler_t* handler)
{
    handler->is_flock_enabled = true;
}

bool handler_flock_enabled(handler_t* handler)
{
    return handler->is_flock_enabled;
}

void handler_file_enable(handler_t* handler)
{
    handler->is_file_enabled = true;
}

void handler_file_disable(handler_t* handler)
{
    handler->is_file_enabled = false;
}

bool handler_file_enabled(handler_t* handler)
{
    return handler->is_file_enabled;
}

void handler_stdout_enable(handler_t* handler)
{
    handler->is_stdout_enabled = true;
}

void handler_stdout_disable(handler_t* handler)
{
    handler->is_stdout_enabled = false;
}

bool handler_stdout_enabled(handler_t* handler)
{
    return handler->is_stdout_enabled;
}

void handler_stderr_enable(handler_t* handler)
{
    handler->is_stderr_enabled = true;
}

void handler_stderr_disable(handler_t* handler)
{
    handler->is_stderr_enabled = false;
}

bool handler_stderr_enabled(handler_t* handler)
{
    return handler->is_stderr_enabled;
}

void handler_set_error(handler_t* handler, LG_ERRNO error, const char* message)
{
    handler->last_error = error;
    strcpy(handler->error_msg, message);
}

LG_ERRNO handler_get_error(handler_t* handler)
{
    return handler->last_error;
}

bool handler_has_error(handler_t* handler)
{
    return handler->last_error != LG_E_NO_ERROR;
}

void handler_clear_error(handler_t* handler)
{
    handler->last_error = LG_E_NO_ERROR;
    handler->error_msg[0] = '\0';
}

bool handler_set_bmode(handler_t* handler, int mode)
{
    assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
    
    if (handler->bmode == mode)
    {
        return true;
    }

    if (mode == _IONBF)
    {
        handler->bsize = 0;
    }
    
    handler->bmode = mode;
    return true;
}

int handler_bmode(const handler_t* handler)
{
    return handler->bmode;
}

bool handler_set_bsize(handler_t* handler, size_t size)
{
    if (handler->bsize == size)
    {
        return true;
    }
    else if (size == 0)
    {
        handler->bmode = _IONBF;
    }

    handler->bsize = size;
    return true;
}

size_t handler_bsize(const handler_t* handler)
{
    return handler->bsize;
}

bool handler_set_fmode(handler_t* handler, LG_FMODE mode)
{
    assert(mode == LG_FMODE_ROTATE || mode == LG_FMODE_REWRITE);
    handler->fmode = mode;
    return true;
}

LG_FMODE handler_fmode(const handler_t* handler)
{
    return handler->fmode;
}

bool handler_set_fname_format(handler_t* handler, const char* format)
{
    if (!formatter_set(&handler->fname_formatter, format))
    {
        return false;
    }
    _handler_refresh_path(handler);
    return true;
}

char* handler_fname_format(handler_t* handler, char* dest)
{
    formatter_get(&handler->fname_formatter, dest);
    return dest;
}

char* handler_curr_fname(const handler_t* handler, char* dest)
{
    strcpy(dest, handler->curr_fname);
    return dest;
}

char* handler_curr_dname(const handler_t* handler, char* dest)
{
    strcpy(dest, handler->curr_dname);
    return dest;
}

char* handler_curr_fpath(const handler_t* handler, char* dest)
{
    strcpy(dest, handler->curr_fpath);
    return dest;
}

bool handler_set_dname_format(handler_t* handler, const char* format)
{
    if (!formatter_set(&handler->dname_formatter, format))
    {
        return false;
    }
    _handler_refresh_path(handler);
    return true;
}

char* handler_dname_format(handler_t* handler, char* dest)
{
    formatter_get(&handler->dname_formatter, dest);
    return dest;
}

bool handler_set_max_fsize(handler_t* handler, size_t size)
{
    handler->max_fsize = size;
    return true;
}

size_t handler_max_fsize(const handler_t* handler)
{
    return handler->max_fsize;
}

size_t handler_current_fsize(const handler_t* handler)
{
    return handler->curr_fsize;
}

bool handler_send(handler_t* handler, const char* data_out)
{
    if (!handler->is_enabled)
    {
        return false;
    }

    if (handler->is_file_enabled)
    {
        _handler_file_write(handler, data_out);
    }
    if (handler->is_stdout_enabled)
    {
        _handler_stdout_write(handler, data_out);
    }
    if (handler->is_stderr_enabled)
    {
        _handler_stderr_write(handler, data_out);
    }
    if (handler->is_user_output_enabled)
    {
        handler->user_output(data_out);
    }

    return true;
}

bool _handler_stdout_write(handler_t* handler, const char* data_out)
{
    return fputs(data_out, stdout);
}

bool _handler_stderr_write(handler_t* handler, const char* data_out)
{
    return fputs(data_out, stderr);
}

bool _handler_file_write(handler_t* handler, const char* data_out)
{
    if (!handler->is_file_enabled)
    {
        return false;
    }

    if (!handler->fstream)
    {
        _handler_deploy_file(handler);
    }

    fpos_t data_size = 0;
    if (handler->is_strict_fsize_enabled)
    {
        data_size = strlen(data_out);
        if (strlen(data_out) + handler->curr_fsize >= handler->max_fsize)
        {
            _handler_close_file(handler);
            _handler_deploy_file(handler);
        }
    }
    else
    {
        if (_handler_file_size(handler) >= handler->max_fsize)
        {
            _handler_close_file(handler);
            _handler_deploy_file(handler);
        }
    }

    if (!handler->fstream) { return false; }

    /* Write. */
    if (fputs(data_out, handler->fstream) == EOF)
    {
        fclose(handler->fstream);
        handler->fstream = NULL;
        return false;
    }

    handler->has_file_changed = true;
    handler->has_dir_changed = true;
    if (handler->is_strict_fsize_enabled)
    {
        handler->curr_fsize += data_size;
    }

    return true;
}

/* Updates the active filepath. The handlerandler will attempt to write in
that file. */
void _handler_refresh_path(handler_t* handler)
{
    handler->curr_dname[0] = '\0';
    handler->curr_fname[0] = '\0';
    handler->curr_fpath[0] = '\0';
    formatter_path(&handler->dname_formatter, handler->curr_dname);
    formatter_path(&handler->fname_formatter, handler->curr_fname);
    strcpy(handler->curr_fpath, handler->curr_dname);
    strcat(handler->curr_fpath, LG_PATH_DELIM_STR);
    strcat(handler->curr_fpath, handler->curr_fname);
}

bool _rotate_files(const char* abs_path)
{
    char file_to_rename[LG_MAX_FNAME_SIZE];
    char new_filename[LG_MAX_FNAME_SIZE];
    size_t i = 0;

    /* Rename old file to old_filename.0 to simplify logic
    below. */
    if (_does_file_exist(abs_path))
    {
        sprintf(new_filename, "%s.0", abs_path);
        rename(abs_path, new_filename);
    }
    else { return true; }

    do
    {
        sprintf(file_to_rename, "%s.%u", abs_path, i);
        ++i;
    } while (_does_file_exist(file_to_rename));
    
    for (i; i >= 1; --i)
    {
        sprintf(file_to_rename, "%s.%u", abs_path, i - 1);
        sprintf(new_filename, "%s.%u", abs_path, i);
        rename(file_to_rename, new_filename);
    }
    return true;
}

void _handler_deploy_file(handler_t* handler)
{
    /* Create directory and open file. */
    _handler_refresh_path(handler);
    if (!_does_dir_exist(handler->curr_dname))
    {
        _create_dir(handler->curr_dname);
    }
    if (_does_file_exist(handler->curr_fpath))
    {
        switch (handler->fmode)
        {
        case LG_FMODE_MANUAL:
            handler->fstream = fopen(handler->curr_fpath, "a"); break;
        case LG_FMODE_REWRITE:
            handler->fstream = fopen(handler->curr_fpath, "w"); break;
        case LG_FMODE_ROTATE:
            _rotate_files(handler->curr_fpath);
            handler->fstream = fopen(handler->curr_fpath, "w"); break;
        }
    }
    else
    {
        handler->fstream = fopen(handler->curr_fpath, "w");
    }

    /* Set output buffer. */
    if (handler->fstream)
    {
        setvbuf(handler->fstream,
                handler->file_buf,
                handler->bmode,
                handler->bsize);
        handler->curr_fsize = _handler_file_size(handler);
    }
}

void _handler_close_file(handler_t* handler)
{
    fclose(handler->fstream);
    if (!handler->has_file_changed && handler->is_file_creator)
    {
        _remove_file(handler->curr_fname);
    }
    
    if (handler->is_dir_creator && !handler->has_dir_changed)
    {
         _remove_dir(handler->curr_dname);
    }
    handler->fstream = NULL;
    handler->is_dir_creator = false;
    handler->has_dir_changed = false;
    handler->has_file_changed = false;
    handler->is_file_creator = false;
    handler->curr_fsize = 0;
}

fpos_t _handler_file_size(handler_t* handler)
{
    /* TODO: Error checks */
    fpos_t size = 0;
    fpos_t orig_pos = 0;
    fgetpos(handler->fstream, &orig_pos);
    fseek(handler->fstream, 0L, SEEK_END);
    fgetpos(handler->fstream, &size);
    fsetpos(handler->fstream, &orig_pos);

    return size;
}
