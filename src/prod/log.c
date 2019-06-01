/*
 * File: log.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "log.h"
#include <assert.h>

static inline log_t*
__log_malloc(char* dir_form, char* filename_form,
	LOG_FILE_MODE file_mode, int buf_mode);

log_t*
log_init(char* dirn_format,
	char* fn_format,
	LOG_FILE_MODE file_mode,
	int buf_mode)
{
	assert(dirn_format); assert(fn_format);
	assert(file_mode == ROTATE || file_mode == REWRITE);
	assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);

	log_t* log = __log_malloc(dirn_format, fn_format, file_mode, buf_mode);
	if (!log) { return NULL; }

	log->_fh = fh_init(dirn_format, fn_format, __DEF_MAX_FSIZE, file_mode,
		buf_mode, BUFSIZ);
	log->_is_enabled = true;
	log->_threshold = __DEF_THRESHOLD;

	return log;
}

bool log_close(log_t* log)
{
	assert(log);

	if (log->_fh) { fh_close(log->_fh); }
	if (log->_ef) { ef_close(log->_ef); }
	__get_dealloc()(log);
	return true;
}

bool
log_enable(log_t* log)
{
	assert(log);
	log->_is_enabled = true;
	return true;
}

bool
log_disable(log_t* log)
{
	assert(log);
	log->_is_enabled = false;
	return true;
}

bool
log_set_threshold(log_t* log, LOG_LEVEL threshold)
{
	assert(log); assert(threshold >= 0 && threshold <= __VALID_LVL_COUNT - 1);
	log->_threshold = threshold;
	return true;
}

LOG_LEVEL
log_threshold(log_t* log)
{
	assert(log);
	return log->_threshold;
}

bool
log_set_buf_mode(log_t* log, int mode)
{
	assert(log);
	assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
	return fh_set_buf_mode(log->_fh, mode);
}

int
log_buf_mode(log_t* log)
{
	assert(log);
	return fh_buf_mode(log->_fh);
}

bool
log_set_buf_size(log_t* log, size_t buf_size)
{
	assert(log);
	return fh_set_buf_size(log->_fh, buf_size);
}

bool
log_set_file_mode(log_t* log, LOG_FILE_MODE mode)
{
	assert(log);
	return fh_set_file_mode(log->_fh, mode);
}

LOG_FILE_MODE
log_file_mode(log_t* log)
{
	assert(log);
	return fh_file_mode(log->_fh);
}

bool
log_set_dirn_format(log_t* log, char* format)
{
	assert(log); assert(format);
	return fh_set_dirn_format(log->_fh, format);
}

char*
log_curr_dirname(log_t* log, char* dir)
{
	assert(log); assert(dir);
	return fh_curr_dirname(log->_fh, dir);
}

bool
log_set_fname_format(log_t* log, char* format)
{
	assert(log); assert(format);
	return fh_set_fn_format(log->_fh, format);
}

char*
log_curr_fname(log_t* log, char* filename)
{
	assert(log); assert(filename);
	return fh_curr_fname(log->_fh, filename);
}

char*
log_curr_fpath(log_t* log, char* filepath)
{
	assert(log); assert(filepath);
	return fh_curr_fpath(log->_fh, filepath);
}

bool
log_set_max_fsize(log_t* log, size_t size)
{
	assert(log);
	return fh_set_max_fsize(log->_fh, size);
}

size_t
log_max_fsize(log_t* log)
{
	assert(log);
	return fh_max_fsize(log->_fh);
}

size_t
log_current_fsize(log_t* log)
{
	return 0;
}

extern bool
log_set_entry_format(log_t* log, char* format)
{
	assert(log); assert(format);
	ef_set_format(log->_ef, format);
	return true;
}

extern bool
log_write(log_t* log, LOG_LEVEL level, char* message)
{
	assert(log); assert(message);

	char formatted_msg[__MAX_MSG_SIZE];
	ef_format(log->_ef, formatted_msg, message, level);

	if (level >= log->_threshold &&
		log->_is_enabled)
	{
		return fh_write(log->_fh, formatted_msg);
	}
	return false;
}

bool
log_trace(log_t* log, char* message)
{
	assert(log); assert(message);
	return log_write(log, L_TRACE, message);
}

bool
log_debug(log_t* log, char* message)
{
	assert(log); assert(message);
	return log_write(log, L_DEBUG, message);
}

bool
log_info(log_t* log, char* message)
{
	assert(log); assert(message);
	return log_write(log, L_INFO, message);
}

bool
log_warning(log_t* log, char* message)
{
	assert(log); assert(message);
	return log_write(log, L_WARNING, message);
}

bool
log_error(log_t* log, char* message)
{
	assert(log); assert(message);
	return log_write(log, L_ERROR, message);
}

bool
log_critical(log_t* log, char* message)
{
	assert(log); assert(message);
	return log_write(log, L_CRITICAL, message);
}

log_t*
__log_malloc(char* dir_form, char* filename_form,
	LOG_FILE_MODE file_mode, int buf_mode)
{
	log_t* log = __get_alloc()(sizeof(log_t));
	if (!log) { return NULL; }

	log->_fh = fh_init(dir_form, filename_form, __DEF_MAX_FSIZE,
		file_mode, buf_mode, BUFSIZ);
	log->_ef = ef_init(__DEF_ENTRY_FORMAT);
	if (!log->_fh || !log->_ef)
	{
		log_close(log);
		return NULL;
	}

	return log;
}
