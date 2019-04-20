/*
 * File: formatter_test.c
 * Project: logger
 * Created: 2019-04-19
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This file implements tests for the format.h module.
 */

#include "formatter_test.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>


void test_user_macro_as_str_single_pass(char* macro_seq, char* correct_result, size_t correct_size)
{
	assert(macro_seq); assert(correct_result); assert(correct_size);

	char result[128];
	size_t size;
	__user_macro_as_str(macro_seq, result, &size);
	assert(strcmp(result, correct_result) == 0);
	assert(size == correct_size);
}


void test_user_macro_as_str()
{
	printf("  test_user_macro_as_str\n");
	for (size_t i = 0; i < __UM_COUNT; ++i)
	{
		char* macro_sequence = malloc(strlen(__USER_MACROS[i]) + 4);
		char* correct_result = __USER_MACROS[i];
		size_t correct_size = strlen(correct_result) + 3;
		macro_sequence[0] = __UM_BEGIN_INDIC;
		macro_sequence[1] = __UM_LEFT_DELIM;
		strcpy(macro_sequence + 2, __USER_MACROS[i]);
		macro_sequence[correct_size - 1] = __UM_RIGHT_DELIM;
		macro_sequence[correct_size] = '\0';
		correct_size = strlen(macro_sequence);
		test_user_macro_as_str_single_pass(macro_sequence, correct_result, correct_size);
		free(macro_sequence);
	}

#define test_cases 3
	char* test_seqs[test_cases] = { "%(NOT_A_MACRO(", "%   not a macro ", "%)" };
	char* correct_results[test_cases] = { "%", "%", "%" };
	char* correct_sizes[test_cases] = { 1, 1, 1 };
	for (size_t i = 0; i < test_cases; ++i)
	{
		test_user_macro_as_str_single_pass(test_seqs[i],
			correct_results[i], correct_sizes[i]);
	}
	printf("  passed\n");
}

void test_identify_user_macro_single_pass(char* macro, __UM_ID correct_result)
{
	assert(macro);
	size_t macro_length = 0;
	__UM_ID result = -1;
	__identify_user_macro(macro, &result, &macro_length);
	assert(result == correct_result);
}

void test_identify_user_macro(void)
{
	printf("  test_identify_macro\n");
	for (size_t i = 0; i < __UM_COUNT; ++i)
	{
		char macro_seq[256] = "%(";
		strcat(macro_seq, __USER_MACROS[i]);
		strcat(macro_seq, ")");
		test_identify_user_macro_single_pass(macro_seq, i);
		strcat(macro_seq, " ");
		test_identify_user_macro_single_pass(macro_seq, i);
		strcat(macro_seq, "_");
		test_identify_user_macro_single_pass(macro_seq, i);
	}

	test_identify_user_macro_single_pass("%(year", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%     year", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%_(year)", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%_year)", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%_year", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%_(__)", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%_____", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%      ", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%     )", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%     ()", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%()", __UM_NO_MACRO);
	test_identify_user_macro_single_pass("%%", __UM_NO_MACRO);

	printf("  passed\n");
}

void run_formatter_tests(char* test_set_title)
{
	printf(test_set_title);
	test_user_macro_as_str();
	test_identify_user_macro();
}
