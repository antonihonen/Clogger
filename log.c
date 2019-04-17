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
}
