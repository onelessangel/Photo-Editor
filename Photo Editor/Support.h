// Chelcea Claudiu Marian

#ifndef __SUPPORT_H_
#define __SUPPORT_H_
#include <stdio.h>

// This function loads the image from the file
// and keeps the width and the height.
unsigned char** LOAD(const char*,int*,int*,int*,int*,int*,int*,int*,int*,char*);

// This function selects a part of the area.
void SELECT(int*, int*, int*, int*, int*, int*);

// This function selects the whole area.
void SELECT_ALL(int*, int*, int*, int*, int*, int*);

// This function rotates the image or a selection of pixels from the image by a certain angle.
void ROTATE(const int,unsigned char***, int*, int*, int*, int*, const int, int*, int*,const int);

// This function crops the image.
void CROP(int*,int*,int*,int*,int*,int*,const int);

// This function will turn the image to grayscale format.
void GRAYSCALE(int*,int*,int*,int*,unsigned char***,const int);

// This functions returns the lowest value from the comparison of two values
int minimum_value(int, int);

// This function will turn the image to sepia format.
void SEPIA(int*,int*,int*,int*,unsigned char***,int*,const int);

// This function saves the current image to a file in the specified format.
void SAVE(const char*,unsigned char**,int,const int,const int, const char*,int);

// This function closes the program and frees the memory.
void EXIT(unsigned char***,const int);

// This functions checks if an valid command has been received
// and, if true, executes the corresponding function.
void check_command(const int, int*, int*,int*,int*, int*,int*,int*,unsigned char***,char**,int*,char*,int*,int*);


// Exit status
enum {
    SUCCESS=0,
    ERROR=1,
};

#endif
