/*
 * File: format.c
 * Project: logger
 * Created: 2019-04-17
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file implements the interface defined in
 * format.h.
 */

#include "format.h"
#include "time_handler.h"
#include <stdbool.h>
#include <string.h>

 /* File name formatter functions. */

#define LOG_CLEAR_STRING(string) (string[0] = '\0')
#define LOG_NULL_TERMINATOR '\0'

static LOG_ERROR
expand_macro(char** dest_head, char** format_head, LOG_LEVEL lvl)
{
	return E_NO_ERROR;
}

LOG_ERROR
fn_formatter_init(fn_formatter_t* formatter, char* fn_format)
{
	// TODO: Check validity of parameters.

	fn_formatter_set_format(formatter, fn_format);
	return E_NO_ERROR;
}

LOG_ERROR
fn_formatter_set_format(fn_formatter_t* formatter, char* format)
{
	// TODO: Check validity of parameters.

	strcpy(formatter->_fn_format, format);
	// Clear the expanded filename string.
	formatter->_expanded_fn[0] = '\0';
	return E_NO_ERROR;
}

LOG_ERROR
fn_formatter_format(fn_formatter_t* formatter, char* formatted_filename)
{
	// TODO: Check validity of parameters.
	
	// Pointer to the byte to be next written in the formatted_filename
	// buffer.
	char* filename_head = formatted_filename;
	// Pointer to the first byte in the format string that hasn't yet
	// been handled.
	char* format_head = formatter->_fn_format;
	
	while (*format_head != LOG_NULL_TERMINATOR)
	{
		// Copy characters one at a time until
		// the beginning of a macro is found.
		while (*format_head != __MACRO_BEGIN)
		{
			*filename_head = *format_head;
			++filename_head;
			++format_head;
		}
		// Expand the macro.
		expand_macro(&filename_head, &format_head, -1);
	}
	// Add the null terminator which was excluded in the
	// while loop.
	*filename_head = *format_head;

	return E_NO_ERROR;
}

LOG_ERROR
fn_formatter_fn_max_len(fn_formatter_t* formatter, size_t* size)
{
	return E_NO_ERROR;
}

LOG_ERROR
fn_formatter_close(fn_formatter_t* formatter)
{
	return E_NO_ERROR;
}

/* Entry formatter functions. */

LOG_ERROR
e_formatter_init(e_formatter_t* formatter, char* format)
{
	return E_NO_ERROR;
}

LOG_ERROR
e_formatter_set_format(e_formatter_t* formatter, char* format)
{
	return E_NO_ERROR;
}

LOG_ERROR
e_formatter_format(e_formatter_t* formatter, char* message, char* formatted_entry)
{
	return E_NO_ERROR;
}

LOG_ERROR
e_formatter_close(e_formatter_t* formatter)
{
	return E_NO_ERROR;
}
