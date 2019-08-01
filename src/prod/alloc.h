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
#include <stddef.h>

#ifndef LG_ALLOC_H
#define LG_ALLOC_H

/* Registers a custom allocator and deallocator that will be used
instead of malloc and free to reserve and free memory within the
library. This function must be called prior to calling any
other functions in the library in order to be effective. */
bool LG_register_allocator(void* (*alloc)(size_t), void (*dealloc)(void*));

void* LG_alloc(size_t size);

void LG_dealloc(void* ptr);

#endif /* LG_ALLOC_H */
