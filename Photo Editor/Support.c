// Chelcea Claudiu Marian

#include <stdio.h>
#include <string.h>
#define DEFINED_COMMANDS 9

// This function loads the image from the file.
void LOAD(const char *file_name){
    printf("LOADED %s\n",file_name);
}

// This function selects a part of the area.
void SELECT(int x1, int y1, int x2, int y2){
    printf("SELECTED %d %d %d %d\n",x1,y1,x2,y2);
}

// This function selects the whole area.
void SELECT_ALL(void){
    printf("SELECT ALL\n");
}

// This function rotates the image by a certain angle.
void ROTATE(const int angle) {
    printf("ROTATE by %d\n",angle);
}

// This function crops the image.
void CROP(void) {
    printf("CROP\n");
}

// This function will turn the image to grayscale format.
void GRAYSCALE(void){
    printf("GRAYSCALE\n");
}

// This function will turn the image to sepia format.
void SEPIA(void){
    printf("SEPIA\n");
}

// This function saves the current image to a file.
void SAVE(void){
    printf("SAVE\n");
}

// This function closes the program.
void EXIT(void){
    printf("EXIT\n");
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
    if(strcmp("ALL",input)==0) 
        command_value=2;
    return command_value;
}
  
// This functions checks if an valid command has been received
// and,if true, executes the corresponding function
void check_command(int command_value)
{
    int coord_x1, coord_y1, coord_x2, coord_y2;

    switch(command_value) {
        
        // LOAD
        case 0:
            LOAD("text");
                break;

        // SELECT
        case 1:
                if((scanf("%d %d %d %d",&coord_x1,&coord_y1,&coord_x2,&coord_y2)) == 4 ) {
                    SELECT(coord_x1,coord_y1,coord_x2,coord_y2);
                    break;     
                } else {
                    SELECT_ALL();
                    break;            
                } 
        // SELECT ALL
        case 2:
                break;

        // ROTATE    
        case 3:
                ROTATE(45);
                break;

        // CROP   
        case 4:
                CROP();
                break;
            
        // GREYSCALE    
        case 5:
                GRAYSCALE();
                break;

        // SEPIA    
        case 6:
                SEPIA();
                break;
        // SAVE    
        case 7:
                SAVE();
                break;

        // EXIT 
        case 8:
                EXIT();
                break;

        // INVALID COMMAND
        default:
            printf("Invalid command\n");
        
    }

} 
