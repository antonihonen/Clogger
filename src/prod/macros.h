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

#ifndef LG_MACROS_H
#define LG_MACROS_H

#define LG_DEF_MAX_FSIZE 1048576 /* 1 MiB */
#define LG_DEF_THRESHOLD LG_TRACE
#define LG_DEF_ENTRY_FORMAT "%(MSG)\n"

#define LG_MAX_DIR_SIZE 512
#define LG_MAX_FNAME_SIZE 512
#define LG_MAX_MSG_SIZE 512
#define LG_MAX_EXP_FORMAT_SIZE 256
#define LG_MAX_E_FORMAT_SIZE 256
#define LG_MAX_ENTRY_SIZE 1024
#define LG_MAX_ERR_MSG_SIZE 256

/* The sizes of expanded format macros. */
#define LG_FM_YEAR_EXP_SIZE 5
#define LG_FM_MONTH_EXP_SIZE 3
#define LG_FM_MDAY_EXP_SIZE 3
#define LG_FM_HOUR_EXP_SIZE 3
#define LG_FM_MIN_EXP_SIZE 3
#define LG_FM_SEC_EXP_SIZE 3
#define LG_FM_MNAME_S_EXP_SIZE 3
#define LG_MAX_FM_MNAME_L_EXP_SIZE 10 /* "september" + null terminator */
#define LG_FM_WDAY_S_EXP_SIZE 3
#define LG_MAX_FM_WDAY_L_EXP_SIZE 10 /* "wednesday" + null terminator */

#endif /* LG_MACROS_H */
