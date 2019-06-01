/*
 * File: formatter.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "fm_parser.h"
#include "formatter.h"
#include "string_util.h"
#include "time_handler.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

void
__format_str(const char* format, char* dest,
	thandler_t* const th, const char* const msg, const LOG_LEVEL lvl);

static bool
__is_valid_fn_form(const char* format);

static bool
__is_valid_e_form(const char* format);

/* File name formatter functions. */

fn_format_t*
fnf_init(const char* const format)
{
	assert(format);
	fn_format_t* new_fnf = _log_alloc(sizeof(fn_format_t));
	thandler_t* new_th = th_init();

	if (new_fnf && new_th
		&& fnf_set_format(new_fnf, format))
	{
		new_fnf->_th = new_th;
		return new_fnf;
	}

	/* Memory allocation failed or format was invalid. Clean up
	and return NULL. */
	if (new_fnf) { _log_dealloc(new_fnf); }
	return NULL;
}

bool
fnf_set_format(fn_format_t* const fnf, const char* const format)
{
	assert(fnf);
	assert(format);
	if (!__is_valid_fn_form(format)) { return false; }

	strcpy(fnf->_form, format);

	return true;
}

void
fnf_format(fn_format_t* const fnf, char* formatted_filename)
{
	assert(fnf);
	assert(formatted_filename);

	__format_str(fnf->_form, formatted_filename,
		fnf->_th, NULL, __L_NO_LEVEL);
}

void
fnf_close(fn_format_t* const fnf)
{
	assert(fnf);
	th_close(fnf->_th);
	_log_dealloc(fnf);
}

/* Entry formatter functions. */

e_format_t*
ef_init(const char* const format)
{
	assert(format);
	e_format_t* new_ef = _log_alloc(sizeof(e_format_t));
	thandler_t* new_th = th_init();

	if (new_ef && new_th && ef_set_format(new_ef, format))
	{
		new_ef->_th = new_th;
		return new_ef;
	}

	/* Memory allocation failed or format was invalid. Clean up
	and return NULL. */
	if (new_ef) { _log_dealloc(new_ef); }
	return NULL;
}

bool
ef_set_format(e_format_t* const ef, const char* const format)
{
	assert(ef); assert(format);

	if (!__is_valid_e_form(format)) { return false; }

	strcpy(ef->_form, format);
	return true;
}

void
ef_format(e_format_t* const ef, char* formatted_entry, const char* const msg, const LOG_LEVEL lvl)
{
	assert(ef); assert(msg); assert(formatted_entry);

	__format_str(ef->_form, formatted_entry,
		ef->_th, msg, lvl);
}

void
ef_close(e_format_t* const ef)
{
	assert(ef);
	th_close(ef->_th);
	_log_dealloc(ef);
}

/* Helper functions. */



/* Expands all format macros starting from format, writing the expanded
string to dest. Th will be used to expand time-related macros.
Msg contains the log message entered by the user, if any.
Lvl contains the log level of the message, if any.
Msg and lvl may be omitted when this function is used to
format a file name, since they are meaningless in that context. */
void
__format_str(const char* format, char* dest,
	thandler_t* const th, const char* const msg, const LOG_LEVEL lvl)
{
	assert(format); assert(dest); assert(th);
	/* If message is given, logging level must also be given (this function
	was called by the entry formatter) - if not, logging level must not be
	given either (called by filename formatter). */
	assert((msg && lvl != __L_NO_LEVEL) || (!msg && lvl == __L_NO_LEVEL));

	/* Fetch the local time for time-related macros so they all
	refer to the same point in time. */
	th_fetch_ltime(th);

	while (*format != '\0')
	{
		if (*format != __FM_BEGIN_INDIC)
		{
			/* No macro begin encountered. */
			*dest = *format;
			++dest;
			++format;
		}
		else
		{
			/* Macro begin encountered. */

			/* Unexpanded macro length. */
			size_t macro_len = 0;
			/* Expanded macro length. */
			size_t exp_macro_len = 0;
			/* Expand the macro. */
			__expand_fm(format, dest, th, msg, lvl, &macro_len, &exp_macro_len);

			if (macro_len == 0 && exp_macro_len == 0)
			{
				/* False alarm, no valid macro found. */
				*dest = *format;
				macro_len = 1;
				exp_macro_len = 1;
			}
			format += macro_len;
			dest += exp_macro_len;
		}
	}
	/* Add the null terminator which was excluded in the
	while loop. */
	assert(*format == '\0');
	*dest = *format;
}

/* Returns true if format is valid, i.e. contains no illegal
macros and has a maximum length < __MAX_FILENAME_SIZE - 1
when expanded. */
bool
__is_valid_fn_form(const char* format)
{
	assert(format);
	size_t max_len = 0;

	while (*format != '\0')
	{
		size_t macro_len = 1;
		size_t exp_macro_len = 1;
		if (*format == __FM_BEGIN_INDIC)
		{
			__FM_ID id = __identify_fm(format, &macro_len);
			if (id != __FM_NO_MACRO) { exp_macro_len = __FM_TABLE[id].max_len; }
			switch (id)
			{
			case __FM_MSG:
			case __FM_LVL_N:
			case __FM_LVL_F:
			case __FM_LVL_A:
				return false;
			}
		}
		format += macro_len;
		max_len += exp_macro_len;
	}

	if (max_len < __MAX_FILENAME_SIZE - 1) { return true; }

	return false;
}

/* Returns true if format is valid, i.e. contains no illegal macros and
has a maximum length < __MAX_ENTRY_SIZE - 1 when expanded. */
bool
__is_valid_e_form(const char* format)
{
	assert(format);
	size_t max_len = 0;

	while (*format != '\0')
	{
		size_t macro_len = 1;
		size_t exp_macro_len = 1;
		if (*format == __FM_BEGIN_INDIC)
		{
			__FM_ID id = __identify_fm(format, &macro_len);
			if (id != __FM_NO_MACRO) { exp_macro_len = __FM_TABLE[id].max_len; }
		}
		format += macro_len;
		max_len += exp_macro_len;
	}

	if (max_len < __MAX_ENTRY_SIZE - 1) { return true; }

	return false;
}
