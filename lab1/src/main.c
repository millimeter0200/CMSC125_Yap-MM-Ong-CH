#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "parser.h"
#include "executor.h"
#include "jobs.h"

#define INPUT_SIZE 1024 //this is for when we read user input, we need a buffer to store it

int main(void) { //to handle Ctrl+D, we check for NULL return from fgets and break the loop to exit gracefully instead of crashing or entering an infinite loop
    char input[INPUT_SIZE];
    Command cmd;

    while (1) {
        reap_background_jobs();

        printf("mysh > ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        if (input[0] == '\n') {
            continue;
        }

        init_command(&cmd);

        if (parse_input(input, &cmd) == 0) {
            execute_command(&cmd);
        }

        free_command(&cmd);
    }

    return 0;
}
// Reap finished background jobs before showing the prompt to prevent zombie processes.