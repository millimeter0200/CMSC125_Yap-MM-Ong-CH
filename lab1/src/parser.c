#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int parse_input(char *input, Command *cmd) {
    // TODO:
    // - tokenize input
    // - detect <, >, >>, &
    // - populate command struct fields

    // placeholder logic
    char *token = strtok(input, " \t\n");
    if (token == NULL) {
        return -1;
    }

    cmd->command = token;
    cmd->args[0] = token;
    cmd->args[1] = NULL;

    return 0;
}
