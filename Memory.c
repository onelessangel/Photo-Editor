// Chelcea Claudiu Marian

#include <stdlib.h>
#define MAX_COMMAND_SIZE 10
#define particular_case "SELECT"

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
