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
void GREYSCALE(void);

// This function will turn the image to sepia format.
void SEPIA(void);

// This function saves the current image to a file.
void SAVE(void);

// This function closes the program.
void EXIT(void);

enum {
    SUCCESS=0,
    ERROR=1,
    MALLOC_FAIL=2
};

#endif