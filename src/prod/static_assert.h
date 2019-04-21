/*
 * File: static_assert.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines a makeshift static
 * (compile-time) assert.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

// If cond is false, the array is initialized
// with a negative value. Msg will be concatenated
// to "static_assert_" so as to give an informative
// compiler warning.
#define __STATIC_ASSERT(cond, msg) \
	typedef char static_assert_##msg[(cond)? 1 : -1]
