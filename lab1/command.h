#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

#define MAX_ARGS 256

typedef struct {
    char *command;              // command name
    char *args[MAX_ARGS];       // argument list (null terminated)
    char *input_file;           // for '<' redirection
    char *output_file;          // for '>' or '>>' redirection
    bool append;                // true if '>>'
    bool background;            // true if '&'
} Command;

void init_command(Command *cmd);
void free_command(Command *cmd);

#endif
