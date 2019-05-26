/*
 * File: log.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "log.h"
#include <assert.h>
#include <malloc.h>

static inline log_t*
__log_malloc(char* dir_form, char* filename_form,
	LOG_FILE_MODE file_mode, int buf_mode);

log_t*
log_init(char* dir_form,
	char* filename_form,
	LOG_FILE_MODE file_mode,
	int buf_mode)
{
	assert(dir_form); assert(filename_form);
	assert(file_mode == ROTATE || file_mode == REWRITE);
	assert(buf_mode == _IONBF || buf_mode == _IOLBF || buf_mode == _IOFBF);

	log_t* log = __log_malloc(dir_form, filename_form, file_mode, buf_mode);
	if (!log) { return NULL; }

	log->_fh = fh_init(dir_form, filename_form, __DEF_MAX_FSIZE, file_mode,
		buf_mode, BUFSIZ);
	log->_is_enabled = true;
	log->_threshold = __DEF_THRESHOLD;

	return log;
}

bool log_close(log_t* log)
{
	assert(log);

	if (log->_fh) { fh_close(log->_fh); }
	free(log);
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
}

LOG_LEVEL
log_threshold(log_t* log)
{
	assert(log);
	return log->_threshold;
}

bool
log_set_buf_mode(log_t* log, LOG_BUF_MODE mode)
{
	assert(log);
	assert(mode == _IONBF || mode == _IOLBF || mode == _IOFBF);
	fh_set_buf_mode(log->_fh, mode);
	return true;
}

LOG_BUF_MODE
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
log_set_filename_format(log_t* log, char* fn_form)
{
	assert(log); assert(fn_form);
	return fh_set_fn_format(log->_fh, fn_form);
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

bool
log_write(log_t* log, LOG_LEVEL level, char* message)
{
	assert(log); assert(message);
	if (level >= log->_threshold &&
		log->_is_enabled)
	{
		return fh_write(log->_fh, message);
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
	log_t* log = malloc(sizeof(log_t));
	if (!log) { return NULL; }

	log->_fh = fh_init(dir_form, filename_form, __DEF_MAX_FSIZE,
		file_mode, buf_mode, BUFSIZ);
	if (!log->_fh) { log_close(log); return NULL; }

	return log;
}
