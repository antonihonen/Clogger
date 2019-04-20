/*
 * File: formatter.c
 * Project: logger
 * Created: 2019-04-17
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file implements the interface defined in
 * format.h.
 */

#include "formatter.h"
#include "time_handler.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>


#define __CLEAR_STRING(string) (string[0] = '\0')
#define __IS_EMPTY_STRING(string) (string[0] == '\0')
#define __NULL_LOG_LEVEL -1

/* Private helper functions. */

/* Figures out the user macro in format_sequence and writes it to macro_str.
If the sequence doesn't have a valid format, i.e. begin with
__UM_BEGIN_INDIC followed by __UM_LEFT_DELIM and end with
__UM_RIGHT_DELIM, only __UM_BEGIN_INDIC is written to macro_str and
skip_over will be 1. Skip_over indicates how many characters the macro
string written in macro_str contains, not including the null terminator. */
void
__user_macro_as_str(const char* format_sequence, char* macro_str, size_t* const skip_over)
{
	assert(format_sequence); assert(macro_str); assert(skip_over);
	assert(*format_sequence == __UM_BEGIN_INDIC);

	char* macro_as_str_original = macro_str;
	bool has_macro_ended = false;
	bool has_macro_begun = false;
	bool has_macro_valid_format = true;
	*skip_over = 0;

	while (!has_macro_ended)
	{	
		switch (*format_sequence)
		{
		case __UM_LEFT_DELIM:
			if (has_macro_begun || skip_over != 1)
			{
				// Only one __UM_LEFT_DELIM can be contained
				// by a valid macro sequence and it must
				// be the second character.
				has_macro_valid_format = false;
				has_macro_ended = true;
			}
			has_macro_begun = true;
			break;
		case __UM_RIGHT_DELIM:
			if (!has_macro_begun)
			{
				// __UM_LEFT_DELIM must come before __UM_RIGHT_DELIM
				has_macro_valid_format = false;
			}
			has_macro_ended = true;
			break;
		case __UM_BEGIN_INDIC:
			if (*skip_over > 0)
			{
				// A macro cannot contain a __UM_BEGIN_INDIC
				// unless it's the first char.
				has_macro_valid_format = false;
				has_macro_ended = true;
			}
			break;
		case '\0':
			if (!has_macro_begun)
			{
				has_macro_valid_format = false;
			}
			has_macro_ended = true;
			break;
		default:
			*macro_str = *format_sequence;
			++macro_str;

			break;
		}

		if (!has_macro_valid_format)
		{
			// Invalid format so write % in the first char of
			// the macro string.
			*macro_as_str_original = __UM_BEGIN_INDIC;
			macro_str = macro_as_str_original + 1;
			// Only one valid char in macro_str now.
			*skip_over = 1;
		}
		else
		{
			++*skip_over;
		}
		
		if (has_macro_ended)
		{
			// Finish the macro string by appending null.
			*macro_str = '\0';
		}
	
		// Move on to the next char of the macro sequence.
		++format_sequence;
	}
}

/* Figures the __UM_ID corresponding to the macro in macro_seq.
__UM_NO_MACRO if not valid. */
void
__identify_user_macro(const char* const macro_seq, __UM_ID* const macro_id, size_t* const skip_over)
{
	assert(macro_seq); assert(macro_id); assert(skip_over);
	assert(*macro_seq == __UM_BEGIN_INDIC);

	// Get the macro as a string as well as the number of
	// characters the macro consists of.
	char macro_as_str[__MAX_UM_S_LEN];
	__user_macro_as_str(macro_seq, macro_as_str, skip_over);

	// Iterate through __USER_MACROS and see if one of them
	// matches. The indexes of the macro strings in __USER_MACROS
	// match their respective __UM_IDs so i = __UM_ID.
	for (size_t i = 0; i < __UM_COUNT; ++i)
	{
		if (strcmp(macro_as_str, __USER_MACROS[i]) == 0) {
			// Match.
			*macro_id = i;
			return;
		}
	}
	
	// No match.
	*macro_id = __UM_NO_MACRO;
}

void
__expand_macro(char** dest_head, char** format_head, char* message,
	LOG_LEVEL lvl)
{
	char macro[20];
	char* macro_end = format_head;

	return E_NO_ERROR;
}

 /* File name formatter functions. */

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
	__CLEAR_STRING(formatter->_expanded_fn);
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
	
	while (*format_head != '\0')
	{
		// Copy characters one at a time until
		// the beginning of a macro is found.
		while (*format_head != __UM_BEGIN_INDIC)
		{
			*filename_head = *format_head;
			++filename_head;
			++format_head;
		}
		// Expand the macro.
		__expand_macro(&filename_head, &format_head, NULL, __NULL_LOG_LEVEL);
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
