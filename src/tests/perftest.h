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
    log_t* log = log_init(NULL);
    log_set_dname_format(log, LG_ALL_LEVELS, "D:\\log_perftest\\%(year)_%(month)_%(mday)");
    log_set_fname_format(log, LG_ALL_LEVELS, "log.log");
    log_set_fmode(log, LG_ALL_LEVELS, LG_FMODE_ROTATE);
    log_set_bmode(log, LG_ALL_LEVELS, _IOFBF);
    log_set_entry_format(log, LG_ALL_LEVELS, e_format);
    log_set_max_fsize(log, LG_ALL_LEVELS, 1024 * 8);
    log_set_fname_format(log, LG_TRACE, "trace_log.log");
    log_set_fname_format(log, LG_DEBUG, "debug_log.log");
    log_set_fname_format(log, LG_INFO, "info_log.log");
    log_set_fname_format(log, LG_NOTICE, "notice_log.log");
    log_set_fname_format(log, LG_WARNING, "warning_log.log");
    log_set_fname_format(log, LG_ERROR, "error_log.log");
    log_set_fname_format(log, LG_CRITICAL, "critical_log.log");
    log_set_fname_format(log, LG_ALERT, "alert_log.log");
    log_set_fname_format(log, LG_EMERGENCY, "emergency_log.log");
    log_set_fname_format(log, LG_FATAL, "fatal_log.log");
    log_enable_file(log, LG_ALL_LEVELS);
    size_t entries = 0;
    printf("log: %u\n", sizeof(log_t));
    printf("handler: %u\n", sizeof(fhandler_t));
    printf("formatter: %u\n", sizeof(formatter_t));
    while ((end_time - begin_time) < duration)
    {
        log_write(log, LG_TRACE, msg);
        log_write(log, LG_DEBUG, msg);
        log_write(log, LG_INFO, msg);
        log_write(log, LG_NOTICE, msg);
        log_write(log, LG_WARNING, msg);
        log_write(log, LG_ERROR, msg);
        log_write(log, LG_CRITICAL, msg);
        log_write(log, LG_ALERT, msg);
        log_write(log, LG_EMERGENCY, msg);
        log_write(log, LG_FATAL, msg);

        time(&end_time);
        ++entries;
        for (size_t i = 0; i < 0xFFFFFF; ++i);
    }
    printf("  - Time elapsed: %u\n", duration);
    printf("  - Total entries: %u\n", entries);
    printf("  - Entries per sec: %u\n", entries / duration);
}

#endif /* PERFTEST_H */
