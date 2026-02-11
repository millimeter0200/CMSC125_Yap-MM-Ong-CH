#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

#define DELIM " \t"

static int is_operator(const char *token)
{
    return (
        strcmp(token, "<") == 0 ||
        strcmp(token, ">") == 0 ||
        strcmp(token, ">>") == 0 ||
        strcmp(token, "&") == 0
    );
}

int parse_input(char *input, Command *cmd)
{
    char *token;
    int arg_index = 0;

    // remove newline
    input[strcspn(input, "\n")] = '\0';

    // start tokenizing
    token = strtok(input, DELIM);

    // empty input
    if (token == NULL)
        return -1;

    while (token != NULL)
    {

        // INPUT REDIRECTION
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, DELIM);

            if (token == NULL || is_operator(token)) {
                printf("Error: expected input filename after <\n");
                return -1;
            }

            cmd->input_file = token;
        }

        // OUTPUT REDIRECTION (overwrite)
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, DELIM);

            if (token == NULL || is_operator(token)) {
                printf("Error: expected output filename after >\n");
                return -1;
            }

            cmd->output_file = token;
            cmd->append = 0;
        }

        // OUTPUT REDIRECTION (append)
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, DELIM);

            if (token == NULL || is_operator(token)) {
                printf("Error: expected output filename after >>\n");
                return -1;
            }

            cmd->output_file = token;
            cmd->append = 1;
        }

        // BACKGROUND EXECUTION
        else if (strcmp(token, "&") == 0)
        {
            // reject standalone '&'
            if (arg_index == 0) {
                printf("Error: '&' without command\n");
                return -1;
            }

            cmd->background = 1;
        }

        // NORMAL ARGUMENT
        else
        {
            cmd->args[arg_index++] = token;
        }

        token = strtok(NULL, DELIM);
    }

    // no command found
    if (arg_index == 0)
        return -1;

    // first argument is command name
    cmd->command = cmd->args[0];

    // NULL terminate for execvp
    cmd->args[arg_index] = NULL;

    return 0;
}
