/*
 * File: alloc.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include <stdbool.h>

inline bool __register_alloc(void* (*alloc)(size_t), void(*dealloc)(void*));

inline void* (*__get_alloc())(size_t);

inline void (*__get_dealloc())(void*);
