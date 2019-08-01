/*
 * File: policy.h
 * Project: logger
 * Author: Anton Ihonen, anton.ihonen@gmail.com
 *
 * This module defines file policies
 * and buffering policies supported by the library.
 * File policy determines what happens when
 * the current log file reaches its maximum size.
 * Buffering policy determines how log output is
 * buffered.
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#ifndef LG_POLICY_H
#define LG_POLICY_H

/* REWRITE: Only use one log file and whenever it gets full,
erase all data in the file and keep writing in the same file.
ROTATE: When the log file gets full, append a sequential
number to the file name.
IGNORE_EXCESS: When the file gets full, no longer accept
log writes until the file has been emptied by an external
process. */
typedef enum {
    LG_FMODE_NONE = 0,
    LG_FMODE_REWRITE = 1,
    LG_FMODE_ROTATE
} LG_FMODE;
#define LG_VALID_FMODE_COUNT LG_FMODE_ROTATE
const LG_FMODE LG_VALID_FMODES[LG_VALID_FMODE_COUNT];

/* These three buffering modes correspond 1:1 with the buffering modes
explained in the documentation of the setvbuf function(stdio.h).*/
typedef enum {
    LG_NBF = 1,
    LG_LBF,
    LG_FBF
} LG_BMODE;
#define LG_VALID_BMODE_COUNT LG_FBF
const LG_BMODE LG_VALID_BMODES[LG_VALID_BMODE_COUNT];

#endif /* LG_POLICY_H */
