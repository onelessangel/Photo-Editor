#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Support.h"

#define MAX_COMMAND_SIZE 10
#define DEFINED_COMMANDS 9

int main(void) {
    

    char *input = (char*) malloc(MAX_COMMAND_SIZE*sizeof(char));
    if(input==NULL)
        return MALLOC_FAIL;
    
    scanf("%s",input);
    const char *commands[DEFINED_COMMANDS] = {"LOAD","SELECT","SELECT ALL","ROTATE","CROP","GRAYSCALE","SEPIA","SAVE","EXIT"};

    int command_value=-1;
    for(int i=0;i<DEFINED_COMMANDS;i++) if(strcmp(commands[i],input)==0) {command_value=i;break;}
    if(command_value==-1) printf("No command found!");
    else {
        //text
    
        ROTATE(45);   
    }

    free(input);

    return SUCCESS;
}