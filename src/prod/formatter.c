/*
 * File: formatter.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "formatter.h"
#include "string_util.h"
#include "time_handler.h"
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#define __FM_HANDLER(macro_id) __FM_HANDLERS[macro_id]

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
__fm_as_str(const char* macro_start, char* macro_as_str,
	size_t* const macro_length)
{
	assert(macro_start); assert(macro_as_str); assert(macro_length);
	assert(*macro_start == __FM_BEGIN_INDIC);

	/* Save the initial state of macro_as_str. */
	char* macro_as_str_initial = macro_as_str;
	
	/* Indicates if __FM_RIGHT_DELIM has been encountered in the macro
	string. */
	bool has_macro_ended = false; 
	/* Indicates if __FM_LEFT_DELIM was encountered as the second char. */
	bool has_macro_begun = false;
	/* Indicates whether the macro conforms to the format described in
	format_macro.h, except that in terms of this function the macro
	body doesn't need to be a valid one. */
	bool has_macro_valid_format = true;
	*macro_length = 0;

	/* Read the macro string one character at a time until the macro
	either ends or is found to be invalid. */
	while (!has_macro_ended)
	{	
		switch (*macro_start)
		{
		case __FM_LEFT_DELIM:
			/* Only one __FM_LEFT_DELIM can be contained
			by a valid macro sequence and it must
			be the second character. */
			if (has_macro_begun || *macro_length != 1)
			{
				has_macro_valid_format = false;
				has_macro_ended = true;
			}
			has_macro_begun = true;
			break;
		case __FM_RIGHT_DELIM:
			/* __FM_LEFT_DELIM must come before __FM_RIGHT_DELIM */
			if (!has_macro_begun)
			{
				has_macro_valid_format = false;
			}
			has_macro_ended = true;
			break;
		case __FM_BEGIN_INDIC:
			/* A valid macro cannot contain __FM_BEGIN_INDIC
			unless it's the first char. */
			if (*macro_length > 0)
			{
				has_macro_valid_format = false;
				has_macro_ended = true;
			}
			break;
		case '\0':
			/* End of macro string. */
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
			/* Only the characters forming the body of the macro
			is written into the macro_as_str buffer. */
			*macro_as_str = *macro_start;
			++macro_as_str;
			break;
		}

		if (!has_macro_valid_format)
		{
			/* Invalid format so write __FM_BEGIN_INDIC in the first
			char of the macro string. */
			*macro_as_str_initial = __FM_BEGIN_INDIC;
			macro_as_str = macro_as_str_initial + 1;
			/* Set length to 0 as if the last character,
			which caused the macro to be found invalid,
			was the first one. */
			*macro_length = 0;
		}
		
		++*macro_length;
		
		if (has_macro_ended)
		{
			/* Finish the macro string by appending null. */
			*macro_as_str = '\0';
		}
	
		/* Move on to the next char of the macro sequence. */
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
__identify_fm(const char* const macro_start, __FM_ID* const macro_id, size_t* const macro_length)
{
	assert(macro_start); assert(macro_id); assert(macro_length);
	assert(*macro_start == __FM_BEGIN_INDIC);

	/* Get the macro as a string as well as the number of
	characters the macro sequence consists of. */
	char macro_as_str[__MAX_FM_S_LEN];
	__fm_as_str(macro_start, macro_as_str, macro_length);

	/* Iterate through __FORMAT_MACROS and see if one of them
	matches. The indexes of the macro strings in __FORMAT_MACROS
	match their respective __FM_IDs so i = __FM_ID. */
	for (size_t i = 0; i < __FM_COUNT; ++i)
	{
		if (strcmp(macro_as_str, __FORMAT_MACROS[i]) == 0) {
			/* Match. */
			*macro_id = i;
			return;
		}
	}
	
	/* No match. */
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
only __FM_BEGIN_INDIC is written to dest (macro_length
will be 1). */
void
__expand_fm(char* macro_start, char* dest, thandler_t* thandler,
	char* msg, LOG_LEVEL lvl, size_t* macro_length)
{
	assert(macro_start); assert(dest);
	assert(*macro_start == __FM_BEGIN_INDIC);
	assert(macro_length);
	/* Local time must have been fetched. */
	/* TODO: Add a function to the thandler interface
	for this. */
	assert(thandler->_last_fetch);

	/* Figure out which macro is in question. */
	__FM_ID macro_id = __FM_NO_MACRO;
	__identify_fm(macro_start, &macro_id, macro_length);

	if (macro_id != __FM_NO_MACRO)
	{
		/* Valid macro detected. Call the handler, it will
		expand the macro. */
		__FM_HANDLER(macro_id)(thandler, dest, lvl, msg);
	}
	else
	{
		/* Invalid macro detected. Only write __FM_BEGIN_INDIC
		to dest. Macro length is already set to 1. */
		*dest = __FM_BEGIN_INDIC;
	}
}

/* Expands all macros in the format buffer, writing the expanded
string to dest. Thandler will be used to expand time-related
macros. Msg contains the log message entered by the user,
if any. Lvl contains the log level of the message, if any.
Msg and lvl may be omitted when this function is used to
format a file name, since they are meaningless in that context. */
void
__format_str(char* format, char* dest, thandler_t* thandler,
	char* msg, LOG_LEVEL lvl)
{
	assert(format); assert(dest); assert(thandler);
	/* If message is given, logging level must also be given - if not,
	logging level must not be given either. */
	assert((msg && lvl != __L_NO_LEVEL) || !msg && lvl == __L_NO_LEVEL);

	/* Pointer to the next byte to be written in the formatted_filename
	buffer. */
	char* dest_head = dest;
	/* Pointer to the first byte in the format string that hasn't yet
	been handled. */
	char* format_head = format;

	/* Fetch the local time for time-related macros so they all
	refer to the same point in time. */

	thandler_fetch_ltime(thandler);
	while (*format_head != '\0')
	{
		/* Copy characters one at a time until
		the beginning of a macro is found. */
		while (*format_head != __FM_BEGIN_INDIC)
		{
			*dest_head = *format_head;
			++dest_head;
			++format_head;
		}
		/* Macro begin was discovered.
		Expand the macro. */
		size_t macro_length = 0;
		__expand_fm(format_head, dest_head, thandler,
			msg, lvl, &macro_length);
		/* The macro was handled so skip the rest of the characters
		in the macro. */
		format_head += macro_length;
	}
	/* Add the null terminator which was excluded in the
	while loop. */
	*dest_head = *format_head;
}

 /* File name formatter functions. */

LOG_ERROR
fn_formatter_init(fn_formatter_t* formatter, char* fn_format)
{
	assert(formatter); assert(fn_format);

	fn_formatter_set_format(formatter, fn_format);
	formatter->thandler = malloc(sizeof(thandler_t));
	/* TODO: Check that malloc was successful. */
	thandler_init(formatter->thandler);
	return E_NO_ERROR;
}

LOG_ERROR
fn_formatter_set_format(fn_formatter_t* formatter, char* format)
{
	assert(formatter); assert(format);
	/* TODO: Check format validity(? may not be needed). */

	strcpy(formatter->_fn_format, format);

	/* Clear the expanded filename string since the format was changed. */
	__CLEAR_STRING(formatter->_expanded_fn);

	return E_NO_ERROR;
}

LOG_ERROR
fn_formatter_format(fn_formatter_t* formatter, char* formatted_filename)
{
	assert(formatter); assert(formatted_filename);

	__format_str(formatter->_fn_format, formatted_filename,
		formatter->thandler, NULL, __L_NO_LEVEL);

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