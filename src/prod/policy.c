/*
 * File: policy.c
 * Project: logger
 * Author: Anton Ihonen, anton@ihonen.net
 *
 * Copyright (C) 2019. Anton Ihonen
 */

#include "policy.h"

const LG_FMODE LG_VALID_FMODES[LG_VALID_FMODE_COUNT] =
    { LG_FMODE_MANUAL, LG_FMODE_REWRITE, LG_FMODE_ROTATE };

/*
const LG_BMODE LG_VALID_BMODES[LG_VALID_BMODE_COUNT] =
    { LG_NBF, LG_LBF, LG_FBF };
*/
