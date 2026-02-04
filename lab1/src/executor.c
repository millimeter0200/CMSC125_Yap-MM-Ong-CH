#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "executor.h"
#include "jobs.h"

void execute_command(Command *cmd) {
    // TODO:
    // - handle built-in commands (exit, cd, pwd)
    // - fork and exec external commands
    // - handle I/O redirection
    // - handle background execution

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // child
        execvp(cmd->command, cmd->args);
        perror("execvp");
        _exit(127);
    } else {
        // parent
        if (cmd->background) {
            add_background_job(pid);
            printf("[bg] started pid %d\n", pid);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}
