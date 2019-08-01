/*
 * File: file_handler.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "flags.h"
#include "file_handler.h"
#include "string_util.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32) && !defined(_CYGWIN_)
#define LG_USE_WINAPI
#include <windows.h>
#define LG_WIN_PATH_DELIM_CHAR '\\'
#define LG_WIN_PATH_DELIM_STR "\\"
#endif

#define LG_MAX_OPEN_ATTEMPTS 3

static fhandler_t* _fh_alloc(const size_t bufsize);

static bool _fh_open_fstream(fhandler_t* const fh, size_t data_size);

static void _fh_refresh_path(fhandler_t* const fh);

static bool _rotate_files(const char* const abs_filepath);

static bool _file_size(FILE* const fstream, fpos_t* const size);

static bool _does_dir_exist(const char* const abs_path);

static bool _create_dir(const char* const abs_path);

static bool _remove_dir(const char* const abs_path);

static bool _does_file_exist(const char* const abs_filepath);

/* Allocates and initializes a new fhandler_t object and returns
a pointer to it. */
fhandler_t* fh_init(const char* dname_format,
                    const char* fname_format,
                    size_t max_fsize,
                    LG_FMODE fmode,
                    int buf_mode,
                    size_t buf_size,
                    uint16_t flags)
{
    /* Assert parameter validity and/or correctness. */
    assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);
    assert(fmode > 0 && fmode <= LG_VALID_FMODE_COUNT);
    if (buf_mode == _IONBF)
    {
        buf_size = 0;
    }
    else if (buf_size == 0)
    {
        buf_size = LG_DEF_BUF_SIZE;
    }

    /* Allocate memory. */
    fhandler_t* fh = _fh_alloc(buf_size);
    if (!fh)
    {
        return NULL;
    }

    /* Finish initialization. */
    format_set(fh->fname_formatter, fname_format);
    format_set(fh->dname_formatter, dname_format);
    fh->buf_mode = buf_mode;
    fh->fstream = NULL;
    fh->buf_size = buf_size;
    fh->file_mode = fmode;
    fh->has_file_changed = false;
    fh->is_dir_creator = false;
    fh->is_file_creator = false;
    fh->max_fsize = max_fsize;
    fh->curr_fsize = 0;
    fh->flags = flags;
    LG_clear_str(fh->curr_fname);
    LG_clear_str(fh->curr_dname);
    LG_clear_str(fh->curr_fpath);

    return fh;
}

/* Frees the memory reserved for fh and its sub-objects. */
void fh_free(fhandler_t* fh)
{
    if (fh->fstream)         { fclose(fh->fstream);              }
    if (fh->fname_formatter) { format_free(fh->fname_formatter); }
    if (fh->dname_formatter) { format_free(fh->dname_formatter); }
    if (fh->buf)             { _log_dealloc(fh->buf);            }

    _log_dealloc(fh);
}

bool fh_set_buf_mode(fhandler_t* fh, int mode)
{
    assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
    
    if (fh->buf_mode == mode)
    {
        return true;
    }

    if (mode == _IONBF)
    {
        if (fh->buf)
        {
            _log_dealloc(fh->buf);
        }
        fh->buf = NULL;
        fh->buf_size = 0;
    }
    else
    {
        fh->buf = _log_alloc(LG_DEF_BUF_SIZE);
        if (!fh->buf)
        {
            return false;
        }
    }
    
    fh->buf_mode = mode;
    return true;
}

int fh_buf_mode(const fhandler_t* fh)
{
    return fh->buf_mode;
}

bool fh_set_buf_size(fhandler_t* fh, size_t size)
{
    if (fh->buf_size == size)
    {
        return true;
    }
    else if (size == 0)
    {
        return fh_set_buf_mode(fh, _IONBF);
    }
    
    if (fh->buf)
    {
        if (fh->fstream)
        {
            fclose(fh->fstream);
        }
        _log_dealloc(fh->buf);
    }    
    fh->buf = _log_alloc(size);
    fh->buf_size = size;
    return true;
}

size_t fh_buf_size(const fhandler_t* fh)
{
    return fh->buf_size;
}

bool fh_set_file_mode(fhandler_t* fh, LG_FMODE mode)
{
    assert(mode == LG_FMODE_ROTATE || mode == LG_FMODE_REWRITE);
    fh->file_mode = mode;
    return true;
}

LG_FMODE fh_file_mode(const fhandler_t* fh)
{
    return fh->file_mode;
}

bool fh_set_fname_format(fhandler_t* fh, const char* format)
{
    if (!format_set(fh->fname_formatter, format))
    {
        return false;
    }
    _fh_refresh_path(fh);
    return true;
}

char* fh_fname_format(fhandler_t* fh, char* src)
{
    format_get(fh->fname_formatter, src);
    return src;
}

char* fh_curr_fname(const fhandler_t* fh, char* dest)
{
    strcpy(dest, fh->curr_fname);
    return dest;
}

char* fh_curr_dname(const fhandler_t* fh, char* dest)
{
    strcpy(dest, fh->curr_dname);
    return dest;
}

char* fh_curr_fpath(const fhandler_t* fh, char* dest)
{
    strcpy(dest, fh->curr_fpath);
    return dest;
}

bool fh_set_dname_format(fhandler_t* fh, const char* format)
{
    if (!format_set(fh->dname_formatter, format))
    {
        return false;
    }
    _fh_refresh_path(fh);
    return true;
}

char* fh_dname_format(fhandler_t* fh, char* src)
{
    format_get(fh->dname_formatter, src);
    return src;
}

bool fh_set_max_fsize(fhandler_t* fh, size_t size)
{
    fh->max_fsize = size;
    return true;
}

size_t fh_max_fsize(const fhandler_t* fh)
{
    return fh->max_fsize;
}

size_t fh_current_fsize(const fhandler_t* fh)
{
    return fh->curr_fsize;
}

bool fh_fwrite(fhandler_t* fh, const char* data_out)
{
    size_t data_size = strlen(data_out);
    bool new_fstream = fh->fstream ? false : true;

    /* Attempt to open the correct file. */
    if (!_fh_open_fstream(fh, data_size))
    {
        return false;
    }

    /* Set output buffer if any. */
    if (new_fstream)
    {
        setvbuf(fh->fstream, fh->buf, fh->buf_mode, fh->buf_size);
    }

    /* Write. */
    if (fputs(data_out, fh->fstream) == EOF)
    {
        fclose(fh->fstream);
        fh->fstream = NULL;
        return false;
    }

    fh->has_file_changed = true;
    fh->curr_fsize += data_size;    

    return true;
}

/* Allocates memory for the fhandler object and its sub-objects. */
fhandler_t* _fh_alloc(const size_t buf_size)
{
    fhandler_t* fh = _log_alloc(sizeof(fhandler_t));
    if (!fh) { return NULL; }
    fh->fname_formatter = format_init("", LG_FORMAT_PATHS);
    fh->dname_formatter = format_init("", LG_FORMAT_PATHS);
    fh->buf = NULL;
    if (buf_size != 0)
    {
        fh->buf = _log_alloc(buf_size);
    }
    if (!fh->fname_formatter || !fh->dname_formatter || (!fh->buf && buf_size))
    {
        fh_free(fh);
        return NULL;
    }
    return fh;
}

bool _fh_open_fstream(fhandler_t* fh, size_t write_size)
{
    if (fh->fstream)
    {
        if (fh->curr_fsize > fh->max_fsize - write_size)
        {
            fclose(fh->fstream);
            fh->fstream = NULL;
        }
        else
        {
            return true;
        }
    }

    /* Attempt to open the correct file up to 3 times. */
    size_t opening_attempts = 0;
    while (!fh->fstream && opening_attempts < LG_MAX_OPEN_ATTEMPTS)
    {
        if (LG_is_empty_str(fh->curr_fpath))
        {
            /* A new file needs to be created. Get the new filepath. */
            _fh_refresh_path(fh);
        }

        /* First attempt was unsuccessful. Check if this was due to
        directory not existing, create if so. */
        if (opening_attempts > 0)
        {
            if (!_does_dir_exist(fh->curr_dname))
            {
                if (!_create_dir(fh->curr_dname))
                {
                    return false;
                }
                fh->is_dir_creator = true;
            }
        }

        /* Open the file. This creates a new file if one doesn't exist,
        but won't discard a pre-existing file with the same name. */
        fh->fstream = fopen(fh->curr_fpath, "a");

        if (fh->fstream)
        {
            /* Get the current file size. */
            fpos_t file_size = 0;
            if (!_file_size(fh->fstream, &file_size))
            {
                fclose(fh->fstream);
                fh->fstream = NULL;
                return false;
            }
            /* Check if file size cap will be hit. */
            if (file_size + write_size >= fh->max_fsize - 1)
            {
                /* Close the stream and get the name for the new file. */
                if (fclose(fh->fstream) == EOF)
                {
                    return false;
                }
                fh->fstream = NULL;
                _fh_refresh_path(fh);
                fh->curr_fsize = 0;

                /* Rotate the pre-existing files if rotate mode. */
                if (fh->file_mode == LG_FMODE_ROTATE)
                {
                    _rotate_files(fh->curr_fpath);
                }
                /* This will discard an old file with the same name. */
                else { fopen(fh->curr_fpath, "w"); }
            }
            /* File size cap won't be hit, good to go. */
            else { break; }
        }

        ++opening_attempts;
    }

    return fh->fstream != NULL;
}

/* Updates the active filepath. The fhandler will attempt to write in
that file. */
void _fh_refresh_path(fhandler_t* fh)
{
    LG_clear_str(fh->curr_dname);
    LG_clear_str(fh->curr_fname);
    LG_clear_str(fh->curr_fpath);
    format_path(fh->dname_formatter, fh->curr_dname);
    format_path(fh->fname_formatter, fh->curr_fname);
    strcpy(fh->curr_fpath, fh->curr_dname);
#ifdef LG_USE_WINAPI
    strcat(fh->curr_fpath, LG_WIN_PATH_DELIM_STR);
#endif
    strcat(fh->curr_fpath, fh->curr_fname);
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

/* Writes the current size of the file associated with fstream into size.
Returns false if an error occurred. */
bool _file_size(FILE* fstream, fpos_t* size)
{
    fpos_t orig_pos = 0;
    if (fgetpos(fstream, &orig_pos) != 0)
    {
        return false;
    }
    if (fseek(fstream, 0L, SEEK_END) != 0)
    {
        return false;
    }
    if (fgetpos(fstream, size) != 0)
    {
        return false;
    }
    
    fsetpos(fstream, &orig_pos);

    return true;
}

/* Returns true if dir_path points to an existing directory. */
bool _does_dir_exist(const char* abs_path)
{
#ifdef LG_USE_WINAPI
    DWORD ftyp = GetFileAttributesA(abs_path);
    if (ftyp == INVALID_FILE_ATTRIBUTES)
    {
        return false;
    }
    else if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true;
    }
    return false;
#endif
}

/* Creates the directory in dir_path and returns true if successful. */
bool _create_dir(const char* abs_path)
{
#ifdef LG_USE_WINAPI
    /* TODO: Recursive folder creation, i.e. create parent folder(s) */
    return CreateDirectoryA(abs_path, NULL) != 0;
#endif
}

bool _remove_dir(const char* abs_path)
{
#ifdef LG_USE_WINAPI
    return RemoveDirectoryA(abs_path) == 0;
#endif
        return false;
}

/* Returns true if filepath points to an existing file. */
bool _does_file_exist(const char* abs_path)
{
    FILE* f = fopen(abs_path, "r");
    if (f)
    {
        fclose(f);
        return true;
    }
    return false;
}
