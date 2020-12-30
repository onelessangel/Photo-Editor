// Chelcea Claudiu Marian

#ifndef __SUPPORT_H_
#define __SUPPORT_H_

// This function loads the image from the file.
// and keeps the width and the height
void LOAD(const char*,int*,int*);

// This function selects a part of the area.
void SELECT(int*, int*, int*, int*, int*, int*);

// This function selects the whole area.
void SELECT_ALL(int*, int*);

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

// This functions checks if an valid command has been received
// and,if true, executes the corresponding function
void check_command(const int, int*, int*,int*,int*, int*,int*,int*);

// This functions allocates the memory for the image pixels
// and copies the pixels from the file in a matrix shape
unsigned char** read_pixels(const int, const int, FILE*);

// This functions frees the memory from the currently loaded image.
void free_pixels(const int, unsigned char***);

// Exit status
enum {
    SUCCESS=0,
    ERROR=1,
};


#endif
