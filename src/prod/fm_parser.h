#ifndef _FM_PARSER_H
#define _FM_PARSER_H

#include "format_macro_handlers.h"
#include "format_macro.h"

/* Checks that macro conforms to the valid form defined in
format_macro.h, then writes the string between the two
delimiters to dest, adding the null terminator.
Macro_len will indicate how many characters there were
from _FM_BEGIN_INDIC to _FM_RIGHT_DELIM (inclusive) -
the formatter can jump that many characters in the format
string since those characters have been handled.
If the macro is incomplete, only _FM_BEGIN_INDIC will
be written into dest (and macro_len will be 1).
*/
void _fm_as_str(const char* macro, char* dest, size_t* const macro_len);

/* Figures what format macro macro contains
and stores the corresponding _FM_ID to macro_id.
Macro_form_len will contain the length of the macro format,
i.e. how many characters the macro occupies in the
format string, not including null terminator.
*/
_FM_ID _identify_fm(const char* const macro, size_t* const macro_len);

/* Expands the format macro in macro and writes
the result to dest without adding the
null terminator.
Th will be used to expand time-related macros.
Msg contains the log message entered by the user, if any.
Lvl contains the log level of the message, if any.
Macro_len will contain the number of characters the macro
format consisted of, exp_macro_len the same but
for the expanded macro.
If the macro format is invalid, only _FM_BEGIN_INDIC
is written to dest (macro_len and exp_macro_len will be 1). */
void _expand_fm(const char* macro, char* dest, thandler_t* const th,
    const char* msg, const LOG_LEVEL lvl, size_t* const macro_len,
    size_t* const exp_macro_len);

#endif /* _FM_PARSER_H */
