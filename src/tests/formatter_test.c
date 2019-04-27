/*
 * File: formatter_test.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "formatter_test.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/* Global for convenience. */
fn_format_t* fnf;
e_format_t* ef;
thandler_t* th;

static const int TEST_YEAR = 100;
static const char* const TEST_YEAR_S = "2000";
static const int TEST_MON = 0;
static const char* const TEST_MON_S = "01";
static const int TEST_MDAY = 31;
static const char* const TEST_MDAY_S = "31";
static const int TEST_HOUR = 6;
static const char* const TEST_HOUR_S = "06";
static const int TEST_MIN = 7;
static const char* const TEST_MIN_S = "07";
static const int TEST_SEC = 8;
static const char* const TEST_SEC_S = "08";
static const int TEST_WDAY = 0;
static const char* const TEST_MNAME_S = "JANUARY";
static const char* const TEST_WDAY_S = "SUNDAY";

/* Single application of the test. */
static void
test_fm_as_str_s(char* macro_seq, char* correct_result, size_t correct_size)
{
	char result[128];
	size_t size;
	__fm_as_str(macro_seq, result, &size);
	assert(strcmp(result, correct_result) == 0);
	assert(size == correct_size);
}

/* Runs tests for the __fm_as_str() function. */
static void
test_fm_as_str()
{
	printf("  test_fm_as_str");
	
	/* Test all the valid macros first. */
	for (size_t i = 0; i < __FM_COUNT; ++i)
	{
		/* Allocate memory. +4 because strlen doesn't count null
		terminator and __FM_BEGIN_INDIC, __FM_LEFT_DELIM and
		__FM_RIGHT_DELIM will be added. */
		char* macro_sequence = malloc(strlen(__FORMAT_MACROS[i]) + 4);
		const char* correct_result = __FORMAT_MACROS[i];
		size_t correct_size = strlen(correct_result) + 3;
		macro_sequence[0] = __FM_BEGIN_INDIC;
		macro_sequence[1] = __FM_LEFT_DELIM;
		strcpy(macro_sequence + 2, __FORMAT_MACROS[i]);
		macro_sequence[correct_size - 1] = __FM_RIGHT_DELIM;
		macro_sequence[correct_size] = '\0';
		correct_size = strlen(macro_sequence);
		test_fm_as_str_s(macro_sequence, correct_result, correct_size);
		free(macro_sequence);
	}

	/* Test invalid macros. */
	#define fm_as_str_inv_test_cases 5
	char* test_seqs[fm_as_str_inv_test_cases] =
		{ "%(NOT_A_MACRO(", "%   not a macro ", "%)",
		"%(year", "%year" };
	char* correct_results[fm_as_str_inv_test_cases] = { "%", "%", "%", "%", "%" };
	size_t correct_sizes[fm_as_str_inv_test_cases] = { 1, 1, 1, 1, 1 };
	for (size_t i = 0; i < fm_as_str_inv_test_cases; ++i)
	{
		test_fm_as_str_s(test_seqs[i],
			correct_results[i], correct_sizes[i]);
	}

	printf("  -> OK\n");
}

static void
test_identify_fm_s(char* macro, __FM_ID correct_result)
{
	size_t macro_length = 0;
	__FM_ID result = -1;
	__identify_fm(macro, &result, &macro_length);
	assert(result == correct_result);
}

static void
test_identify_fm(void)
{
	printf("  test_identify_fm");
	for (size_t i = 0; i < __FM_COUNT; ++i)
	{
		char macro_seq[256] = "%(";
		strcat(macro_seq, __FORMAT_MACROS[i]);
		strcat(macro_seq, ")");
		test_identify_fm_s(macro_seq, i);
		strcat(macro_seq, " ");
		test_identify_fm_s(macro_seq, i);
		strcat(macro_seq, "_");
		test_identify_fm_s(macro_seq, i);
	}

	test_identify_fm_s("%(year", __FM_NO_MACRO);
	test_identify_fm_s("%     year", __FM_NO_MACRO);
	test_identify_fm_s("%_(year)", __FM_NO_MACRO);
	test_identify_fm_s("%_year)", __FM_NO_MACRO);
	test_identify_fm_s("%_year", __FM_NO_MACRO);
	test_identify_fm_s("%_(__)", __FM_NO_MACRO);
	test_identify_fm_s("%_____", __FM_NO_MACRO);
	test_identify_fm_s("%      ", __FM_NO_MACRO);
	test_identify_fm_s("%     )", __FM_NO_MACRO);
	test_identify_fm_s("%     ()", __FM_NO_MACRO);
	test_identify_fm_s("%()", __FM_NO_MACRO);
	test_identify_fm_s("%%", __FM_NO_MACRO);

	printf("  -> OK\n");
}

static void
test_expand_fm_s(thandler_t* thandler, char* macro,
	char* message, LOG_LEVEL lvl, char* correct_result,
	size_t correct_skip_over)
{
	char result[__MAX_MSG_SIZE];
	size_t skip_over_result = 0;
	size_t exp_macro_len = 0;
	__expand_fm(macro, result, thandler, message, lvl, &skip_over_result, &exp_macro_len);
	/* Compare only as many characters as the result contains, since
	no null terminator is added to the string in __expand_fm(). */
	assert(strncmp(result, correct_result, strlen(correct_result) - 1) == 0);
	/* TODO: Check that no null terminator was added. Not implemented yet. */
/*  assert(result[strlen(result)] != '\0'); */
	assert(skip_over_result == correct_skip_over);
}

static void
test_expand_fm()
{
	printf("  test_expand_macro");

	char* message = "this is a message";
	test_expand_fm_s(th, "%(year)", message,
		L_TRACE, "2000", sizeof("%(year)") - 1);
	test_expand_fm_s(th, "%(month)", message,
		L_TRACE, "01", sizeof("%(month)") - 1);
	test_expand_fm_s(th, "%(mday)", message,
		L_TRACE, "31", sizeof("%(mday)") - 1);
	test_expand_fm_s(th, "%(hour)", message,
		L_TRACE, "06", sizeof("%(hour)") - 1);
	test_expand_fm_s(th, "%(min)", message,
		L_TRACE, "07", sizeof("%(min)") - 1);
	test_expand_fm_s(th, "%(sec)", message,
		L_TRACE, "08", sizeof("%(sec)") - 1);
	test_expand_fm_s(th, "%(mname_s)", message,
		L_TRACE, "jan", sizeof("%(mname_s)") - 1);
	test_expand_fm_s(th, "%(Mname_s)", message,
		L_TRACE, "Jan", sizeof("%(mname_s)") - 1);
	test_expand_fm_s(th, "%(MNAME_S)", message,
		L_TRACE, "JAN", sizeof("%(MNAME_S)") - 1);
	test_expand_fm_s(th, "%(mname_l)", message,
		L_TRACE, "january", sizeof("%(mname_l)") - 1);
	test_expand_fm_s(th, "%(Mname_l)", message,
		L_TRACE, "January", sizeof("%(Mname_l)") - 1);
	test_expand_fm_s(th, "%(MNAME_L)", message,
		L_TRACE, "JANUARY", sizeof("%(MNAME_L)") - 1);
	test_expand_fm_s(th, "%(wday_s)", message,
		L_TRACE, "sun", sizeof("%(wday_s)") - 1);
	test_expand_fm_s(th, "%(Wday_s)", message,
		L_TRACE, "Sun", sizeof("%(Wday_s)") - 1);
	test_expand_fm_s(th, "%(WDAY_S)", message,
		L_TRACE, "SUN", sizeof("%(WDAY_S)") - 1);
	test_expand_fm_s(th, "%(wday_l)", message,
		L_TRACE, "sunday", sizeof("%(wday_l)") - 1);
	test_expand_fm_s(th, "%(Wday_l)", message,
		L_TRACE, "Sunday", sizeof("%(Wday_l)") - 1);
	test_expand_fm_s(th, "%(WDAY_L)", message,
		L_TRACE, "SUNDAY", sizeof("%(WDAY_L)") - 1);
	/* Not implemented yet.
	test_expand_macro_single_pass(thandler, "%(lvl)", message,
		L_TRACE, "trace", sizeof("%(LVL)") - 1);
	test_expand_macro_single_pass(thandler, "%(Lvl)", message,
		L_TRACE, "Trace", sizeof("%(LVL)") - 1); */
	test_expand_fm_s(th, "%(LVL)", message,
		L_TRACE, "TRACE", sizeof("%(LVL)") - 1);
	test_expand_fm_s(th, "%(MSG)", message,
		L_TRACE, message, sizeof("%(MSG)") - 1);

	/* Test cases for invalid macros. */
	test_expand_fm_s(th, "% (", message,
		L_TRACE, "%", sizeof("%") - 1);
	test_expand_fm_s(th, "%__", message,
		L_TRACE, "%", sizeof("%") - 1);
	test_expand_fm_s(th, "%     ", message,
		L_TRACE, "%", sizeof("%") - 1);
	test_expand_fm_s(th, "%__", message,
		L_TRACE, "%", sizeof("%") - 1);

	printf("  -> OK\n");
}

void test_fn_format_s(fn_format_t* fnf, char* format, char* correct_result)
{
	char result[512];
	fnf_set_format(fnf, format);
	fnf_format(fnf, result);
	assert(strcmp(result, correct_result) == 0);
}

void test_fn_format(void)
{
	printf("  test_fn_format");
	char* format = "%(year)-%(month)-%(mday).log";
	char result[512];
	char result_f[512] = "%s-%s-%s.log";
	sprintf(result, result_f, TEST_YEAR_S, TEST_MON_S, TEST_MDAY_S);
	test_fn_format_s(fnf, format, result);
	printf(" -> OK\n");
}

void
run_formatter_tests(char* test_set_title)
{
	printf(test_set_title);

	/* Set up the global objects. */
	th = malloc(sizeof(thandler_t));
	thandler_init(th);
	/* Set thandler time to be constant. */
	thandler_fetch_ltime(th);
	th->_is_testing = true; /* Time can't be fetched anymore. */
	th->_last_fetch->tm_year = TEST_YEAR;
	th->_last_fetch->tm_mon = TEST_MON;
	th->_last_fetch->tm_mday = TEST_MDAY;
	th->_last_fetch->tm_hour = TEST_HOUR;
	th->_last_fetch->tm_min = TEST_MIN;
	th->_last_fetch->tm_sec = TEST_SEC;
	th->_last_fetch->tm_wday = TEST_WDAY;
	fnf = fnf_init("");
	/* Swap the thandler so that the tests can use the rigged one
	we set up above. */
	thandler_close(fnf->_thandler);
	free(fnf->_thandler);
	fnf->_thandler = th;

	/* Execute tests. */
	test_fm_as_str();
	test_identify_fm();
	test_expand_fm();
	test_fn_format();

	fnf_close(fnf);
	thandler_close(th);
}
