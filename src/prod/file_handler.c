/*
 * File: file_handler.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "file_handler.h"
#include <assert.h>
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool __fh_fopen_if_good_size(fhandler_t*, size_t);
static bool __file_size(FILE*, fpos_t*);

fhandler_t*
fh_init(LOG_BUF_POLICY buf_policy,
	size_t buf_size,
	LOG_FILE_POLICY file_policy,
	char* fn_format,
	size_t max_file_size)
{
	assert(fn_format);
	assert(buf_policy > 0 && buf_policy <= __VALID_BUFPOL_COUNT);
	assert(file_policy > 0 && file_policy <= __VALID_FILEPOL_COUNT);
	if (buf_policy != NO_BUFFERING && buf_size == 0) { buf_size = BUFSIZ; }

	fhandler_t* new_fh = malloc(sizeof(fhandler_t));
	fn_format_t* new_fnf = fnf_init(fn_format);
	char* new_buf = NULL;
	if (buf_policy != NO_BUFFERING) { new_buf = malloc(buf_size); }
	else { buf_size = 0; }

	if (!new_fh || !new_fnf || (!new_buf && buf_policy != NO_BUFFERING))
	{
		/* Memory allocation failed. Clean up and return NULL. */
		if (new_fh) { free(new_fh); }
		if (new_fnf) { free(new_fnf); }
		if (new_buf) { free(new_buf); }
		return NULL;
	}

	new_fh->_fstream = NULL;
	new_fh->_fnf = new_fnf;
	new_fh->_buf = new_buf;

	switch (buf_policy)
	{
	case NO_BUFFERING: new_fh->_buf_mode = _IONBF; break;
	case LINE_BUFFERING: new_fh->_buf_mode = _IOLBF; break;
	case FULL_BUFFERING: new_fh->_buf_mode = _IOFBF; break;
	}

	new_fh->_buf_cap = buf_size;
	new_fh->_file_policy = file_policy;
	new_fh->_has_file_changed = false;
	new_fh->_is_file_creator = false;
	new_fh->_file_iter = 0;
	new_fh->_max_file_size = max_file_size;

	return new_fh;
}

void fh_close(fhandler_t* fh)
{
	assert(fh);

	fnf_close(fh->_fnf);
	free(fh);
}


bool fh_write(fhandler_t* fh, char* str)
{
	assert(fh); assert(str);

	size_t write_size = strlen(str);
	
	/* TODO: Check current file size. */
	/* TODO: Create new file if current file has
	reached the maximum size. */

	/* TODO: Only expand the filename when starting to write
	in a new file */
	char filename[__MAX_FILENAME_SIZE];
	
	fnf_format(fh->_fnf, filename);

	if (!__fh_fopen_if_good_size(fh, write_size))
	{
		assert(!fh->_fstream);
		return false;
	}
	if (!fh->_fstream) { return false; }

	fh->_fstream = fopen(filename, "a");
	if (!fh->_fstream) { return false; }

	/* TODO: Create dir if doesn't exist. */
	/* TODO: Check if file already exists (? may not be needed). */

	setvbuf(fh->_fstream, fh->_buf, fh->_buf_mode, fh->_buf_cap);

	if (fputs(str, fh->_fstream) == EOF) { return false; }
	if (fclose(fh->_fstream) == EOF) { return false; }

	fh->_fstream = NULL;

	return true;
}

bool __fh_fopen_if_good_size(fhandler_t* fh, size_t next_write_size)
{
	assert(fh);

	char path[__MAX_FILENAME_SIZE];
	fnf_format(fh->_fnf, path);
	fh->_fstream = fopen(path, "a");
	if (!fh->_fstream) { /* TODO: Handle. */ return false; }
	fpos_t current_size = 0;

	if (!__file_size(fh->_fstream, &current_size))
	{
		fclose(fh);
		fh->_fstream = NULL;
		return false;
	}
	else if (current_size + (fpos_t)next_write_size >= fh->_max_file_size)
	{
		fclose(fh);
		fh->_fstream = NULL;
	}
	return true;
}

bool __file_size(FILE* fstream, fpos_t* size)
{
	assert(fstream); assert(size);

	fpos_t orig_pos = 0;
	if (fgetpos(fstream, &orig_pos) != 0) { return false; }
	if (fseek(fstream, 0L, SEEK_END) != 0) { return false; }
	if (fgetpos(fstream, size) != 0) { return false; }
	
	fsetpos(fstream, &orig_pos);

	return true;
}
