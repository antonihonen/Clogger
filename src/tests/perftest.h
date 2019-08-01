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
    log_set_entry_format(log, LG_L_TRACE, e_format);
    log_set_entry_format(log, LG_L_DEBUG, e_format);
    log_set_entry_format(log, LG_L_INFO, e_format);
    log_set_entry_format(log, LG_L_NOTICE, e_format);
    log_set_entry_format(log, LG_L_WARNING, e_format);
    log_set_entry_format(log, LG_L_ERROR, e_format);
    log_set_entry_format(log, LG_L_CRITICAL, e_format);
    log_set_entry_format(log, LG_L_ALERT, e_format);
    log_set_entry_format(log, LG_L_EMERGENCY , e_format);
    log_set_max_fsize(log, LG_L_TRACE, 1024 * 8);
    log_set_max_fsize(log, LG_L_DEBUG, 1024 * 8);
    log_set_max_fsize(log, LG_L_INFO, 1024 * 8);
    log_set_max_fsize(log, LG_L_NOTICE, 1024 * 8);
    log_set_max_fsize(log, LG_L_WARNING, 1024 * 8);
    log_set_max_fsize(log, LG_L_ERROR, 1024 * 8);
    log_set_max_fsize(log, LG_L_CRITICAL, 1024 * 8);
    log_set_max_fsize(log, LG_L_ALERT, 1024 * 8);
    log_set_max_fsize(log, LG_L_EMERGENCY, 1024 * 8);
    log_set_fname_format(log, LG_L_TRACE, "trace_log.log");
    log_set_fname_format(log, LG_L_DEBUG, "debug_log.log");
    log_set_fname_format(log, LG_L_INFO, "info_log.log");
    log_set_fname_format(log, LG_L_NOTICE, "notice_log.log");
    log_set_fname_format(log, LG_L_WARNING, "warning_log.log");
    log_set_fname_format(log, LG_L_ERROR, "error_log.log");
    log_set_fname_format(log, LG_L_CRITICAL, "critical_log.log");
    log_set_fname_format(log, LG_L_ALERT, "alert_log.log");
    log_set_fname_format(log, LG_L_EMERGENCY, "emergency_log.log");
    size_t entries = 0;
    while ((end_time - begin_time) < duration)
    {
        log_write(log, LG_L_TRACE, msg);
        log_write(log, LG_L_DEBUG, msg);
        log_write(log, LG_L_INFO, msg);
        log_write(log, LG_L_NOTICE, msg);
        log_write(log, LG_L_WARNING, msg);
        log_write(log, LG_L_ERROR, msg);
        log_write(log, LG_L_CRITICAL, msg);
        log_write(log, LG_L_ALERT, msg);
        log_write(log, LG_L_EMERGENCY, msg);

        time(&end_time);
        ++entries;
        for (size_t i = 0; i < 0xFFFFFF; ++i);
    }
    printf("  - Time elapsed: %u\n", duration);
    printf("  - Total entries: %u\n", entries);
    printf("  - Entries per sec: %u\n", entries / duration);
}

#endif /* PERFTEST_H */
