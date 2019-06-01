/*
 * File: file_handler.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains a file handler that the log
 * uses to write in a log file: the file handler is responsible
 * for all operations involving files.
 *
 * The user of this module can:
 * -use format macros in directory and file names
 * -choose buffer size
 * -choose  buffer mode
 * -choose file mode
 *
 * The file handler has two possible file modes: ROTATE
 * and REWRITE.
 * 
 * In ROTATE mode whenever a new log file is being created
 * and there already is a file with the desired name, the old file will
 * be renamed to <filename>.1. If <filename>.1 already exists it will
 * be renamed to <filename>.2 and so on.
 *
 * In REWRITE mode whenever a new log file is being created
 * and there already is a file with the desired name, the file will
 * be wiped completely clean, after which the log will continue writing
 * in that file.
 *
 * The file handler has three possible buffering modes: _IONBF
 * (no buffering), _IOLBF (line buffering) and _IOFBF (full buffering).
 * These are defined in stdio.h and work precisely as described
 * in the documentation of setvbuf.
 * 
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "error.h"
#include "formatter.h"
#include "macros.h"
#include "policy.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define _DEF_BUF_SIZE BUFSIZ

/* File handler. */
typedef struct {
    /* The file stream used to write in files. */
    FILE* _fstream;
    
    /* File name formatter: required to support user macros
    in file names. */
    fn_format_t* _fnf;

    /* Directory name formatter: required to support user macros
    in directory names. */
    fn_format_t* _dirnf;

    /* The name of the currently active file. */
    char _cur_fn[_MAX_FILENAME_SIZE];

    /* The absolute filepath of the directory where the current
    log fill resides. */
    char _cur_dirn[_MAX_FILENAME_SIZE];

    /* The absolute filepath of the currently active log file. */
    char _cur_fp[_MAX_FILENAME_SIZE];

    /* Output buffer. NULL if buffering mode is _IONBF. */
    char* _buf;

    /* The capacity of the buffer in bytes. */
    size_t _buf_cap;

    /* Buffering mode. One of: _IONBF, _IOLBF, _IOFBF. */
    int _buf_mode;

    /* File mode. One of: ROTATE, REWRITE. */
    LOG_FILE_MODE _file_mode;

    /* The maximum size of a log file in bytes. Log files are
    guaranteed to be smaller than this. */
    size_t _max_fsize;

    /* Indicates whether the log directory was created by the
    file handler. */
    bool _is_dir_creator;

    /* Indicates whether the log file was created by the
    file handler. */
    bool _is_file_creator;
    
    /* Indicates if the current log file has been written in. */
    bool _has_file_changed;

    /* Indicates the size of the current log file in bytes. */
    size_t _current_fsize;
} fhandler_t;

fhandler_t* fh_init(const char* dname_format,
    const char* fname_format,
    size_t max_fsize,
    LOG_FILE_MODE fmode,
    int buf_mode,
    size_t buf_size);

void fh_close(fhandler_t* fh);

bool fh_set_buf_mode(fhandler_t* fh, int mode);

int fh_buf_mode(const fhandler_t* fh);

bool fh_set_buf_size(fhandler_t* fh, size_t size);

size_t fh_buf_size(const fhandler_t* fh);

bool fh_set_file_mode(fhandler_t* fh, LOG_FILE_MODE mode);

LOG_FILE_MODE fh_file_mode(const fhandler_t* fh);

bool fh_set_fname_format(fhandler_t* fh, const char* format);

char* fh_curr_fname(const fhandler_t* fh, char* dest);

char* fh_curr_dname(const fhandler_t* fh, char* dest);

char* fh_curr_fpath(const fhandler_t* fh, char* dest);

bool fh_set_dname_format(fhandler_t* fh, const char* format);

bool fh_set_max_fsize(fhandler_t* fh, size_t size);

size_t fh_max_fsize(const fhandler_t* fh);

size_t fh_current_fsize(const fhandler_t* fh);

bool fh_fwrite(fhandler_t* fh, const char* data_out);

#endif /* FILE_HANDLER_H */
