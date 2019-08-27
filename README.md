# Clogger - a C99 logging library

**What it can do:**
- format output and file paths (for example, `%(year)-%(month)-%(mday) %(LVL)`
`%(MSG)\n` could be expanded to `2019-08-27 DEBUG Did that thing there\n`)
- split output in files of user-specified maximum size (strict or non-strict)
- output to both stdout, stderr, ordinary file and user-defined function
- write in files at a _ridiculous_ rate (1,250,000 short-ish formatted
log entries per second on an Intel i7-4790K and Western Digital Blue 7200 RPM
HDD in Windows 10)
- use a user-defined memory allocation scheme
