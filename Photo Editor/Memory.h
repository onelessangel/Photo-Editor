// Chelcea Claudiu Marian

#ifndef __MEMORY_H_
#define __MEMORY_H_
#include <stdio.h>

// This function allocates the space necessary for the commands.
char* user_input(void);

// This function returns a value between 0 - 7 representing
// the position in the command list of the received input
// and returns -1 if it doesn't exist
int find_command_value(const char**, const char*);

#endif
