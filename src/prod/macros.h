/*
 * File: macros.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines macros that multiple
 * modules in the project share.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef MACROS_H
#define MACROS_H

#define _MAX_DIR_SIZE 512
#define _MAX_FILENAME_SIZE 512
#define _MAX_MSG_SIZE 512
#define _MAX_EXP_FORMAT_SIZE 256
#define _MAX_E_FORMAT_SIZE 256
#define _MAX_ENTRY_SIZE 1024

/* The sizes of expanded format macros. */
#define _FM_YEAR_EXP_SIZE 5
#define _FM_MONTH_EXP_SIZE 3
#define _FM_MDAY_EXP_SIZE 3
#define _FM_HOUR_EXP_SIZE 3
#define _FM_MIN_EXP_SIZE 3
#define _FM_SEC_EXP_SIZE 3
#define _FM_MNAME_S_EXP_SIZE 3
#define _MAX_FM_MNAME_L_EXP_SIZE 10 /* "september" + null terminator */
#define _FM_WDAY_S_EXP_SIZE 3
#define _MAX_FM_WDAY_L_EXP_SIZE 10 /* "wednesday" + null terminator */

#endif /* MACROS_H */
