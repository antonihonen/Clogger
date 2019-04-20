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
#include <string.h>

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
		const char* correct_result = __USER_MACROS[i];
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

#define test_cases 5
	char* test_seqs[test_cases] =
		{ "%(NOT_A_MACRO(", "%   not a macro ", "%)",
		"%(year", "%year" };
	char* correct_results[test_cases] = { "%", "%", "%", "%", "%" };
	size_t correct_sizes[test_cases] = { 1, 1, 1, 1, 1 };
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
	printf("  test_identify_user_macro\n");
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

void test_expand_macro_single_pass(thandler_t* thandler, char* macro,
	char* message, LOG_LEVEL lvl, char* correct_result, size_t correct_skip_over)
{
	char* result[__MAX_MSG_SIZE];
	size_t skip_over_result = 0;
	__expand_macro(thandler, result, macro, message, lvl, &skip_over_result);
	printf("result = '%s'\n", result);
	printf("correct = '%s'\n", correct_result);
	assert(strcmp(result, correct_result) == 0);
	assert(skip_over_result == correct_skip_over);
}

void test_expand_macro()
{
	printf("  test_expand_macro\n");

	thandler_t* thandler = malloc(sizeof(thandler_t));
	thandler_init(thandler);
	thandler->_last_fetch = malloc(sizeof(struct tm));
	thandler->_last_fetch->tm_year = 100;
	thandler->_last_fetch->tm_mon = 0;
	thandler->_last_fetch->tm_mday = 31;
	thandler->_last_fetch->tm_hour = 6;
	thandler->_last_fetch->tm_min = 7;
	thandler->_last_fetch->tm_sec = 8;
	thandler->_last_fetch->tm_wday = 0;
	thandler->_is_testing = true;
	char* message = "this is a message";
	test_expand_macro_single_pass(thandler, "%(year)", message,
		L_TRACE, "2000", sizeof("%(year)") - 1);
	test_expand_macro_single_pass(thandler, "%(month)", message,
		L_TRACE, "01", sizeof("%(month)") - 1);
	test_expand_macro_single_pass(thandler, "%(mday)", message,
		L_TRACE, "31", sizeof("%(mday)") - 1);
	test_expand_macro_single_pass(thandler, "%(hour)", message,
		L_TRACE, "06", sizeof("%(hour)") - 1);
	test_expand_macro_single_pass(thandler, "%(min)", message,
		L_TRACE, "07", sizeof("%(min)") - 1);
	test_expand_macro_single_pass(thandler, "%(sec)", message,
		L_TRACE, "08", sizeof("%(sec)") - 1);
	test_expand_macro_single_pass(thandler, "%(mname_s)", message,
		L_TRACE, "jan", sizeof("%(mname_s)") - 1);
	test_expand_macro_single_pass(thandler, "%(Mname_s)", message,
		L_TRACE, "Jan", sizeof("%(mname_s)") - 1);
	test_expand_macro_single_pass(thandler, "%(MNAME_S)", message,
		L_TRACE, "JAN", sizeof("%(MNAME_S)") - 1);
	test_expand_macro_single_pass(thandler, "%(mname_l)", message,
		L_TRACE, "january", sizeof("%(mname_l)") - 1);
	test_expand_macro_single_pass(thandler, "%(Mname_l)", message,
		L_TRACE, "January", sizeof("%(Mname_l)") - 1);
	test_expand_macro_single_pass(thandler, "%(MNAME_L)", message,
		L_TRACE, "JANUARY", sizeof("%(MNAME_L)") - 1);
	test_expand_macro_single_pass(thandler, "%(wday_s)", message,
		L_TRACE, "sun", sizeof("%(wday_s)") - 1);
	test_expand_macro_single_pass(thandler, "%(Wday_s)", message,
		L_TRACE, "Sun", sizeof("%(Wday_s)") - 1);
	test_expand_macro_single_pass(thandler, "%(WDAY_S)", message,
		L_TRACE, "SUN", sizeof("%(WDAY_S)") - 1);
	test_expand_macro_single_pass(thandler, "%(wday_l)", message,
		L_TRACE, "sunday", sizeof("%(wday_l)") - 1);
	test_expand_macro_single_pass(thandler, "%(Wday_l)", message,
		L_TRACE, "Sunday", sizeof("%(Wday_l)") - 1);
	test_expand_macro_single_pass(thandler, "%(WDAY_L)", message,
		L_TRACE, "SUNDAY", sizeof("%(WDAY_L)") - 1);
	// Not implemented yet.
//	test_expand_macro_single_pass(thandler, "%(lvl)", message,
//		L_TRACE, "trace", sizeof("%(LVL)") - 1);
//	test_expand_macro_single_pass(thandler, "%(Lvl)", message,
//		L_TRACE, "Trace", sizeof("%(LVL)") - 1);
	test_expand_macro_single_pass(thandler, "%(LVL)", message,
		L_TRACE, "TRACE", sizeof("%(LVL)") - 1);
	test_expand_macro_single_pass(thandler, "%(MSG)", message,
		L_TRACE, message, sizeof("%(MSG)") - 1);
	thandler_close(thandler);
	free(thandler->_last_fetch);
	free(thandler);
	printf("  passed\n");
}

void run_formatter_tests(char* test_set_title)
{
	printf(test_set_title);
	test_user_macro_as_str();
	test_identify_user_macro();
	test_expand_macro();
}
