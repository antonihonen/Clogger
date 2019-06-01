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

#define _ASCII_CAP_AND_SMALL_DIFF 32

static char _char_to_lower(char c)
{
    return c + _ASCII_CAP_AND_SMALL_DIFF;
}

static bool _is_uppercase_c(char c)
{
    return c >= 'A' && c <= 'Z' ? true : false;
}

void _terminate_str(char* str, size_t i)
{
    str[i] = '\0';
}

void _clear_str(char* str)
{
    _terminate_str(str, 0);
}

bool _is_empty_str(char* str)
{
    return *str == '\0';
}

void _two_digit_int_to_str(int i, char* str)
{
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

void _ascii_str_to_lower(char* str)
{
    while (*str != '\0')
    {
        if (_is_uppercase_c(*str))
        {
            *str = _char_to_lower(*str);
        }
        ++str;
    }
}
