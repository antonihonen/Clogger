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
	// TODO: Check legality of parameters.

	strcpy(log->file_dir_, dir);
	stcpy(log->filename_format_, filename_format);
	log->max_file_size_ = max_file_size;
	log->file_policy_ = file_policy;
	log->file_ = NULL;
	log->is_file_creator_ = false;
	log->has_file_changed_ = false;

	log->buffering_policy_ = buffering_policy;
	log->buffer_capacity_ = LOG_DEF_BUFFER_SIZE;

	strcpy(log->entry_format_, LOG_DEF_ENTRY_FORMAT);
	log->entry_threshold_ = LOG_DEF_THRESHOLD;
	log->do_allow_entries_ = true;

	return NO_ERROR;
}

LOG_ERROR
log_enable(log_t* log)
{
	// TODO: Check legality of parameters.

	log->do_allow_entries_ = true;
	return NO_ERROR;
}

LOG_ERROR
log_disable(log_t* log)
{
	// TODO: Check legality of parameters.

	log->do_allow_entries_ = false;
	return NO_ERROR;
}

LOG_ERROR
log_close(log_t* log)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_threshold(log_t* log, LOG_LEVEL threshold)
{
	return NO_ERROR;
}

LOG_ERROR
log_threshold(log_t* log, LOG_LEVEL* threshold)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_buffering_policy(log_t* log, LOG_BUFFERING_POLICY policy)
{
	return NO_ERROR;
}

LOG_ERROR
log_buffering_policy(log_t* log, LOG_BUFFERING_POLICY* policy)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_buffer(log_t* log, size_t buffer_size);

LOG_ERROR
log_flush_buffer(log_t* log)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_file_policy(log_t* log, LOG_FILE_POLICY policy)
{
	return NO_ERROR;
}

LOG_ERROR
log_file_policy(log_t* log, LOG_FILE_POLICY* policy)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_dir(log_t* log, char* dir)
{
	return NO_ERROR;
}

LOG_ERROR
log_dir(log_t* log, char* dir)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_filename_format(log_t* log, char* filename_format)
{
	return NO_ERROR;
}

LOG_ERROR
log_current_file_name(log_t* log, char* filename)
{
	return NO_ERROR;
}

LOG_ERROR
log_filepath(log_t* log, char* path)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_max_file_size(log_t* log, size_t file_size)
{
	return NO_ERROR;
}

LOG_ERROR
log_max_file_size(log_t* log, size_t* file_size)
{
	return NO_ERROR;
}

LOG_ERROR
log_current_file_size(log_t* log, size_t* file_size)
{
	return NO_ERROR;
}

LOG_ERROR
log_set_entry_format(log_t* log, char* entry_format)
{
	return NO_ERROR;
}

LOG_ERROR
log_write(log_t* log, LOG_LEVEL level, char* message)
{
	return NO_ERROR;
}

LOG_ERROR
log_trace(log_t* log, char* message)
{
	return NO_ERROR;
}

LOG_ERROR
log_debug(log_t* log, char* message)
{
	return NO_ERROR;
}

LOG_ERROR
log_info(log_t* log, char* message)
{
	return NO_ERROR;
}

LOG_ERROR
log_warning(log_t* log, char* message)
{
	return NO_ERROR;
}

LOG_ERROR
log_error(log_t* log, char* message)
{
	return NO_ERROR;
}

LOG_ERROR
log_critical(log_t* log, char* message)
{
	return NO_ERROR;
}
