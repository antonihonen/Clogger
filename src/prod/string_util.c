/*
 * File: string_util.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains utilities that help
 * with handling strings.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "string_util.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define __CHAR_TO_LOWER(c) \
	*c += 32
	
#define __IS_UPPERCASE_CHAR(c) *c >= 'A' && *c <= 'Z' ? true : false

void
__two_digit_int_to_str(int i, char* str)
{
	assert(i >= 0);
	assert(str);

	char format[4];
	if (i < 10)
	{
		strcpy(format, "0%d");
	}
	else
	{
		strcpy(format, "%d");
	}
	sprintf(str, format, i);
}

void
__ascii_str_to_lower(char* str)
{
	assert(str);

	while (*str != '\0')
	{
		if (__IS_UPPERCASE_CHAR(str))
		{
			__CHAR_TO_LOWER(str);
		}
		++str;
	}
}
