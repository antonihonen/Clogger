#ifndef _PERFTEST_H
#define _PERFTEST_H

#include "../prod/log.h"
#include <time.h>

#include <stdint.h>

void run_perftest(char* e_format, char* msg, time_t duration)
{
    printf("PERFTEST\n");
    time_t begin_time; time(&begin_time);
    time_t end_time = 0;
    log_t* log = log_init((char*)"D:\\log_perftest\\%(year)_%(month)_%(mday)", "log.log", ROTATE, _IOFBF, _LOCK_FILE | _PRINT);
    log_set_entry_format(log, e_format);
    log_set_max_fsize(log, 131072UL * 16);
    size_t entries = 0;
    while ((end_time - begin_time) < duration)
    {
        log_write(log, L_CRITICAL, msg);
        time(&end_time);
        ++entries;
        for (size_t i = 0; i < 0xFFFF; ++i);
    }
    printf("  - Time elapsed: %u\n", duration);
    printf("  - Total entries: %u\n", entries);
    printf("  - Entries per sec: %u\n", entries / duration);
}

#endif /* PERFTEST_H */
