/*
 * File: string_util.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "string_util.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define __ASCII_CAP_AND_SMALL_DIFF 32

static inline char __char_to_lower(char c)
{
	return c + __ASCII_CAP_AND_SMALL_DIFF;
}

static inline bool __is_uppercase_c(char c)
{
	return c >= 'A' && c <= 'Z' ? true : false;
}

void __terminate_str(char* str, size_t i)
{
	assert(str);
	str[i] = '\0';
}

void __clear_str(char* str)
{
	assert(str);
	__terminate_str(str, 0);
}

bool __is_empty_str(char* str)
{
	assert(str);
	return *str == '\0';
}

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
		if (__is_uppercase_c(*str))
		{
			*str = __char_to_lower(*str);
		}
		++str;
	}
}
