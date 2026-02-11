#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "executor.h"
#include "jobs.h"

void execute_command(Command *cmd)
{
    if (cmd->command == NULL)
        return;

    // -------------------------
    // BUILT-IN COMMANDS
    // -------------------------

    // exit
    if (strcmp(cmd->command, "exit") == 0) {
        exit(0);
    }

    // cd
    if (strcmp(cmd->command, "cd") == 0) {
        if (cmd->args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(cmd->args[1]) != 0)
                perror("cd");
        }
        return;
    }

    // pwd
    if (strcmp(cmd->command, "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);
        else
            perror("pwd");
        return;
    }

    // -------------------------
    // EXTERNAL COMMANDS
    // -------------------------

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // CHILD PROCESS
        execvp(cmd->command, cmd->args);
        perror("execvp");
        exit(127);
    } else {
        // PARENT PROCESS

        if (cmd->background) {
            add_background_job(pid);
            printf("[bg] started PID %d\n", pid);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}
