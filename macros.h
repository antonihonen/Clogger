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

// Maximum lengths of user-inputted strings.
#define __MAX_DIR_SIZE 512
#define __MAX_FILENAME_SIZE 256
#define __MAX_MSG_SIZE 256
#define __MAX_FORMAT_SIZE 128

// The sizes of expanded format macros.
#define __FM_YEAR_EXP_SIZE 5
#define __FM_MONTH_EXP_SIZE 3
#define __FM_MDAY_EXP_SIZE 3
#define __FM_HOUR_EXP_SIZE 3
#define __FM_MIN_EXP_SIZE 3
#define __FM_SEC_EXP_SIZE 3
#define __FM_MNAME_S_EXP_SIZE 3
#define __MAX_FM_MNAME_L_EXP_SIZE 10 // "september\0"
#define __FM_WDAY_S_EXP_SIZE 3
#define __MAX_FM_WDAY_L_EXP_SIZE 10 // "wednesday\0"

#endif // MACROS_H
