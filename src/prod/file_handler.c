/*
 * File: file_handler.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "file_handler.h"
#include "string_util.h"
#include <assert.h>
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define __USE_WINAPI
#include <windows.h>
#define __WIN_PATH_DELIM "\\"
#endif

static bool __fh_open_fstream(fhandler_t*, char*);
static fhandler_t* __fh_malloc(size_t);
static void __fh_refresh_fp(fhandler_t*);
static bool __rotate_files(const char* const);
static bool __file_size(FILE*, fpos_t*);
static bool __does_dir_exist(const char* const);
static bool __create_dir(const char* const);
static bool __does_file_exist(const char* const);

/* Allocates and initializes a new fhandler_t object and returns
a pointer to it. */
fhandler_t*
fh_init(char* dirn_form,
	char* fn_form,
	size_t max_fsize,
	LOG_FILE_POLICY file_mode,
	int buf_mode,
	size_t bufsize)
{
	/* Assert parameter validity and/or correctness. */
	assert(fn_form);
	assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);
	assert(file_mode > 0 && file_mode <= __VALID_FILEPOL_COUNT);
	if (buf_mode == _IONBF) { bufsize = 0; }
	else if (bufsize == 0) { bufsize = BUFSIZ; }

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
	fh->_is_file_creator = false;
	fh->_max_fsize = max_fsize;
	__clear_str(fh->_cur_dirn);
	__clear_str(fh->_cur_fp);

	return fh;
}

/* Allocates memory for the fhandler object and its sub-objects. */
fhandler_t* __fh_malloc(size_t bufsize)
{
	fhandler_t* fh = malloc(sizeof(fhandler_t));
	if (!fh) { return NULL; }
	fh->_fnf = fnf_init("");
	fh->_dirnf = fnf_init("");
	fh->_buf = NULL;
	if (bufsize) { fh->_buf = malloc(bufsize); }
	if (!fh->_fnf || !fh->_dirnf || (!fh->_buf && bufsize))
	{
		fh_close(fh);
		return NULL;
	}
	return fh;
}

/* Frees the memory reserved for fh and its sub-objects. */
void
fh_close(fhandler_t* fh)
{
	assert(fh);

	if (fh->_fnf) { fnf_close(fh->_fnf); }
	if (fh->_dirnf) { fnf_close(fh->_dirnf); }
	if (fh->_buf) { free(fh->_buf); }
	free(fh);
}

bool
fh_write(fhandler_t* fh, char* str)
{
	char orig_str[256];
	strcpy(orig_str, str);
	assert(fh); assert(str);

	/* Attempt to open the correct file. */
	if (!__fh_open_fstream(fh, str)) { return false; }

	assert(fh->_fstream);

	/* Set output buffer if any. */
	setvbuf(fh->_fstream, fh->_buf, fh->_buf_mode, fh->_buf_cap);

	assert(str);
	assert(strcmp(str, orig_str) == 0);

	/* Write. */
	if (fputs(str, fh->_fstream) == EOF)
	{
		fclose(fh->_fstream);
		return false;
	}
	if (fclose(fh->_fstream) == EOF) { return false; }
	fh->_has_file_changed = true;
	
	return true;
}

bool __fh_open_fstream(fhandler_t* fh, char* str)
{
	/* Attempt to open the correct file up to 3 times. */
	size_t data_size = strlen(str);
	size_t opening_attempts = 0;
	while (!fh->_fstream && opening_attempts < 3)
	{
		if (__is_empty_str(fh->_cur_fp))
		{
			/* A new file needs to be created. Get the new filepath. */
			__fh_refresh_fp(fh);
		}

		/* First attempt was unsuccessful. Check if this was due to
		directory not existing, create if so. */
		if (opening_attempts > 0)
		{
			if (!__does_dir_exist(fh->_cur_dirn))
			{
				if (!__create_dir(fh->_cur_dirn)) { return false; }
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
				__fh_refresh_fp(fh);

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
void __fh_refresh_fp(fhandler_t* fh)
{
	char fn[__MAX_FILENAME_SIZE];

	/* TODO Add the length of the expanded fn to fn_format_t. */
	fnf_format(fh->_dirnf, fh->_cur_dirn);
	fnf_format(fh->_fnf, fn);
	strcpy(fh->_cur_fp, fh->_cur_dirn);
	strcat(fh->_cur_fp, __WIN_PATH_DELIM);
	strcat(fh->_cur_fp, fn);
}

bool
__rotate_files(const char* const filepath)
{
	assert(filepath);

	char file_to_rename[__MAX_FILENAME_SIZE];
	char new_filename[__MAX_FILENAME_SIZE];
	size_t i = 0;

	/* Rename old file to old_filename.0 to simplify logic
	below. */
	if (__does_file_exist(filepath))
	{
		sprintf(new_filename, "%s.0", filepath);
		rename(filepath, new_filename);
	}
	else { return true; }

	do
	{
		sprintf(file_to_rename, "%s.%u", filepath, i);
		++i;
	} while (__does_file_exist(file_to_rename));
	
	for (i; i >= 1; --i)
	{
		sprintf(file_to_rename, "%s.%u", filepath, i - 1);
		sprintf(new_filename, "%s.%u", filepath, i);
		rename(file_to_rename, new_filename);
	}
	return true;
}

/* Writes the current size of the file associated with fstream into size.
Returns false if an error occurred. */
bool
__file_size(FILE* fstream, fpos_t* size)
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
__does_dir_exist(const char* const dir_path)
{
	assert(dir_path);

#ifdef __USE_WINAPI
	DWORD ftyp = GetFileAttributesA(dir_path);
	if (ftyp == INVALID_FILE_ATTRIBUTES) { return false; }
	else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) { return true; }
	return false;
#endif
}

/* Creates the directory in dir_path and returns true if successful. */
bool
__create_dir(const char* const dir_path)
{
	assert(dir_path);

#ifdef __USE_WINAPI
	return CreateDirectoryA(dir_path, NULL) != 0;
#endif
}

/* Returns true if filepath points to an existing file. */
bool
__does_file_exist(const char* const filepath)
{
	FILE* f = fopen(filepath, "r");
	if (f) { fclose(f); return true; }
	return false;
}
