#ifndef __PERFTEST_H
#define __PERFTEST_H

#include "../prod/log.h"
#include <time.h>

#include <stdint.h>

void run_perftest(char* e_format, char* msg, time_t duration)
{
	printf("PERFTEST\n");
	time_t begin_time; time(&begin_time);
	time_t end_time = 0;
	log_t* log = log_init((char*)"D:\\log_perftest\\%(hour)_%(min)_%(sec)", (char*)"%(hour)_%(min)_%(sec).log", ROTATE, _IOFBF);
	log_set_entry_format(log, e_format);
	log_set_max_fsize(log, 100);
	size_t entries = 0;
	char dirname[256];
	char fname[256];
	char fpath[256];
	while ((end_time - begin_time) < duration)
	{
		log_write(log, L_CRITICAL, msg);
		time(&end_time);
		++entries;
		printf("dirname = %s\n", log_curr_dirname(log, dirname));
		printf("fname   = %s\n", log_curr_fname(log, fname));
		printf("fpath   = %s\n", log_curr_fpath(log, fpath));
		for (uint64_t i = 0; i < 0xFFFFFFFFUL / 4; ++i);
	}
	printf("  Total entries: %u\n", entries);
	printf("  Entries per sec: %u\n", entries / (end_time - begin_time));
}

#endif /* PERFTEST_H */
