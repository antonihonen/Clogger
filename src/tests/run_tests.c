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

#include "perftest.h"
#include <stdio.h>

int main()
{
	run_perftest("%(year)-%(month)-%(mday) %(hour):%(min):%(sec) %(LVL) %(MSG)\n",
		"Hello! This is just a tiny little test message!",
		15);
	printf("\nTests passed, press Enter to finish.\n");
	char str[2];
	fgets(str, 2, stdin);
	return 0;
}
