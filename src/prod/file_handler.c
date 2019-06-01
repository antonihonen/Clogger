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

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define __USE_WINAPI
#include <windows.h>
#define __WIN_PATH_DELIM_CHAR '\\'
#define __WIN_PATH_DELIM_STR "\\"
#endif

#define __MAX_OPEN_ATTEMPTS 3

static fhandler_t*
__fh_malloc(const size_t bufsize);

static bool
__fh_open_fstream(fhandler_t* const fh, size_t data_size);

static inline void
__fh_refresh_path(fhandler_t* const fh);

static bool
__rotate_files(const char* const abs_filepath);

static inline bool
__file_size(FILE* const fstream, fpos_t* const size);

static inline bool
__does_dir_exist(const char* const abs_path);

static bool
__create_dir(const char* const abs_path);

static bool
__remove_dir(const char* const abs_path);

static inline bool
__does_file_exist(const char* const abs_filepath);

/* Allocates and initializes a new fhandler_t object and returns
a pointer to it. */
fhandler_t*
fh_init(const char* const dirn_form,
	const char* const fn_form,
	const size_t max_fsize,
	const LOG_FILE_MODE file_mode,
	const int buf_mode,
	size_t bufsize)
{
	/* Assert parameter validity and/or correctness. */
	assert(fn_form);
	assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);
	assert(file_mode > 0 && file_mode <= __VALID_FILEPOL_COUNT);
	if (buf_mode == _IONBF) { bufsize = 0; }
	else if (bufsize == 0) { bufsize = __DEF_BUF_SIZE; }

	/* Allocate memory. */
	fhandler_t* fh = __fh_malloc(bufsize);
	if (!fh) { return NULL; }

	/* Finish initialization. */
	fnf_set_format(fh->_fnf, fn_form);
	fnf_set_format(fh->_dirnf, dirn_form);
	fh->_buf_mode = buf_mode;
	fh->_fstream = NULL;
	fh->_buf_cap = bufsize;
	fh->_file_mode = file_mode;
	fh->_has_file_changed = false;
	fh->_is_dir_creator = false;
	fh->_is_file_creator = false;
	fh->_max_fsize = max_fsize;
	fh->_current_fsize = 0;
	__clear_str(fh->_cur_fn);
	__clear_str(fh->_cur_dirn);
	__clear_str(fh->_cur_fp);

	return fh;
}

/* Frees the memory reserved for fh and its sub-objects. */
void
fh_close(fhandler_t* const fh)
{
	assert(fh);

	if (fh->_fstream) { fclose(fh->_fstream); }
	if (fh->_fnf) { fnf_close(fh->_fnf); }
	if (fh->_dirnf) { fnf_close(fh->_dirnf); }
	if (fh->_buf) { __get_dealloc()(fh->_buf); }
	__get_dealloc()(fh);
}

bool
fh_set_buf_mode(fhandler_t* const fh, const int mode)
{
	assert(fh); assert(mode);
	assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
	
	if (fh->_buf_mode == mode) { return true; }

	if (mode == _IONBF)
	{
		if (fh->_buf) { __get_dealloc()(fh->_buf); fh->_buf = NULL; }
		fh->_buf_cap = 0;
	}
	else
	{
		fh->_buf = __get_alloc()(__DEF_BUF_SIZE);
		if (!fh->_buf) { return false; }
	}
	
	fh->_buf_mode = mode;
	return true;
}

int
fh_buf_mode(const fhandler_t* const fh)
{
	assert(fh);
	return fh->_buf_mode;
}

bool
fh_set_buf_size(fhandler_t* const fh, const size_t size)
{
	assert(fh);

	if (fh->_buf_cap == size) { return true; }
	else if (size == 0) { return fh_set_buf_mode(fh, _IONBF); }
	
	if (fh->_buf) { __get_dealloc()(fh->_buf); fh->_buf = NULL; }
	fh->_buf = __get_alloc()(size);
	fh->_buf_cap = size;
	return true;
}

size_t
fh_buf_size(const fhandler_t* const fh)
{
	assert(fh);
	return fh->_buf_cap;
}

bool
fh_set_file_mode(fhandler_t* const fh, const LOG_FILE_MODE mode)
{
	assert(fh); assert(mode == ROTATE || mode == REWRITE);
	fh->_file_mode = mode;
	return true;
}

LOG_FILE_MODE
fh_file_mode(const fhandler_t* const fh)
{
	assert(fh);
	return fh->_file_mode;
}

bool
fh_set_fn_format(fhandler_t* const fh, const char* const format)
{
	assert(fh); assert(format);

	if (!fnf_set_format(fh->_fnf, format)) { return false; }
	__fh_refresh_path(fh);
	return true;
}

char*
fh_curr_fname(const fhandler_t* const fh, char* filename)
{
	assert(fh); assert(filename);
	strcpy(filename, fh->_cur_fn);
	return filename;
}

char*
fh_curr_dirname(const fhandler_t* const fh, char* dir)
{
	assert(fh); assert(dir);
	strcpy(dir, fh->_cur_dirn);
	return dir;
}

char*
fh_curr_fpath(const fhandler_t* const fh, char* filepath)
{
	assert(fh); assert(filepath);
	strcpy(filepath, fh->_cur_fp);
	return filepath;
}

bool
fh_set_dirn_format(fhandler_t* const fh, const char* const format)
{
	assert(fh); assert(format);

	if (!fnf_set_format(fh->_dirnf, format)) { return false; }
	__fh_refresh_path(fh);
	return true;
}

bool
fh_set_max_fsize(fhandler_t* const fh, const size_t size)
{
	assert(fh);
	fh->_max_fsize = size;
	return true;
}

size_t
fh_max_fsize(const fhandler_t* const fh)
{
	assert(fh);
	return fh->_max_fsize;
}

size_t
fh_current_fsize(fhandler_t* const fh)
{
	assert(fh);
	return fh->_current_fsize;
}

bool
fh_write(fhandler_t* const fh, const char* const data_out)
{
	assert(fh); assert(data_out); assert(!fh->_fstream);

	size_t data_size = strlen(data_out);

	/* Attempt to open the correct file. */
	if (!__fh_open_fstream(fh, data_size)) { return false; }

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
	
	if (fclose(fh->_fstream) == EOF) { fh->_fstream = NULL; false; }
	
	fh->_has_file_changed = true;
	fh->_current_fsize += data_size;
	fh->_fstream = NULL;

	return true;
}

/* Allocates memory for the fhandler object and its sub-objects. */
fhandler_t* __fh_malloc(const size_t bufsize)
{
	fhandler_t* fh = __get_alloc()(sizeof(fhandler_t));
	if (!fh) { return NULL; }
	fh->_fnf = fnf_init("");
	fh->_dirnf = fnf_init("");
	fh->_buf = NULL;
	if (bufsize) { fh->_buf = __get_alloc()(bufsize); }
	if (!fh->_fnf || !fh->_dirnf || (!fh->_buf && bufsize))
	{
		fh_close(fh);
		return NULL;
	}
	return fh;
}

bool
__fh_open_fstream(fhandler_t* const fh, size_t data_size)
{
	assert(fh);

	/* Attempt to open the correct file up to 3 times. */
	size_t opening_attempts = 0;
	while (!fh->_fstream && opening_attempts < __MAX_OPEN_ATTEMPTS)
	{
		if (__is_empty_str(fh->_cur_fp))
		{
			/* A new file needs to be created. Get the new filepath. */
			__fh_refresh_path(fh);
		}

		/* First attempt was unsuccessful. Check if this was due to
		directory not existing, create if so. */
		if (opening_attempts > 0)
		{
			if (!__does_dir_exist(fh->_cur_dirn))
			{
				if (!__create_dir(fh->_cur_dirn)) { return false; }
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
			if (!__file_size(fh->_fstream, &file_size))
			{
				fclose(fh->_fstream);
				fh->_fstream = NULL;
				return false;
			}
			/* Check if file size cap will be hit. */
			if (file_size + data_size >= fh->_max_fsize - 1)
			{
				/* Close the stream and get the name for the new file. */
				if (fclose(fh->_fstream) == EOF) { return false; }
				fh->_fstream = NULL;
				__fh_refresh_path(fh);
				fh->_current_fsize = 0;

				/* Rotate the pre-existing files if rotate mode. */
				if (fh->_file_mode == ROTATE) { __rotate_files(fh->_cur_fp); }
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
void
__fh_refresh_path(fhandler_t* const fh)
{
	assert(fh);

	/* TODO Add the length of the expanded fn to fn_format_t. */
	__clear_str(fh->_cur_dirn);
	__clear_str(fh->_cur_fn);
	__clear_str(fh->_cur_fp);
	fnf_format(fh->_dirnf, fh->_cur_dirn);
	fnf_format(fh->_fnf, fh->_cur_fn);
	strcpy(fh->_cur_fp, fh->_cur_dirn);
#ifdef __USE_WINAPI
	strcat(fh->_cur_fp, __WIN_PATH_DELIM_STR);
#endif
	strcat(fh->_cur_fp, fh->_cur_fn);
}

bool
__rotate_files(const char* const abs_filepath)
{
	assert(abs_filepath);

	char file_to_rename[__MAX_FILENAME_SIZE];
	char new_filename[__MAX_FILENAME_SIZE];
	size_t i = 0;

	/* Rename old file to old_filename.0 to simplify logic
	below. */
	if (__does_file_exist(abs_filepath))
	{
		sprintf(new_filename, "%s.0", abs_filepath);
		rename(abs_filepath, new_filename);
	}
	else { return true; }

	do
	{
		sprintf(file_to_rename, "%s.%u", abs_filepath, i);
		++i;
	} while (__does_file_exist(file_to_rename));
	
	for (i; i >= 1; --i)
	{
		sprintf(file_to_rename, "%s.%u", abs_filepath, i - 1);
		sprintf(new_filename, "%s.%u", abs_filepath, i);
		rename(file_to_rename, new_filename);
	}
	return true;
}

/* Writes the current size of the file associated with fstream into size.
Returns false if an error occurred. */
bool
__file_size(FILE* const fstream, fpos_t* const size)
{
	assert(fstream); assert(size);

	fpos_t orig_pos = 0;
	if (fgetpos(fstream, &orig_pos) != 0) { return false; }
	if (fseek(fstream, 0L, SEEK_END) != 0) { return false; }
	if (fgetpos(fstream, size) != 0) { return false; }
	
	fsetpos(fstream, &orig_pos);

	return true;
}

/* Returns true if dir_path points to an existing directory. */
bool
__does_dir_exist(const char* const abs_path)
{
	assert(abs_path);

#ifdef __USE_WINAPI
	DWORD ftyp = GetFileAttributesA(abs_path);
	if (ftyp == INVALID_FILE_ATTRIBUTES) { return false; }
	else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) { return true; }
	return false;
#endif
}

/* Creates the directory in dir_path and returns true if successful. */
bool
__create_dir(const char* const abs_path)
{
	assert(abs_path);

#ifdef __USE_WINAPI
	/* TODO: Recursive folder creation, i.e. create parent folder(s) */
	return CreateDirectoryA(abs_path, NULL) != 0;
#endif
}

bool
__remove_dir(const char* const abs_path)
{
	assert(abs_path);

#ifdef __USE_WINAPI
	return RemoveDirectoryA(abs_path) == 0;
#endif
		return false;
}

/* Returns true if filepath points to an existing file. */
bool
__does_file_exist(const char* const abs_filepath)
{
	assert(abs_filepath);
	FILE* f = fopen(abs_filepath, "r");
	if (f) { fclose(f); return true; }
	return false;
}
