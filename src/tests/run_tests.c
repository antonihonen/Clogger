/*
 * File: run_tests.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file contains the main function that automatically
 * runs tests for the project.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "time_handler_test.h"
#include "formatter_test.h"
#include "file_handler_test.h"
#include <stdio.h>

int main()
{
	run_time_handler_tests("TIME HANDLER TESTS\n");
	printf("\n");
	run_formatter_tests("FORMATTER TESTS\n");
	printf("\n");
	run_file_handler_tests("FILE HANDLER TESTS\n");
	printf("\nTests passed, press Enter to finish.\n");
	char str[2];
	fgets(str, 2, stdin);
	return 0;
}
