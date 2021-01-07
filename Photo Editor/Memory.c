// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exit status
enum { MALLOC_FAIL = 2, REALLOC_FAIL = 3 };

// Commands sizes
enum { MAX_COMMAND_SIZE = 100, DEFINED_COMMANDS = 9 };

// This function allocates the space necessary for a command.
char *user_input(void) {
	char *input = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));

	if (input == NULL)
		return (char *)MALLOC_FAIL;

	return input;
}

// This function returns a value between 0 - 8 representing
// the position in the command list of the received command
// and returns -1 if it doesn't exist
int find_command_value(const char *commands[], char *input) {
    
	// Receive command
	int command_value = -1;
	char *first_command = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
	if (first_command == NULL)
		return MALLOC_FAIL;
	char *second_command = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
	if (second_command == NULL)
		return MALLOC_FAIL;
	sscanf(input, "%s %s", first_command, second_command);

	// Check if the command is in the list
	for (int i = 0; i < DEFINED_COMMANDS; i++)
		if (strcmp(commands[i], first_command) == 0) {
			command_value = i;
			break;
		}
	if (command_value == 1 && (strcmp(second_command, "ALL") == 0))
		command_value = 2;

	return command_value;
}

// This functions allocates the memory for the image pixels
// and saves the pixels in a matrix shape, reading from an ASCII file
unsigned char **read_pixels(
		const int my_image_width, const int my_image_height, FILE *file) {
	// Allocate memory
	unsigned char **pixel_matrix =
			(unsigned char **)malloc(my_image_width * sizeof(unsigned char *));
	for (int i = 0; i < my_image_height; i++)
		pixel_matrix[i] =
				(unsigned char *)malloc(my_image_width * sizeof(unsigned char));

	// Scan values from ASCII file
	for (int i = 0; i < my_image_height; i++)
		for (int j = 0; j < my_image_width; j++)
			fscanf(file, "%hhu", &pixel_matrix[i][j]);

	return pixel_matrix;
}

// This functions creates a copy of the current selection
unsigned char **copy_pixels_selection(const int x1, const int y1, const int x2,
const int y2, unsigned char ***image) {
	// find the width and the height of the image
	int my_image_width = y2 - y1;
	int my_image_height = x2 - x1;

	// Memory allocation
	unsigned char **pixel_matrix = (unsigned char **)malloc(
			(my_image_width) * sizeof(unsigned char *));
	for (int i = 0; i < my_image_height; i++)
		pixel_matrix[i] = (unsigned char *)malloc(
				(my_image_height) * sizeof(unsigned char));

	// Copy values
	for (int i = 0; i < my_image_height; i++)
		for (int j = 0; j < my_image_width; j++)
			pixel_matrix[i][j] = (*image)[x1 + i][y1 + j];

	return pixel_matrix;
}

// This functions frees the memory from the currently loaded image.
void free_pixels(const int my_image_height, unsigned char ***pixel_matrix) {

	// Free every line
	for (int i = 0; i < my_image_height; i++)
		free((*pixel_matrix)[i]);

	// Free the main pointer
	free(*pixel_matrix);
}
