// Chelcea Claudiu Marian

#ifndef __SUPPORT_H_
#define __SUPPORT_H_

// This function loads the image from the file.
void LOAD(const char*);

// This function selects a part of the area.
void SELECT(int, int, int, int);

// This function selects the whole area.
void SELECT_ALL(void);

// This function rotates the image by a certain angle.
void ROTATE(const int);

// This function crops the image.
void CROP(void);

// This function will turn the image to grayscale format.
void GRAYSCALE(void);

// This function will turn the image to sepia format.
void SEPIA(void);

// This function saves the current image to a file.
void SAVE(void);

// This function closes the program.
void EXIT(void);

// This function returns a value between 0 - 8 representing
// the position in the command list of the received input
// and returns -1 if it doesn't exist
int find_command_value(const char**, const char* );

// This functions checks if an valid command has been received
// and,if true, executes the corresponding function
void check_command(const int);

// Exit status
enum {
    SUCCESS=0,
    ERROR=1,
};

#endif

