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
    char a=0,b=0,c=0,d=0;
    char wrong_input[100];

    if(command_value==1)  {
        scanf("%c%c%c%c",&a,&b,&c,&d);
        if(a!=' ' || b!='A' || c!='L' || d != 'L') {
            ungetc(d,stdin);
            ungetc(c,stdin);
            ungetc(b,stdin);
            ungetc(a,stdin);
        
        } else {
            ungetc(d,stdin);
            ungetc(c,stdin);
            ungetc(b,stdin);
            ungetc(a,stdin);
            scanf("%s",wrong_input);
            if(strlen(wrong_input) == 3)
                command_value=2;
            else command_value=-1;
        }
    }
        

    return command_value;
}
