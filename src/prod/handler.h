/*
 * File: handler.h
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
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

#ifndef LG_FILE_HANDLER_H
#define LG_FILE_HANDLER_H

#include "error.h"
#include "formatter.h"
#include "macros.h"
#include "policy.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Log output handler. */
typedef struct {
    /* The file stream used to write in files. */
    FILE*        fstream;
    
    /* File name formatter: required to support user macros
    in file names. */
    formatter_t  fname_formatter;

    /* Directory name formatter: required to support user macros
    in directory names. */
    formatter_t  dname_formatter;

    /* The name of the currently active file. */
    char         curr_fname[LG_MAX_FNAME_SIZE];

    /* The absolute filepath of the directory where the current
    log fill resides. */
    char         curr_dname[LG_MAX_FNAME_SIZE];

    /* The absolute filepath of the currently active log file. */
    char         curr_fpath[LG_MAX_FNAME_SIZE];

    /* The capacity of the buffer in bytes. */
    size_t       bsize;

    /* Buffering mode. One of: _IONBF, _IOLBF, _IOFBF. */
    int          bmode;

    /* File mode. One of: MANUAL, REWRITE, ROTATE. */
    LG_FMODE     fmode;

    /* The maximum size of a log file in bytes. Log files are
    guaranteed to be smaller than this. */
    fpos_t       max_fsize;

    /* Indicates whether the log directory was created by the
    file handler. */
    bool         is_dir_creator;

    /* Indicates whether the log file was created by the
    file handler. */
    bool         is_file_creator;
    
    /* Indicates if the current log file has been written in. */
    bool         has_file_changed;

    /* Indicates if the handler has written to a file within the current
    directory. */
    bool         has_dir_changed;

    /* Indicates the size of the current log file in bytes. */
    size_t       curr_fsize;

    uint16_t     flags;

    /* The logging level the handler is associated with. */
    LG_LEVEL     level;

    /* Indicates whether the handler is enabled. */
    bool         is_enabled;

    /* Indicates whether strict file size is enabled. */
    bool         is_strict_fsize_enabled;

    /* Indicates whether strict time is enabled. */
    bool         is_strict_time_enabled;

    /* Indicates whether file locks are enabled. */
    bool         is_flock_enabled;

    /* Indicates whether writing to files is enabled. */
    bool         is_file_enabled;

    /* Indicates whether writing to stdout is enabled. */
    bool         is_stdout_enabled;

    /* Indicates whether writing to stderr is enabled. */
    bool         is_stderr_enabled;

    /* Indicates whether writing to user-defined place is enabled. */
    bool         is_user_output_enabled;

    /* File output buffer. */
    char         file_buf[BUFSIZ];

    /* Stdout output buffer. */
    char         stdout_buf[BUFSIZ];

    LG_ERRNO     last_error;
    char         error_msg[LG_MAX_ERR_MSG_SIZE];

    /* Indicates whether the object dynamically reserved its own memory. */
    bool         is_dynamic;

    bool         (*user_output)(const char*);
} handler_t;

handler_t* handler_init(handler_t* buffer, LG_LEVEL level);

void handler_free(handler_t* handler);

void handler_enable(handler_t* handler);

void handler_disable(handler_t* handler);

bool handler_enabled(handler_t* handler);

bool handler_user_output_register(handler_t* handler, bool (*user_output)(const char*));

void handler_user_output_enable(handler_t* handler);

void handler_user_output_disable(handler_t* handler);

bool handler_user_output_enabled(handler_t* handler);

/* TODO */
void handler_strict_fsize_enable(handler_t* handler);

/* TODO */
void handler_strict_fsize_disable(handler_t* handler);

/* TODO */
bool handler_strict_fsize_enabled(handler_t* handler);

/* TODO */
void handler_strict_time_enable(handler_t* handler);

/* TODO */
void handler_strict_time_disable(handler_t* handler);

/* TODO */
bool handler_strict_time_enabled(handler_t* handler);

/* TODO */
void handler_flock_enable(handler_t* handler);

/* TODO */
void handler_flock_disable(handler_t* handler);

/* TODO */
bool handler_flock_enabled(handler_t* handler);

void handler_file_enable(handler_t* handler);

void handler_file_disable(handler_t* handler);

bool handler_file_enabled(handler_t* handler);

void handler_stdout_enable(handler_t* handler);

void handler_stdout_disable(handler_t* handler);

bool handler_stdout_enabled(handler_t* handler);

void handler_stderr_enable(handler_t* handler);

void handler_stderr_disable(handler_t* handler);

bool handler_stderr_enabled(handler_t* handler);

void handler_set_error(handler_t* handler, LG_ERRNO error, const char* message);

LG_ERRNO handler_get_error(handler_t* handler);

bool handler_has_error(handler_t* handler);

void handler_clear_error(handler_t* handler);

bool handler_set_bmode(handler_t* handler, int mode);

int handler_bmode(const handler_t* handler);

bool handler_set_bsize(handler_t* handler, size_t size);

size_t handler_bsize(const handler_t* handler);

bool handler_set_fmode(handler_t* handler, LG_FMODE mode);

LG_FMODE handler_fmode(const handler_t* handler);

bool handler_set_fname_format(handler_t* handler, const char* format);

char* handler_fname_format(handler_t* handler, char* dest);

char* handler_curr_fname(const handler_t* handler, char* dest);

char* handler_curr_dname(const handler_t* handler, char* dest);

char* handler_curr_fpath(const handler_t* handler, char* dest);

bool handler_set_dname_format(handler_t* handler, const char* format);

char* handler_dname_format(handler_t* handler, char* dest);

bool handler_set_max_fsize(handler_t* handler, size_t size);

size_t handler_max_fsize(const handler_t* handler);

size_t handler_current_fsize(const handler_t* handler);

bool handler_send(handler_t* handler, const char* data_out);

#endif /* LG_FILE_HANDLER_H */
