#include <sys/wait.h>
#include <stdio.h>

#include "jobs.h"

#define MAX_JOBS 64

static pid_t jobs[MAX_JOBS];
static int job_count = 0;

void add_background_job(pid_t pid) {
    if (job_count < MAX_JOBS) {
        jobs[job_count++] = pid;
    }
}

void reap_background_jobs(void) {
    for (int i = 0; i < job_count; i++) {
        if (waitpid(jobs[i], NULL, WNOHANG) > 0) {
            jobs[i] = jobs[--job_count];
            i--;
        }
    }
}
