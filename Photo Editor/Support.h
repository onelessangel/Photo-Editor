// Chelcea Claudiu Marian

#ifndef __SUPPORT_H_
#define __SUPPORT_H_
#include <stdio.h>

// This function loads the image from the file
// and keeps the width and the height.
unsigned char** LOAD(const char*,int*,int*,int*,int*,int*,int*);

// This function selects a part of the area.
void SELECT(int*, int*, int*, int*, int*, int*);

// This function selects the whole area.
void SELECT_ALL(int*, int*, int*, int*, int*, int*);

// This function rotates the image or a selection of pixels from the image by a certain angle.
void ROTATE(const int,unsigned char***, int*, int*, int*, int*, const int, int, int);

// This function crops the image.
void CROP(void);

// This function will turn the image to grayscale format.
void GRAYSCALE(void);

// This function will turn the image to sepia format.
void SEPIA(void);

// This function saves the current image to a file.
void SAVE(void);

// This function closes the program and frees the memory.
void EXIT(char**);

// This functions checks if an valid command has been received
// and, if true, executes the corresponding function.
void check_command(const int, int*, int*,int*,int*, int*,int*,int*,unsigned char***,char**);

// This functions allocates the memory for the image pixels
// and copies the pixels from the file in a matrix shape.
unsigned char** read_pixels(const int, const int, FILE*);

// This functions frees the memory from the currently loaded image.
void free_pixels(const int, unsigned char***);

// This functions creates a copy of the current selection.
unsigned char** copy_pixels_selection(const int ,const int, const int ,const int, unsigned char***);

// Exit status
enum {
    SUCCESS=0,
    ERROR=1,
};


#endif
