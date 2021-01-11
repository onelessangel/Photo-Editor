// Chelcea Claudiu Marian

#ifndef __SUPPORT_H_
#define __SUPPORT_H_

// This function loads the image from the file
// and keeps the width and the height.
unsigned char **LOAD(
	const char *file_name, int *width, int *height, int *x1, int *y1, int *x2,
	int *y2, int *color_image, int *my_image_max, char *type);

// This function selects a part of the area.
void SELECT(
	int *x1, int *y1, int *x2, int *y2, int width, int height, int *correct,
	int color_image);

// This function selects the whole area.
void SELECT_ALL(
	int *width, int *height, int *x1, int *y1, int *x2, int *y2,
	int has_been_cropped, int *px1, int *py1);

// This functions swaps the values of two variables
void swap(int *var1, int *var2);

// This function rotates the image or a selection of pixels from the image by a
// certain angle.
void ROTATE(
	int angle, unsigned char ***image, int *x1, int *y1, int *x2, int *y2,
	const int whole_map_selected, int *width, int *height,
	const int color_image, int *px1, int *py1, int *px2, int *py2);

// This function crops the image.
void CROP(
	int *x1, int *y1, int *x2, int *y2, int *width, int *height,
	const int color_image, int *cropped, int *has_been_cropped);

// This function will turn the image to grayscale format.
void GRAYSCALE(int *x1, int *y1, int *x2, int *y2, unsigned char ***image);

// This functions returns the lowest value from the comparison of two values
int minimum_value(int first_value, int second_value);

// This function will turn the image to sepia format.
void SEPIA(
	int *x1, int *y1, int *x2, int *y2, unsigned char ***image,
	const int my_image_max);

// This function saves the current image to a file in the specified format.
void SAVE(
	const char *file_name, unsigned char **image, int width, const int height,
	const int binary, const char type, int my_image_max, int x1, int y1, int x2,
	int y2);

// This function closes the program and frees the memory.
void EXIT(unsigned char ***image, const int height);

// This functions checks if an valid command has been received
// and, if true, executes the corresponding function.
void check_command(
	int command_value, int *width, int *height, int *image_status, int *x1,
	int *y1, int *x2, int *y2, unsigned char ***image, char **input,
	int *color_image, char *type, int *my_image_max, int *whole_map_selected,
	int *correct, int *cropped, int *has_been_cropped, int *px1, int *py1,
	int *px2, int *py2);

// Exit status
enum { SUCCESS = 0, ERROR = 1 };

#endif
