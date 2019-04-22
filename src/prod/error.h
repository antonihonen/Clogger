/*
 * File: error.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines error codes used in the project.
 * These error codes may be returned to the user of
 * the library or used internally within the library.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef ERROR_H
#define ERROR_H

#include <limits.h>

typedef enum {
	E_FIRST_ERROR_PLACEHOLDER = INT_MIN, /* Error codes are negative */
	/* Add new error codes here */
	E_NO_ERROR = 0
} LOG_ERROR;

#endif /* ERROR_H */
