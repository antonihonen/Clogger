/*
 * File: file_handler_test.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module contains tests for the file handler module.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "file_handler_test.h"
#include <assert.h>

fhandler_t* fh;

static void init_test()
{
	printf("  init_test");

	if (fh) { fh_close(fh); }

	fh = fh_init(FULL_BUFFERING, 1024, ROTATE, "D:\\logs\\%(year)_%(month)_%(mday)\\log.log", 1024 * 1024 * 8);
	assert(fh);
	fh = fh_init(NO_BUFFERING, 0, REWRITE, "D:\\logs\\%(year)_%(month)_%(mday)\\log.log", 0);
	assert(fh);

	fh_close(fh);
	printf(" -> OK\n");
}

void run_file_handler_tests(char* test_set_title)
{
	fh = NULL;
	printf(test_set_title);
	init_test();
}
