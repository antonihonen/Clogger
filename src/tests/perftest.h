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
    log_t* log = log_init((char*)"D:\\log_perftest\\%(year)_%(month)_%(mday)", "log.log", LG_FMODE_ROTATE, _IOFBF, LG_LOCK_FILE | LG_STDOUT);
    log_set_format(log, LG_TRACE, e_format);
    log_set_format(log, LG_DEBUG, e_format);
    log_set_format(log, LG_INFO, e_format);
    log_set_format(log, LG_NOTICE, e_format);
    log_set_format(log, LG_WARNING, e_format);
    log_set_format(log, LG_ERROR, e_format);
    log_set_format(log, LG_CRITICAL, e_format);
    log_set_format(log, LG_ALERT, e_format);
    log_set_format(log, LG_EMERGENCY , e_format);
    log_set_max_fsize(log, LG_TRACE, 1024 * 8);
    log_set_max_fsize(log, LG_DEBUG, 1024 * 8);
    log_set_max_fsize(log, LG_INFO, 1024 * 8);
    log_set_max_fsize(log, LG_NOTICE, 1024 * 8);
    log_set_max_fsize(log, LG_WARNING, 1024 * 8);
    log_set_max_fsize(log, LG_ERROR, 1024 * 8);
    log_set_max_fsize(log, LG_CRITICAL, 1024 * 8);
    log_set_max_fsize(log, LG_ALERT, 1024 * 8);
    log_set_max_fsize(log, LG_EMERGENCY, 1024 * 8);
    log_set_fname(log, LG_TRACE, "trace_log.log");
    log_set_fname(log, LG_DEBUG, "debug_log.log");
    log_set_fname(log, LG_INFO, "info_log.log");
    log_set_fname(log, LG_NOTICE, "notice_log.log");
    log_set_fname(log, LG_WARNING, "warning_log.log");
    log_set_fname(log, LG_ERROR, "error_log.log");
    log_set_fname(log, LG_CRITICAL, "critical_log.log");
    log_set_fname(log, LG_ALERT, "alert_log.log");
    log_set_fname(log, LG_EMERGENCY, "emergency_log.log");
    size_t entries = 0;
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

        time(&end_time);
        ++entries;
        for (size_t i = 0; i < 0xFFFFFF; ++i);
    }
    printf("  - Time elapsed: %u\n", duration);
    printf("  - Total entries: %u\n", entries);
    printf("  - Entries per sec: %u\n", entries / duration);
}

#endif /* PERFTEST_H */
