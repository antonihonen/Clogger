/*
 * File: string_util.c
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "string_util.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define LG_ASCII_CAP_AND_SMALL_DIFF 32

static char LG_char_to_lower(char c)
{
    return c + LG_ASCII_CAP_AND_SMALL_DIFF;
}

static bool LG_is_uppercase_char(char c)
{
    return c >= 'A' && c <= 'Z' ? true : false;
}

void LG_terminate_str(char* str, size_t pos)
{
    str[pos] = '\0';
}

void LG_clear_str(char* str)
{
    LG_terminate_str(str, 0);
}

bool LG_is_empty_str(char* str)
{
    return *str == '\0';
}

void LG_str_to_lower(char* str)
{
    while (*str != '\0')
    {
        if (LG_is_uppercase_char(*str))
        {
            *str = LG_char_to_lower(*str);
        }
        ++str;
    }
}
