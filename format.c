/*
 * File: format.c
 * Project: logger
 * Created: 2019-04-17
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file implements the interface defined in
 * format.h.
 */

 /* File name formatter functions. */

#include "format.h"
#include <string.h>

#define LOG_MAX_FORMAT_MACRO_LEN 8
#define LOG_CLEAR_STRING(string) (string[0] = '\0')
#define LOG_NULL_TERMINATOR '\0'
#define LOG_MACRO_BEGIN '%'
#define LOG_MACRO_BEGIN_ESC "%%"

static LOG_ERROR expand_macro(char** format_head, char* peek_buf)
{
	return NO_ERROR;
}

LOG_ERROR
fn_formatter_init(fn_formatter_t* formatter, char* fn_format)
{
	// TODO: Check validity of parameters.

	fn_formatter_set_format(formatter, fn_format);
	return NO_ERROR;
}

LOG_ERROR
fn_formatter_set_format(fn_formatter_t* formatter, char* format)
{
	// TODO: Check validity of parameters.

	strcpy(formatter->fn_format_, format);
	// Clear the expanded filename string.
	formatter->expanded_fn_[0] = '\0';
	return NO_ERROR;
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
	char* format_head = formatter->fn_format_;
	// Buffer where peek-ahead results will be stored.
	char peek_buf[LOG_MAX_FORMAT_MACRO_LEN];
	// Pointer to the first uncopied byte in the peek buffer.
	char* peek_head = peek_buf;
	
	while (*format_head != LOG_NULL_TERMINATOR)
	{
		// Copy characters one at a time until
		// the beginning of a macro is found.
		while (*format_head != LOG_MACRO_BEGIN)
		{
			*filename_head = *format_head;
			++filename_head;
			++format_head;
		}
		// Expand the macro.
		LOG_CLEAR_STRING(peek_buf);
		peek_head = peek_buf;
		expand_macro(&format_head, peek_buf);
	}
	// Add the null terminator which was excluded in the
	// while loop.
	*filename_head = *format_head;

	return NO_ERROR;
}

LOG_ERROR
fn_formatter_fn_max_len(fn_formatter_t* formatter, size_t* size)
{
	return NO_ERROR;
}

LOG_ERROR
fn_formatter_close(fn_formatter_t* formatter)
{
	return NO_ERROR;
}

/* Entry formatter functions. */

LOG_ERROR
e_formatter_init(e_formatter_t* formatter, char* format)
{
	return NO_ERROR;
}

LOG_ERROR
e_formatter_set_format(e_formatter_t* formatter, char* format)
{
	return NO_ERROR;
}

LOG_ERROR
e_formatter_format(e_formatter_t* formatter, char* message, char* formatted_entry)
{
	return NO_ERROR;
}

LOG_ERROR
e_formatter_close(e_formatter_t* formatter)
{
	return NO_ERROR;
}
