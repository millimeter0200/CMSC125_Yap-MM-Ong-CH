#ifndef JOBS_H
#define JOBS_H

#include <sys/types.h>

void add_background_job(pid_t pid);
void reap_background_jobs(void);

#endif
