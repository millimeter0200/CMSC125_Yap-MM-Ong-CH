#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

#define MAX_ARGS 256

typedef struct {
    char *command;            // command name
    char *args[MAX_ARGS];     // argument list (NULL terminated)

    char *input_file;         // for <
    char *output_file;        // for > or >>
    bool append;              // true if >>
    bool background;          // true if &
} Command;

// initialize fields
void init_command(Command *cmd);

// free/reset if needed
void free_command(Command *cmd);

#endif
