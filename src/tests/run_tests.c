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

#include "file_handler_test.h"
#include "formatter_test.h"
#include "perftest.h"
#include "time_handler_test.h"
#include <stdio.h>

int main()
{
    run_perftest("%(Wday_s) %(mday) %(Mname_s) %(year) %(hour) %(min) %(sec) %(LVL) %(MSG)\n", "Hello world!", 10);
    char str[2];
    fgets(str, 2, stdin);
    return 0;
}
