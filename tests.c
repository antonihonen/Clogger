/*
 * File: tests.c
 * Project: logger
 * Created: 2019-04-15
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file contains the main function that automatically
 * runs tests.
 */

#include "time_handler.h"
#include "formatter.h"
#include <stdio.h>

int main()
{
	run_thandler_tests("TIME HANDLER TESTS\n");
	run_formatter_tests("FORMATTER TESTS\n");
	printf("\nTests passed, press Enter to finish.\n");
	char str[2];
	fgets(str, 2, stdin);
	return 0;
}