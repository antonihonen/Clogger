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
#include <stdio.h>

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

	fhandler_t* new_fh = malloc(sizeof(fhandler_t));
	fn_format_t* new_fnf = fnf_init(fn_format);

	if (!new_fh || !new_fnf)
	{
		/* Memory allocation failed. Clean up and return NULL. */
		if (new_fh) { free(new_fh); }
		return NULL;
	}

	new_fh->fnf = new_fnf;
	new_fh->_fstream = NULL;
	new_fh->_buf_policy = buf_policy;
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

	fnf_close(fh->fnf);
	free(fh);
}
