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
    log_t* log = log_init((char*)"D:\\log_perftest\\%(year)_%(month)_%(mday)_%(hour)_%(min)_%(sec)", (char*)"%(hour)_%(min)_%(sec).log", ROTATE, _IOFBF);
    log_set_entry_format(log, e_format);
    log_set_max_fsize(log, 131072);
    size_t entries = 0;
    while ((end_time - begin_time) < duration)
    {
        log_write(log, L_CRITICAL, msg);
        time(&end_time);
        ++entries;
    }
    printf("  Total entries: %u\n", entries);
    printf("  Entries per sec: %u\n", entries / (end_time - begin_time));
}

#endif /* PERFTEST_H */
