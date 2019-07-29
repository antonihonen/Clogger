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
    log_set_entry_format(log, L_TRACE, e_format);
    log_set_entry_format(log, L_DEBUG, e_format);
    log_set_entry_format(log, L_INFO, e_format);
    log_set_entry_format(log, L_NOTICE, e_format);
    log_set_entry_format(log, L_WARNING, e_format);
    log_set_entry_format(log, L_ERROR, e_format);
    log_set_entry_format(log, L_CRITICAL, e_format);
    log_set_entry_format(log, L_ALERT, e_format);
    log_set_entry_format(log, L_EMERGENCY , e_format);
    log_set_max_fsize(log, L_TRACE, 1024 * 8);
    log_set_max_fsize(log, L_DEBUG, 1024 * 8);
    log_set_max_fsize(log, L_INFO, 1024 * 8);
    log_set_max_fsize(log, L_NOTICE, 1024 * 8);
    log_set_max_fsize(log, L_WARNING, 1024 * 8);
    log_set_max_fsize(log, L_ERROR, 1024 * 8);
    log_set_max_fsize(log, L_CRITICAL, 1024 * 8);
    log_set_max_fsize(log, L_ALERT, 1024 * 8);
    log_set_max_fsize(log, L_EMERGENCY, 1024 * 8);
    log_set_fname_format(log, L_TRACE, "trace_log.log");
    log_set_fname_format(log, L_DEBUG, "debug_log.log");
    log_set_fname_format(log, L_INFO, "info_log.log");
    log_set_fname_format(log, L_NOTICE, "notice_log.log");
    log_set_fname_format(log, L_WARNING, "warning_log.log");
    log_set_fname_format(log, L_ERROR, "error_log.log");
    log_set_fname_format(log, L_CRITICAL, "critical_log.log");
    log_set_fname_format(log, L_ALERT, "alert_log.log");
    log_set_fname_format(log, L_EMERGENCY, "emergency_log.log");
    size_t entries = 0;
    while ((end_time - begin_time) < duration)
    {
        log_write(log, L_TRACE, msg);
        log_write(log, L_DEBUG, msg);
        log_write(log, L_INFO, msg);
        log_write(log, L_NOTICE, msg);
        log_write(log, L_WARNING, msg);
        log_write(log, L_ERROR, msg);
        log_write(log, L_CRITICAL, msg);
        log_write(log, L_ALERT, msg);
        log_write(log, L_EMERGENCY, msg);

        time(&end_time);
        ++entries;
        for (size_t i = 0; i < 0xFFFFFF; ++i);
    }
    printf("  - Time elapsed: %u\n", duration);
    printf("  - Total entries: %u\n", entries);
    printf("  - Entries per sec: %u\n", entries / duration);
}

#endif /* PERFTEST_H */
