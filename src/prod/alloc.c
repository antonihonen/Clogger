/*
 * File: alloc.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include <assert.h>
#include <malloc.h>

/* Pointers to the active allocator and deallocator functions. */
static void* (*__ALLOC_FUN)(size_t) = malloc;
static void (*__DEALLOC_FUN)(void*) = free;

bool
__register_alloc(void* (*alloc)(size_t), void (*dealloc)(void*))
{
	assert(alloc); assert(dealloc);

	if (!__CAN_REGISTER_ALLOC) { return false; }

	__ALLOC_FUN = alloc;
	__DEALLOC_FUN = dealloc;
	return true;
}

void* (*__get_alloc())(size_t)
{
	return __ALLOC_FUN;
}

void (*__get_dealloc())(void*)
{
	return __DEALLOC_FUN;
}
