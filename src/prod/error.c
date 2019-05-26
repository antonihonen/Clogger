/*
 * File: error.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "error.h"
	
static LOG_ERROR LAST_ERROR = E_NO_ERROR;

bool
__register_error(LOG_ERROR error)
{
	LAST_ERROR = error;
	return true;
}

LOG_ERROR
log_get_error()
{
	return LAST_ERROR;
}
