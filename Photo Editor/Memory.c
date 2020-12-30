// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND_SIZE 10
#define DEFINED_COMMANDS 9

// Exit status
enum {
    MALLOC_FAIL=2,
    REALLOC_FAIL=3
};

// This function allocates the space necessary for a command.
char* user_input(void) {
    char *input = (char*) malloc(MAX_COMMAND_SIZE * sizeof(char));

    if(input==NULL)
        return (char* ) MALLOC_FAIL;
    
    return input;
}

// This function returns a value between 0 - 8 representing
// the position in the command list of the received command
// and returns -1 if it doesn't exist
int find_command_value(const char *commands[], char* input)
{
    int command_value=-1;
    for(int i=0;i<DEFINED_COMMANDS;i++) 
        if(strcmp(commands[i],input)==0) {
            command_value=i;
            break;
        }

    if(strcmp("ALL",input)==0 || command_value == -1) 
        command_value=2;

    return command_value;
}
