/*
 * File: alloc.c
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include <assert.h>
#include <malloc.h>

 /* Determines whether a call to LG_register_allocator will be effective
 or not. */
static bool LG_can_register_allocator = true;

/* Pointers to the active allocator and deallocator functions. */
static void* (*LG_alloc_fun)(size_t) = malloc;
static void (*LG_dealloc_fun)(void*) = free;

bool LG_register_allocator(void* (*alloc)(size_t), void (*dealloc)(void*))
{
    if (!LG_can_register_allocator)
    {
        return false;
    }
    LG_alloc_fun = alloc;
    LG_dealloc_fun = dealloc;
    return true;
}

void* LG_alloc(size_t size)
{
    return LG_alloc_fun(size);
}

void LG_dealloc(void* ptr)
{
    LG_dealloc_fun(ptr);
}
