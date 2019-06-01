/*
 * File: string_util.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains utilities that make handling
 * strings easier.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stddef.h>
#include <stdbool.h>

/* Writes '\0' in the ith char of str. */
void _terminate_str(char* str, size_t i);

/* Writes '\0' in the first char of str. */
void _clear_str(char* str);

/* Returns true if the first char in str is '\0'. */
bool _is_empty_str(char* str);

/* Writes the value of i to str with two digits.
Zero is used as prefix for i < 10, so 1
will turn into "01" and so on. */
void
_two_digit_int_to_str(int i, char* str);

/* Converts alphabetical characters in str to lowercase. */
void
_ascii_str_to_lower(char* str);

#endif /* STRING_UTIL_H */
