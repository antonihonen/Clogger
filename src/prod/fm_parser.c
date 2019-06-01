#include "fm_parser.h"
#include <assert.h>
#include <string.h>

/* Returns a pointer to the macro handler corresponding with id. */
static _FM_HANDLER _get_fm_handler(const _FM_ID id)
{
    return _FM_TABLE[id].handler;
}

void _fm_as_str(const char* macro, char* dest, size_t* const macro_len)
{
    assert(*macro == _FM_BEGIN_INDIC);

    /* Save the initial state of dest. */
    char* dest_begin = dest;

    /* Indicates if _FM_RIGHT_DELIM has been encountered in the macro
    string. */
    bool has_ended = false;
    /* Indicates if _FM_LEFT_DELIM was encountered as the second char. */
    bool has_begun = false;
    /* Indicates whether the macro conforms to the format described in
    format_macro.h, except that in terms of this function the macro
    body doesn't need to be a valid one. */
    bool has_valid_format = true;
    *macro_len = 0;

    /* Read the macro string one character at a time until the macro
    either ends or is found to be invalid. */
    while (!has_ended)
    {
        switch (*macro)
        {
        case _FM_LEFT_DELIM:
            /* Only one _FM_LEFT_DELIM can be contained
            by a valid macro sequence and it must
            be the second character. */
            if (has_begun || *macro_len != 1)
            {
                has_valid_format = false;
                has_ended = true;
            }
            has_begun = true;
            break;
        case _FM_RIGHT_DELIM:
            /* _FM_LEFT_DELIM must come before _FM_RIGHT_DELIM */
            if (!has_begun)
            {
                has_valid_format = false;
            }
            has_ended = true;
            break;
        case _FM_BEGIN_INDIC:
            /* A valid macro cannot contain _FM_BEGIN_INDIC
            unless it's the first char. */
            if (*macro_len > 0)
            {
                has_valid_format = false;
                has_ended = true;
            }
            break;
        case '\0':
            /* End of macro string. */
            if (!has_begun || !has_ended)
            {
                has_valid_format = false;
            }
            has_ended = true;
            break;
        default:
            /* Only the characters forming the body of the macro
            is written into the macro_as_str buffer. */
            *dest = *macro;
            ++dest;
            break;
        }

        if (!has_valid_format)
        {
            /* Invalid format so write _FM_BEGIN_INDIC in the first
            char of the macro string. */
            *dest_begin = _FM_BEGIN_INDIC;
            dest = dest_begin + 1;
            /* Set length to 0 as if the last character,
            which caused the macro to be found invalid,
            was the first one. */
            *macro_len = 0;
        }

        ++*macro_len;

        if (has_ended)
        {
            /* Finish the macro string by appending null. */
            *dest = '\0';
        }

        /* Move on to the next char of the macro. */
        ++macro;
    }
}

_FM_ID _identify_fm(const char* const macro, size_t* const macro_len)
{
    assert(*macro == _FM_BEGIN_INDIC);

    /* Get the macro as a string as well as the number of
    characters the macro sequence consists of. */
    char macro_as_str[_MAX_FM_S_LEN];
    _fm_as_str(macro, macro_as_str, macro_len);

    if (*macro_len == 1 && strncmp(macro_as_str, "%", 1) == 0)
    {
        return _FM_NO_MACRO;
    }

    /* Iterate through the strings in _FM_TABLE and see if
    one of them matches. The indices of the macro strings
    in _FM_TABLE match their respective _FM_IDs so
    i == _FM_ID. */
    for (size_t i = 0; i < _FM_COUNT; ++i)
    {
        if (strcmp(macro_as_str, _FM_TABLE[i].str) == 0)
        {
            /* Match. */
            return i;
        }
    }

    /* No match. */
    return _FM_NO_MACRO;
}

void _expand_fm(const char* macro, char* dest, thandler_t* const th,
    const char* msg, const LOG_LEVEL lvl, size_t* const macro_len,
    size_t* const exp_macro_len)
{
    assert(*macro == _FM_BEGIN_INDIC);
    /* Local time must have been fetched prior to call to this function. */
    assert(th_has_legal_state(th));

    /* Figure out which macro is in question. */
    _FM_ID macro_id = _identify_fm(macro, macro_len);

    if (macro_id != _FM_NO_MACRO)
    {
        /* Valid macro detected. Get and call the handler, it will
        expand the macro. */
        _get_fm_handler(macro_id)(th, dest, lvl, msg, exp_macro_len);
    }
    else
    {
        /* The "macro" was incomplete. Don't expand. */
        *macro_len = 0;
        *exp_macro_len = 0;
    }
}
