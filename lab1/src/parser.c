#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

int parse_input(char *input, Command *cmd)
{
    char *token;
    int arg_index = 0;

    // remove newline if present
    input[strcspn(input, "\n")] = '\0';

    // tokenize by whitespace
    token = strtok(input, " \t");

    while (token != NULL)
    {
        // INPUT REDIRECTION
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " \t");
            if (token == NULL) {
                printf("Error: missing input file\n");
                return -1;
            }
            cmd->input_file = token;
        }

        // OUTPUT REDIRECTION (overwrite)
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, " \t");
            if (token == NULL) {
                printf("Error: missing output file\n");
                return -1;
            }
            cmd->output_file = token;
            cmd->append = 0;
        }

        // OUTPUT REDIRECTION (append)
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, " \t");
            if (token == NULL) {
                printf("Error: missing output file\n");
                return -1;
            }
            cmd->output_file = token;
            cmd->append = 1;
        }

        // BACKGROUND EXECUTION
        else if (strcmp(token, "&") == 0)
        {
            cmd->background = 1;
        }

        // NORMAL ARGUMENT
        else
        {
            cmd->args[arg_index++] = token;
        }

        token = strtok(NULL, " \t");
    }

    // no command entered
    if (arg_index == 0)
        return -1;

    // first argument is command
    cmd->command = cmd->args[0];

    // NULL terminate args for execvp
    cmd->args[arg_index] = NULL;

    return 0;
}
