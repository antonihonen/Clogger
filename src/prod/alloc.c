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

 /* Determines whether a call to __register_alloc will be effective
 or not. */
static bool can_register_alloc = true;

/* Pointers to the active allocator and deallocator functions. */
static void* (*alloc_fun)(size_t) = malloc;
static void (*dealloc_fun)(void*) = free;

bool
log_register_allocator(void* (*alloc)(size_t), void (*dealloc)(void*))
{
	assert(alloc); assert(dealloc);

	if (!can_register_alloc) { return false; }

	alloc_fun = alloc;
	dealloc_fun = dealloc;
	return true;
}

void* _log_alloc(size_t size)
{
	return alloc_fun(size);
}

void _log_dealloc(void* ptr)
{
	dealloc_fun(ptr);
}