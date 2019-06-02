/*
 * File: file_handler.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "file_handler.h"
#include "string_util.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32) && !defined(_CYGWIN_)
#define _USE_WINAPI
#include <windows.h>
#define _WIN_PATH_DELIM_CHAR '\\'
#define _WIN_PATH_DELIM_STR "\\"
#endif

#define _MAX_OPEN_ATTEMPTS 3

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
                    LOG_FILE_MODE fmode,
                    int buf_mode,
                    size_t buf_size)
{
    /* Assert parameter validity and/or correctness. */
    assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);
    assert(fmode > 0 && fmode <= _VALID_FILEPOL_COUNT);
    if (buf_mode == _IONBF)
    {
        buf_size = 0;
    }
    else if (buf_size == 0)
    {
        buf_size = _DEF_BUF_SIZE;
    }

    /* Allocate memory. */
    fhandler_t* fh = _fh_alloc(buf_size);
    if (!fh)
    {
        return NULL;
    }

    /* Finish initialization. */
    format_set(fh->_fname_formatter, fname_format);
    format_set(fh->_dname_formatter, dname_format);
    fh->_buf_mode = buf_mode;
    fh->_fstream = NULL;
    fh->_buf_cap = buf_size;
    fh->_file_mode = fmode;
    fh->_has_file_changed = false;
    fh->_is_dir_creator = false;
    fh->_is_file_creator = false;
    fh->_max_fsize = max_fsize;
    fh->_current_fsize = 0;
    _clear_str(fh->_cur_fn);
    _clear_str(fh->_cur_dirn);
    _clear_str(fh->_cur_fp);

    return fh;
}

/* Frees the memory reserved for fh and its sub-objects. */
void fh_close(fhandler_t* fh)
{
    if (fh->_fstream)         { fclose(fh->_fstream); }
    if (fh->_fname_formatter) { format_free(fh->_fname_formatter); }
    if (fh->_dname_formatter) { format_free(fh->_dname_formatter); }
    if (fh->_buf)             { _log_dealloc(fh->_buf); }

    _log_dealloc(fh);
}

bool fh_set_buf_mode(fhandler_t* fh, int mode)
{
    assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
    
    if (fh->_buf_mode == mode)
    {
        return true;
    }

    if (mode == _IONBF)
    {
        if (fh->_buf)
        {
            _log_dealloc(fh->_buf);
        }
        fh->_buf = NULL;
        fh->_buf_cap = 0;
    }
    else
    {
        fh->_buf = _log_alloc(_DEF_BUF_SIZE);
        if (!fh->_buf)
        {
            return false;
        }
    }
    
    fh->_buf_mode = mode;
    return true;
}

int fh_buf_mode(const fhandler_t* fh)
{
    return fh->_buf_mode;
}

bool fh_set_buf_size(fhandler_t* fh, size_t size)
{
    if (fh->_buf_cap == size)
    {
        return true;
    }
    else if (size == 0)
    {
        return fh_set_buf_mode(fh, _IONBF);
    }
    
    if (fh->_buf)
    {
        _log_dealloc(fh->_buf);
    }    
    fh->_buf = _log_alloc(size);
    fh->_buf_cap = size;
    return true;
}

size_t fh_buf_size(const fhandler_t* fh)
{
    return fh->_buf_cap;
}

bool fh_set_file_mode(fhandler_t* fh, LOG_FILE_MODE mode)
{
    assert(mode == ROTATE || mode == REWRITE);
    fh->_file_mode = mode;
    return true;
}

LOG_FILE_MODE fh_file_mode(const fhandler_t* fh)
{
    return fh->_file_mode;
}

bool fh_set_fname_format(fhandler_t* fh, const char* format)
{
    if (!format_set(fh->_fname_formatter, format))
    {
        return false;
    }
    _fh_refresh_path(fh);
    return true;
}

char* fh_curr_fname(const fhandler_t* fh, char* dest)
{
    strcpy(dest, fh->_cur_fn);
    return dest;
}

char* fh_curr_dname(const fhandler_t* fh, char* dest)
{
    strcpy(dest, fh->_cur_dirn);
    return dest;
}

char* fh_curr_fpath(const fhandler_t* fh, char* dest)
{
    strcpy(dest, fh->_cur_fp);
    return dest;
}

bool fh_set_dname_format(fhandler_t* fh, const char* format)
{
    if (!format_set(fh->_dname_formatter, format))
    {
        return false;
    }
    _fh_refresh_path(fh);
    return true;
}

bool fh_set_max_fsize(fhandler_t* fh, size_t size)
{
    fh->_max_fsize = size;
    return true;
}

size_t fh_max_fsize(const fhandler_t* fh)
{
    return fh->_max_fsize;
}

size_t fh_current_fsize(const fhandler_t* fh)
{
    return fh->_current_fsize;
}

bool fh_fwrite(fhandler_t* fh, const char* data_out)
{
    assert(!fh->_fstream);

    size_t data_size = strlen(data_out);

    /* Attempt to open the correct file. */
    if (!_fh_open_fstream(fh, data_size))
    {
        return false;
    }

    assert(fh->_fstream);

    /* Set output buffer if any. */
    setvbuf(fh->_fstream, fh->_buf, fh->_buf_mode, fh->_buf_cap);

    /* Write. */
    if (fputs(data_out, fh->_fstream) == EOF)
    {
        fclose(fh->_fstream);
        fh->_fstream = NULL;
        return false;
    }
    
    if (fclose(fh->_fstream) == EOF)
    {
        fh->_fstream = NULL;
    }
    
    fh->_has_file_changed = true;
    fh->_current_fsize += data_size;
    fh->_fstream = NULL;

    return true;
}

/* Allocates memory for the fhandler object and its sub-objects. */
fhandler_t* _fh_alloc(const size_t buf_size)
{
    fhandler_t* fh = _log_alloc(sizeof(fhandler_t));
    if (!fh) { return NULL; }
    fh->_fname_formatter = format_init("", _FORMAT_PATHS);
    fh->_dname_formatter = format_init("", _FORMAT_PATHS);
    fh->_buf = NULL;
    if (buf_size != 0)
    {
        fh->_buf = _log_alloc(buf_size);
    }
    if (!fh->_fname_formatter || !fh->_dname_formatter || (!fh->_buf && buf_size))
    {
        fh_close(fh);
        return NULL;
    }
    return fh;
}

bool _fh_open_fstream(fhandler_t* fh, size_t write_size)
{
    /* Attempt to open the correct file up to 3 times. */
    size_t opening_attempts = 0;
    while (!fh->_fstream && opening_attempts < _MAX_OPEN_ATTEMPTS)
    {
        if (_is_empty_str(fh->_cur_fp))
        {
            /* A new file needs to be created. Get the new filepath. */
            _fh_refresh_path(fh);
        }

        /* First attempt was unsuccessful. Check if this was due to
        directory not existing, create if so. */
        if (opening_attempts > 0)
        {
            if (!_does_dir_exist(fh->_cur_dirn))
            {
                if (!_create_dir(fh->_cur_dirn))
                {
                    return false;
                }
                fh->_is_dir_creator = true;
            }
        }

        /* Open the file. This creates a new file if one doesn't exist,
        but won't discard a pre-existing file with the same name. */
        fh->_fstream = fopen(fh->_cur_fp, "a");

        if (fh->_fstream)
        {
            /* Get the current file size. */
            fpos_t file_size = 0;
            if (!_file_size(fh->_fstream, &file_size))
            {
                fclose(fh->_fstream);
                fh->_fstream = NULL;
                return false;
            }
            /* Check if file size cap will be hit. */
            if (file_size + write_size >= fh->_max_fsize - 1)
            {
                /* Close the stream and get the name for the new file. */
                if (fclose(fh->_fstream) == EOF)
                {
                    return false;
                }
                fh->_fstream = NULL;
                _fh_refresh_path(fh);
                fh->_current_fsize = 0;

                /* Rotate the pre-existing files if rotate mode. */
                if (fh->_file_mode == ROTATE)
                {
                    _rotate_files(fh->_cur_fp);
                }
                /* This will discard an old file with the same name. */
                else { fopen(fh->_cur_fp, "w"); }
            }
            /* File size cap won't be hit, good to go. */
            else { break; }
        }

        ++opening_attempts;
    }

    return fh->_fstream != NULL;
}

/* Updates the active filepath. The fhandler will attempt to write in
that file. */
void _fh_refresh_path(fhandler_t* fh)
{
    /* TODO Add the length of the expanded fn to fn_format_t. */
    _clear_str(fh->_cur_dirn);
    _clear_str(fh->_cur_fn);
    _clear_str(fh->_cur_fp);
    format_path(fh->_dname_formatter, fh->_cur_dirn);
    format_path(fh->_fname_formatter, fh->_cur_fn);
    strcpy(fh->_cur_fp, fh->_cur_dirn);
#ifdef _USE_WINAPI
    strcat(fh->_cur_fp, _WIN_PATH_DELIM_STR);
#endif
    strcat(fh->_cur_fp, fh->_cur_fn);
}

bool _rotate_files(const char* abs_path)
{
    char file_to_rename[_MAX_FILENAME_SIZE];
    char new_filename[_MAX_FILENAME_SIZE];
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
#ifdef _USE_WINAPI
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
#ifdef _USE_WINAPI
    /* TODO: Recursive folder creation, i.e. create parent folder(s) */
    return CreateDirectoryA(abs_path, NULL) != 0;
#endif
}

bool _remove_dir(const char* abs_path)
{
#ifdef _USE_WINAPI
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
