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

    input[strcspn(input, "\n")] = '\0';

    token = strtok(input, DELIM);

    if (token == NULL)
        return -1;

    while (token != NULL)
    {

        // INPUT REDIRECTION
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, DELIM);

            if (token == NULL || is_operator(token)) {
                fprintf(stderr, "Error: expected input filename after <\n"); //stderr is to ensure error messages are visible even when stdout is redirected to a file
                return -1;
            }
            char *copy = strdup(token);
            if (!copy) {
                perror("strdup");
                return -1;
            }
            cmd->input_file = copy;
        }

        // OUTPUT REDIRECTION (overwrite)
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, DELIM);

            if (token == NULL || is_operator(token)) {
                fprintf(stderr, "Error: expected output filename after >\n");
                return -1;
            }
            
            char *copy = strdup(token);
            if (!copy) {
                perror("strdup");
                return -1;
            }
            cmd->output_file = copy;
            cmd->append = 0;
        }

        // OUTPUT REDIRECTION (append)
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, DELIM);

            if (token == NULL || is_operator(token)) {
                fprintf(stderr, "Error: expected output filename after >>\n");
                return -1;
            }
            
            char *copy = strdup(token);
            if (!copy) {
                perror("strdup");
                return -1;
            }
            cmd->output_file = copy;
            cmd->append = 1;
        }

        // BACKGROUND EXECUTION 
        else if (strcmp(token, "&") == 0)
        {
            //to reject standalone '&'
            if (arg_index == 0) {
                fprintf(stderr, "Error: '&' without command\n");
                return -1;
            }

            cmd->background = 1;
            break; //added, since '&' should be last token, ignore anything after
        }

        // NORMAL ARGUMENT 
            // Duplicate tokens so the command structure owns its memory.
            // This allows safe cleanup after execution.
        else
        {
            //to prevent writing past the args array
            if (arg_index >= MAX_ARGS - 1) { //since last slot is for NULL terminator, we check against MAX_ARGS - 1
                fprintf(stderr, "Error: too many arguments\n");
                return -1;
            }

            char *copy = strdup(token);
            if (!copy) {
                perror("strdup");
                return -1;
            } 
            cmd->args[arg_index++] = copy;
        } //this block is to handle normal command arguments, we strdup to ensure they persist after strtok modifies the input string

        token = strtok(NULL, DELIM);
    }

    // no command found; don't have anything to execute
    if (arg_index == 0)
        return -1;

    // first argument is command name
    cmd->command = cmd->args[0];

    // NULL terminate for execvp
    cmd->args[arg_index] = NULL;

    return 0;
}