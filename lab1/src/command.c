#include <stdlib.h>
#include <string.h>
#include "command.h"

// This file contains functions related to the Command structure, such as initialization and cleanup.
//implementation here operate on the Command structure yhat keeps responsibilities cleand and separated from the parsing logic in parser.c
void init_command(Command *cmd)
{
    cmd->command = NULL;

     for (int i = 0; i < MAX_ARGS; i++)
        cmd->args[i] = NULL;

    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append = false;
    cmd->background = false;
}

void free_command(Command *cmd)
{
    for(int i=0; cmd->args[i] != NULL; i++) {
        free(cmd->args[i]);
    }

    if (cmd->input_file)
        free(cmd->input_file);

    if (cmd->output_file)
        free(cmd->output_file);
}

//implement free_command properly; implement this function to free the memory allocated for the command structure
//if we switched to strdup() then free_command becomes meaningful, otherwise we are just freeing pointers to the original input string which is not what we want