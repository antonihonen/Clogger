/*
 * File: alloc.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains utilities related to memory
 * allocation and deallocation: custom allocators
 * and deallocators are supported.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include <stdbool.h>

#ifndef __ALLOC_H
#define __ALLOC_H

/* Determines whether a call to __register_alloc will be effective
or not. */
static bool __CAN_REGISTER_ALLOC = true;

/* Registers a custom allocator and deallocator that will be used
instead of malloc and free to reserve and free memory within the
library. This function must be called prior to calling any
other functions in the library in order to be effective. */
extern inline bool __register_alloc(void* (*alloc)(size_t), void(*dealloc)(void*));

/* Returns the allocator function. */
extern inline void* (*__get_alloc())(size_t);

/* Returns the deallocator function. */
extern inline void (*__get_dealloc())(void*);

#endif /* __ALLOC_H */
