/*
 * File: policy.h
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
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

#include <stdio.h>

#ifndef LG_POLICY_H
#define LG_POLICY_H

typedef enum {
    LG_FMODE_NONE = 0,
    LG_FMODE_MANUAL = 1,
    LG_FMODE_REWRITE,
    LG_FMODE_ROTATE
} LG_FMODE;
#define LG_DEF_FMODE LG_FMODE_MANUAL
#define LG_VALID_FMODE_COUNT LG_FMODE_ROTATE
const LG_FMODE LG_VALID_FMODES[LG_VALID_FMODE_COUNT];

/*
typedef enum {
    LG_NBF = 1,
    LG_LBF,
    LG_FBF
} LG_BMODE;
*/
#define LG_DEF_BMODE _IOFBF
#define LG_VALID_BMODE_COUNT 3
/*
const LG_BMODE LG_VALID_BMODES[LG_VALID_BMODE_COUNT];
*/
#endif /* LG_POLICY_H */
