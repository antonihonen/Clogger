/*
 * File: error.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines error codes used in the project.
 * These error codes may be returned to the user of
 * the library or used internally within the library.
 *
 * The module also provides a way for all other modules
 * in the project to register errors and fetch information
 * of the error that last took place. Information of an
 * error is stored by calling the __register_error() function
 * and fetched by calling log_get_error(). Currently
 * only the last error that occurred is stored.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef ERROR_H
#define ERROR_H

#include <limits.h>
#include <stdbool.h>

typedef enum {
	E_NO_ERROR = 0
} LOG_ERROR;

/* Stores an error code that can be fetched
by calling log_get_error. */
extern inline bool
__register_error(LOG_ERROR error);

/* Returns the last error registered by
calling __register_error. */
extern inline LOG_ERROR
log_get_error();

#endif /* ERROR_H */
