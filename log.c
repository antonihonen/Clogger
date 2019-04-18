/*
 * File: log.c
 * Project: logger
 * Created: 2019-04-15
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file implements the logging interface defined in log.h.
 */

#include "log.h"
#include "validate.h"
#include <malloc.h>
#include <string.h>

LOG_ERROR
log_init(log_t* log,
	char* dir,
	char* filename_format,
	size_t max_file_size,
	LOG_FILE_POLICY file_policy,
	LOG_BUFFERING_POLICY buffering_policy)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_enable(log_t* log)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_disable(log_t* log)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_close(log_t* log)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_threshold(log_t* log, LOG_LEVEL threshold)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_threshold(log_t* log, LOG_LEVEL* threshold)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_buffering_policy(log_t* log, LOG_BUFFERING_POLICY policy)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_buffering_policy(log_t* log, LOG_BUFFERING_POLICY* policy)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_buffer_size(log_t* log, size_t buffer_size)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_flush_buffer(log_t* log)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_file_policy(log_t* log, LOG_FILE_POLICY policy)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_file_policy(log_t* log, LOG_FILE_POLICY* policy)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_dir(log_t* log, char* dir)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_dir(log_t* log, char* dir)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_filename_format(log_t* log, char* filename_format)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_current_file_name(log_t* log, char* filename)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_filepath(log_t* log, char* path)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_max_file_size(log_t* log, size_t file_size)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_max_file_size(log_t* log, size_t* file_size)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_current_file_size(log_t* log, size_t* file_size)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_set_entry_format(log_t* log, char* entry_format)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_write(log_t* log, LOG_LEVEL level, char* message)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_trace(log_t* log, char* message)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_debug(log_t* log, char* message)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_info(log_t* log, char* message)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_warning(log_t* log, char* message)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_error(log_t* log, char* message)
{
	return E_NO_ERROR;
}

LOG_ERROR
log_critical(log_t* log, char* message)
{
	return E_NO_ERROR;
}
