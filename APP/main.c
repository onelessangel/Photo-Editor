// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Support.h"
#include "Memory.h"
#define DEFINED_COMMANDS 9

int main(void) {
    
    // Set commands
    const char *commands[DEFINED_COMMANDS] = {"LOAD","SELECT","SELECT ALL","ROTATE","CROP","GRAYSCALE","SEPIA","SAVE","EXIT"};

    // Alocate space for command name
    char *input = user_input();
    
    // Receive commands and execute them
    while(1) {
        scanf("%s",input);

        // Check what command is given and if it exists.
        int command_value = find_command_value(commands, input);

        // If it exists, execute it.
        check_command(command_value);
    }

    free(input);

    return SUCCESS;
}
