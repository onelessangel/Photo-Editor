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
    
    // Set IMAGE
    unsigned char **image = NULL;
    int width = 0, height = 0, image_status=DOWN;
    int x1=0,y1=0,x2=0,y2=0, my_image_max=0;
    int color_image=0, no_image_loaded = 1;
    char type = '0';

    // Set COMMAND
    const char *commands[DEFINED_COMMANDS] = {"LOAD","SELECT","SELECT ALL","ROTATE","CROP","GRAYSCALE","SEPIA","SAVE","EXIT"};
    if(commands == NULL)
        return NULL_LIST;
    char *input = user_input();

    // Receive commands and execute them
    while(UP) {
        scanf("%s",input);

        // Check what command is given and whether it exists or not.
        int command_value = find_command_value(commands, input);

        // If it exists, execute it.
        check_command(command_value, &width, &height, &image_status,&x1,&y1,&x2,&y2,&image,&input,&color_image,&type,&my_image_max,&no_image_loaded);
    }

    // Free memory
    free(commands);

    return SUCCESS;
}
