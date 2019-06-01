/*
 * File: time_handler.c
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "alloc.h"
#include "time_handler.h"
#include "string_util.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Used for easy implementation of thandler_get_mname(). */
static const char* const MONTHS[12] =
    { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
    "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };

/* Used for easy implementation of thandler_get_wday().
Starts from Sunday because in the struct tm returned by localtime()
tm_day value of 0 equals Sunday. */
static const char* const WEEKDAYS[7] =
    { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY",
    "THURSDAY", "FRIDAY", "SATURDAY" };

thandler_t* th_init()
{
    thandler_t* new_th = _log_alloc(sizeof(thandler_t));
    struct tm* new_ltime = _log_alloc(sizeof(struct tm));
    if (!new_th || !new_ltime)
    {
        if (new_th)
        {
            _log_dealloc(new_th);
        }
        return NULL;
    }
    new_th->_ltime = new_ltime;
    new_th->_is_enabled = true;
    
    return new_th;
}

void th_close(thandler_t* th)
{
    _log_dealloc(th->_ltime);
    _log_dealloc(th);
}

bool th_has_legal_state(thandler_t* th)
{
    return th->_ltime != NULL ? true : false;
}

void th_fetch_ltime(thandler_t* th)
{
    if (th->_is_enabled)
    {
        time_t raw_time;
        time(&raw_time);
        /* Create a static copy of the struct returned by localtime(). */
        memcpy(th->_ltime, localtime(&raw_time), sizeof(struct tm));
    }
}

void th_lock(thandler_t* th)
{
    th->_is_enabled = false;
}

void th_unlock(thandler_t* th)
{
    th->_is_enabled = true;
}

void th_get_year(thandler_t* th, char* year)
{
    assert(th_has_legal_state(th));

    /* The year contained by _ltime is counted from 1900. */
    sprintf(year, "%i", 1900L + th->_ltime->tm_year);
}

void th_get_month(thandler_t* th, char* month)
{
    assert(th_has_legal_state(th));

    /* The month contained by local time is counted from 0. */
    _two_digit_int_to_str(th->_ltime->tm_mon + 1, month);
}

void th_get_mday(thandler_t* th, char* mday)
{
    assert(th_has_legal_state(th));

    _two_digit_int_to_str(th->_ltime->tm_mday, mday);
}

void th_get_hour(thandler_t* th, char* hour)
{
    assert(th_has_legal_state(th));

    _two_digit_int_to_str(th->_ltime->tm_hour, hour);
}

void th_get_min(thandler_t* th, char* min)
{
    assert(th_has_legal_state(th));

    _two_digit_int_to_str(th->_ltime->tm_min, min);
}

void th_get_sec(thandler_t* th, char* sec)
{
    assert(th_has_legal_state(th));

    _two_digit_int_to_str(th->_ltime->tm_sec, sec);
}

void th_get_mname(thandler_t* th, char* mname, _MNAME_FORMAT form)
{
    assert(th_has_legal_state(th));
    assert(form >= _MN_SHORT_FIRST_CAP);
    assert(form <= _MN_LONG_ALL_CAPS);

    /* Allocate enough space to accommodate the longest month name. */
    char full_name_in_caps[10];
    strcpy(full_name_in_caps, MONTHS[th->_ltime->tm_mon]);

    if (form == _MN_SHORT_FIRST_CAP || form == _MN_SHORT_ALL_CAPS)
    {
        /* The format is short so cut the full name after 3 chars. */
        full_name_in_caps[3] = '\0';
    }

    if (form == _MN_SHORT_FIRST_CAP || form == _MN_LONG_FIRST_CAP)
    {
        _ascii_str_to_lower(full_name_in_caps + 1);
    }

    /* At this point full_name_in_caps may no longer be the full name
    or in caps. */
    strcpy(mname, full_name_in_caps);
}

void th_get_wday(thandler_t* th, char* wday, _WDAY_FORMAT form)
{
    assert(th_has_legal_state(th));
    assert(form >= _WD_SHORT_FIRST_CAP);
    assert(form <= _WD_LONG_ALL_CAPS);

    /* Allocate enough space to accommodate the longest weekday name. */
    char full_name_in_caps[10];
    strcpy(full_name_in_caps, WEEKDAYS[th->_ltime->tm_wday]);

    if (form == _WD_SHORT_FIRST_CAP || form == _WD_SHORT_ALL_CAPS)
    {
        /* The format is short so cut the full name after 3 chars. */
        full_name_in_caps[3] = '\0';
    }

    if (form == _WD_SHORT_FIRST_CAP || form == _WD_LONG_FIRST_CAP)
    {
        _ascii_str_to_lower(full_name_in_caps + 1);
    }

    strcpy(wday, full_name_in_caps);
}
