/*
 * File: formatter.c
 * Project: logger
 * Created: 2019-04-17
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 */

#include "formatter.h"
#include "time_handler.h"
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#define __CLEAR_STRING(string) (string[0] = '\0')
#define __IS_EMPTY_STRING(string) (string[0] == '\0')
#define __NULL_LOG_LEVEL -1
#define __UM_HANDLER(macro_id) __FM_HANDLERS[macro_id]

/* Private helper functions. */

/* Checks that the format macro indicated by macro_start
begins with __FM_BEGIN_INDIC followed by __FM_LEFT_DELIM
and ends with __FM_RIGHT_DELIM, then writes the string
between the two delimiters to macro_as_str, adding the null
terminator. Macro_length will indicate how many characters
there were between __FM_BEGIN_INDIC and __FM_RIGHT_DELIM
(including those two) - the formatter can jump that many
characters in the format string since those characters
have been handled. If the macro doesn't conform to the rule
stated above, only __FM_BEGIN_INDIC will be written into
macro_as_str (and macro_length will be 1).
*/
void
__um_as_str(const char* macro_start, char* macro_as_str,
	size_t* const macro_length)
{
	assert(macro_start); assert(macro_as_str); assert(macro_length);
	assert(*macro_start == __FM_BEGIN_INDIC);

	char* macro_as_str_original = macro_as_str;
	bool has_macro_ended = false;
	bool has_macro_begun = false;
	bool has_macro_valid_format = true;
	*macro_length = 0;

	while (!has_macro_ended)
	{	
		switch (*macro_start)
		{
		case __FM_LEFT_DELIM:
			if (has_macro_begun || *macro_length != 1)
			{
				// Only one __FM_LEFT_DELIM can be contained
				// by a valid macro sequence and it must
				// be the second character.
				has_macro_valid_format = false;
				has_macro_ended = true;
			}
			has_macro_begun = true;
			break;
		case __FM_RIGHT_DELIM:
			if (!has_macro_begun)
			{
				// __FM_LEFT_DELIM must come before __FM_RIGHT_DELIM
				has_macro_valid_format = false;
			}
			has_macro_ended = true;
			break;
		case __FM_BEGIN_INDIC:
			if (*macro_length > 0)
			{
				// A macro cannot contain __FM_BEGIN_INDIC
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
			if (!has_macro_ended)
			{
				has_macro_valid_format = false;
			}
			has_macro_ended = true;
			break;
		default:
			*macro_as_str = *macro_start;
			++macro_as_str;

			break;
		}

		if (!has_macro_valid_format)
		{
			// Invalid format so write __FM_BEGIN_INDIC in the first
			// char of the macro string.
			*macro_as_str_original = __FM_BEGIN_INDIC;
			macro_as_str = macro_as_str_original + 1;
			// Only one valid char in macro_str now.
			*macro_length = 1;
		}
		else
		{
			++*macro_length;
		}
		
		if (has_macro_ended)
		{
			// Finish the macro string by appending null.
			*macro_as_str = '\0';
		}
	
		// Move on to the next char of the macro sequence.
		++macro_start;
	}
}

/* Figures what the macro indicated by macro_start is
and writes the corresponding __FM_ID to macro_id.
Macro_length will contain the length of the macro sequence,
i.e. how many characters the macro occupies in the
format string, not including null terminator.
*/
void
__identify_um(const char* const macro_start, __FM_ID* const macro_id, size_t* const macro_length)
{
	assert(macro_start); assert(macro_id); assert(macro_length);
	assert(*macro_start == __FM_BEGIN_INDIC);

	// Get the macro as a string as well as the number of
	// characters the macro sequence consists of.
	char macro_as_str[__MAX_UM_S_LEN];
	__um_as_str(macro_start, macro_as_str, macro_length);

	// Iterate through __FORMAT_MACROS and see if one of them
	// matches. The indexes of the macro strings in __FORMAT_MACROS
	// match their respective __FM_IDs so i = __FM_ID.
	for (size_t i = 0; i < __FM_COUNT; ++i)
	{
		if (strcmp(macro_as_str, __FORMAT_MACROS[i]) == 0) {
			// Match.
			*macro_id = i;
			return;
		}
	}
	
	// No match.
	*macro_id = __FM_NO_MACRO;
}

/* Expands the format macro indicated by macro_start
and writes the result to dest without adding the
null terminator. Thandler will be used to expand
time-related macros. Msg contains the log message
entered by the user, if any. Lvl contains the
log level of the message, if any. Macro_length
will contain the number of characters the macro
sequence consisted of. If the macro format is invalid,
only __UM_BEGIN_INDIC is written to dest (macro_length
will be 1). */
void
__expand_um(char* macro_start, char* dest, thandler_t* thandler,
	char* msg, LOG_LEVEL lvl, size_t* macro_length)
{
	assert(dest && macro_start);
	assert(*macro_start == __FM_BEGIN_INDIC);
	assert(macro_length);
	// Local time must have been fetched.
	// TODO: Add a function to the thandler interface
	// for this.
	assert(thandler->_last_fetch);

	__FM_ID macro_id = __FM_NO_MACRO;
	__identify_um(macro_start, &macro_id, macro_length);
	if (macro_id != __FM_NO_MACRO)
	{
		__UM_HANDLER(macro_id)(thandler, dest, lvl, msg);
	}
}

 /* File name formatter functions. */

LOG_ERROR
fn_formatter_init(fn_formatter_t* formatter, char* fn_format)
{
	// TODO: Check validity of parameters.

	fn_formatter_set_format(formatter, fn_format);
	formatter->thandler = malloc(sizeof(thandler_t));
	thandler_init(formatter->thandler);
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
	assert(formatter); assert(formatted_filename);

	// Pointer to the byte to be next written in the formatted_filename
	// buffer.
	char* filename_head = formatted_filename;
	// Pointer to the first byte in the format string that hasn't yet
	// been handled.
	char* format_head = formatter->_fn_format;

	// Fetch the local time for time-related macros so they all
	// refer to the same point in time.

	thandler_fetch_ltime(formatter->thandler);

	while (*format_head != '\0')
	{
		// Copy characters one at a time until
		// the beginning of a macro is found.
		while (*format_head != __FM_BEGIN_INDIC)
		{
			*filename_head = *format_head;
			++filename_head;
			++format_head;
		}
		// Macro begin was discovered.
		size_t macro_length = 0;
		__expand_um(format_head, filename_head, formatter->thandler, NULL, __NULL_LOG_LEVEL, &macro_length);
		format_head += macro_length;
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
	free(formatter->thandler);
	return E_NO_ERROR;
}
