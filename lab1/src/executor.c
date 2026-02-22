#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h> //so that we can use open() for file redirection

#include "executor.h"
#include "jobs.h"

void execute_command(Command *cmd)
{
    if (cmd->command == NULL)
        return;

    // =========================
    // BUILT-IN COMMANDS
    // =========================


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

    // =========================
    // EXTERNAL COMMANDS
    // =========================

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {

        // INPUT REDIRECTION
        if (cmd->input_file) {
            int fd = open(cmd->input_file, O_RDONLY);
            if (fd < 0) {
                perror("open input");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // OUTPUT REDIRECTION
        if (cmd->output_file) {
            int flags = O_WRONLY | O_CREAT;
            if (cmd->append)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;

            int fd = open(cmd->output_file, flags, 0644);
            if (fd < 0) {
                perror("open output");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        // CHILD PROCESS
        // =========================

        // -------- INPUT REDIRECTION (<)
        if (cmd->input_file != NULL) {
            int fd = open(cmd->input_file, O_RDONLY);
            if (fd < 0) {
                perror("open input");
                exit(1);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // -------- OUTPUT REDIRECTION (> or >>)
        if (cmd->output_file != NULL) {

            int flags = O_WRONLY | O_CREAT;

            if (cmd->append)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;

            int fd = open(cmd->output_file, flags, 0644);

            if (fd < 0) {
                perror("open output");
                exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        // Execute program
        execvp(cmd->command, cmd->args);

        // If exec fails
        perror("execvp");
        exit(127);
    }
    else {
        // =========================
        // PARENT PROCESS
        // =========================

        if (cmd->background) {
            add_background_job(pid);
            printf("[bg] started PID %d\n", pid);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}


//update: Redirection is handled in the child process before execvp.
//We open the specified file, replace stdin or stdout using dup2, 
//then execute the command so it inherits the redirected descriptors.