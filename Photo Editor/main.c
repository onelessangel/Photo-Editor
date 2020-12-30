// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Memory.h"
#include "Support.h"
#define DEFINED_COMMANDS 9

// Image state
enum {
    DOWN=0,
    UP=1,
    NULL_LIST=2
};

int main(void) {
    
    // Set commands
    int width = 0, height = 0, image_status=DOWN;
    int x1=0,y1=0,x2=0,y2=0;
    const char *commands[DEFINED_COMMANDS] = {"LOAD","SELECT","SELECT ALL","ROTATE","CROP","GRAYSCALE","SEPIA","SAVE","EXIT"};
    if(commands == NULL)
        return NULL_LIST;

    // Alocate space for command name
    char *input = user_input();
    
// SSS
// SDSD FDSFSDF
// SELECT ALL
// SELECT 23 4 32 35
// select x d gfd s
// SELECT X 53 G 2

    // Receive commands and execute them
    while(UP) {
        scanf("%s",input);

        // Check what command is given and if it exists.
       
        int command_value = find_command_value(commands, input);

        // If it exists, execute it.
        check_command(command_value, &width, &height, &image_status,&x1,&y1,&x2,&y2);
    }

    free(input);

    return SUCCESS;
}
