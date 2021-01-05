// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Memory.h"

// This function loads the image from the file
// and keeps the width and the height.
unsigned char** LOAD(const char *file_name, int *width, int *height, 
int* x1, int* y1, int* x2,int* y2,int* color_image, int* my_image_max,
int* no_image_loaded, char* type) {
    
    FILE *file = fopen(file_name,"rt");
    if(file==NULL) {
        printf("Failed to load %s\n",file_name);
        return (unsigned char**) ERR;
    }

    char first_character,second_character;
    fscanf(file,"%c",&first_character);
    fscanf(file,"%c",&second_character);
    image_t my_image;

    // Check for text files
    if(second_character=='2') {

        // GRAYSCALE - ASCII
        int val1,val2,val3;
        fscanf(file,"%d %d %d",&val1,&val2,&val3);
      
        my_image.width=val1;
        my_image.height=val2;
        *my_image_max=val3;

        // Copy image
        unsigned char** pixels = NULL;
        pixels = read_pixels(my_image.width,my_image.height,file); 
        if(pixels != NULL) {
            printf("Loaded %s\n",file_name);
            *no_image_loaded = 0;}

        // Set new values for coordinates, dimensions and color
        *width = my_image.width;
        *height = my_image.height;
        *x1=0;
        *y1=0;
        *x2=my_image.height;
        *y2=my_image.width;
        *color_image=0;
        *type='2';

        // Close file
        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        return pixels;
    }

    else if(second_character=='3') {

        // RGB - ASCII
        int val1,val2,val3;
        fscanf(file,"%d %d %d",&val1,&val2,&val3);
      
        my_image.width=val1;
        my_image.height=val2;
        *my_image_max=val3;

        // Copy image
        unsigned char** pixels = NULL;
        pixels = read_pixels(my_image.width*3,my_image.height,file); 
        if(pixels != NULL) {
            printf("Loaded %s\n",file_name);
            *no_image_loaded=0;
        }

        // Set new values for coordinates, dimensions and color
        *width = (my_image.width*3);
        *height = my_image.height;
        *x1=0;
        *y1=0;
        *x2=my_image.height;
        *y2=(my_image.width*3);
        *color_image=1;
        *type='3';
        // Close file
        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        return pixels;

    }

    // Check for binary files
    else {
        
        // Put the read characters back into the file
        ungetc(first_character,file);
        ungetc(second_character,file);

        // Close the file opened as text
        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        // Open the same file, but as binary
        FILE *file_bin = fopen(file_name,"rb");
    
        // Get the type of file and the image restrictions
        char file_type2[2];
        int my_width,my_height;  
        fscanf(file_bin,"%s",file_type2);
        fscanf(file_bin,"%d",&my_width);
        fscanf(file_bin,"%d",&my_height);
        fscanf(file_bin,"%d",my_image_max);

        // Decide which file type it is
        if(strcmp("P5",file_type2)==0) 
            second_character='G';
        else second_character = 'R';
        
        // Remove the newline
        getc(file_bin);

        // Binary GRAYSCALE
        if(second_character=='G') {
        
            // Read the image
            unsigned char** pixels = NULL;
            pixels = read_pixels_binary(my_width,my_height,file_bin); 
            if(pixels != NULL) {
                printf("Loaded %s\n",file_name);
                *no_image_loaded=0;
            }

            // Modify the dimensions
            *width = my_width;
            *height = my_height;
            *x1=0;
            *y1=0;
            *x2=my_height;
            *y2=my_width;
            *color_image=0;
            *type='5';
            // Close the file
            if(fclose(file_bin) == EOF)
                return (unsigned char**) FILE_CLOSE_ERROR;
            
            return pixels;
        }
        
        // Binary RGB
        else if(second_character=='R') {
            
            // Read the image
            unsigned char** pixels = NULL;
            pixels = read_pixels_binary(my_width*3,my_height,file_bin); 
            if(pixels != NULL) {
                printf("Loaded %s\n",file_name);
                *no_image_loaded=0;
            }
            
            // Modify the dimensions
            *width = my_width*3;
            *height = my_height;
            *x1=0;
            *y1=0;
            *x2=my_height;
            *y2=my_width*3;
            *color_image=1;
            *type='6';

            // Close the file
            if(fclose(file_bin) == EOF)
                return (unsigned char**) FILE_CLOSE_ERROR;

            return pixels;
        }
    }

    return (unsigned char**) SUCC;

}

// This function selects a part of the area.
void SELECT(int* x1, int* y1, int* x2, int* y2, int *width, int *height){

        // Chech if the coordinates are valid
        if(*x1<0 || *x2 < 0 || *y1 < 0 || *y2 < 0) 
            printf("Invalid coordinates\n");
        else if(*x1> *height || *x2 > *height)
            printf("Invalid coordinates\n");
        else if(*y1> *width || *y2 > *width)
            printf("Invalid coordinates\n");
        else
            printf("Selected %d %d %d %d\n",*x1,*y1,*x2,*y2);

        // Keep the width and height coordinates in ascending order
        int aux;
        if(*x1>*x2) {
            aux = *x1;
            *x1 = *x2;
            *x2 = aux;
        }
        if(*y1>*y2) {
            aux = *y2;
            *y1 = *y2;
            *y2 = aux;
        }
    
}

// This function selects the whole area.
void SELECT_ALL(int *width, int *height, int *x1, int *y1, int *x2, int *y2){

        *x1=0;
        *y1=0;
        *x2=*height;
        *y2=*width;

    printf("Selected ALL\n");
}

// This function rotates the image or a selection of pixels from the image by a certain angle.
void ROTATE(int angle, unsigned char*** image, int *x1, int *y1, int *x2, int *y2, const int whole_map_selected, int *width, int *height) {
    
    // Case one: only a part of the image is selected (a square submatrix)
    if(!whole_map_selected) {

        // Create copy of the current selection
        unsigned char** pixels = copy_pixels_selection(*x1,*y1,*x2,*y2,image); 
        if( pixels == NULL) 
            return;

        // Rotate to 90/-270 degrees
        if(angle == 90 || angle == -270) {
            for(int i=0;i<(*x2-*x1);i++) 
                for(int j=0;j<(*y2-*y1);j++) 
                    (*image)[*x1+i][*y1+j]=pixels[*x2-1-j][*y1+i];
        }

        // Rotate to 180/-180 degrees
        else if(angle == 180 || angle == -180) {
            for(int i=0;i<(*x2-*x1);i++) 
                for(int j=0;j<(*y2-*y1);j++) 
                    (*image)[*x1+i][*y1+j]=pixels[*x2-1-i][*y2-1-j];
        } 

        // Rotate to 270/-90 degrees
        else if(angle == 270 || angle == -90) {
            for(int i=0;i<(*x2-*x1);i++) 
                for(int j=0;j<(*y2-*y1);j++) 
                    (*image)[*x2-1-j][*y1+i]=pixels[*x1+i][*y1+j];
        }  
        
        // Free the matrix copy
        free_pixels((*x2-*x1),&pixels);
    }

    // Case two: the whole map is selected (it might not be a sqaure matrix)
    else if(whole_map_selected) {

        // Rotate to 90/-270 degrees
        if(angle == 90 || angle == -270) {
            
            // Get the minimum square matrix necessary
            int max_size = *height;
            if (max_size < *width) max_size = *width;

            // Memory allocation for rotation
            unsigned char** pixel_matrix = (unsigned char**) calloc(max_size, sizeof(unsigned char*));
            for(int i=0;i<max_size;i++) 
                pixel_matrix[i] = (unsigned char*) calloc(max_size, sizeof(unsigned char));

            // Copy values in the clone matrix
            int p=0;
            for(int i=0;i<*width;i++) {
                for(int j=0;j<*height;j++) {
                    pixel_matrix[i][j]=(*image)[*height -1 - j][p];
                    if(j==(*height-1)) p++;
                }
            
            }

            // Save and change coordinates accordingly
            *image=pixel_matrix;
            int aux = *width;
            *width=*height;
            *height=aux;
            *x2=*height;
            *y2=*width;

        }

        // Rotate to 180/-180 degrees
        else if(angle == 180 || angle == -180) {

            // Get the minimum square matrix necessary
            int max_size = *height;
            if (max_size < *width) max_size = *width;

            // Memory allocation for rotation
            unsigned char** pixel_matrix = (unsigned char**) malloc(max_size * sizeof(unsigned char*));
            for(int i=0;i<max_size;i++) 
                pixel_matrix[i] = (unsigned char*) malloc(max_size * sizeof(unsigned char));
            
            // Copy values in the matrix copy
            for(int i=0;i<*height;i++) {
                for(int j=0;j<*width;j++) {
                    pixel_matrix[i][j]=(*image)[i][j];
                }
            }
      
            // Put the correct values in the original matrix
            for(int i=0;i<*height;i++) {
                for(int j=0;j<*width;j++) {
                    (*image)[i][j]=pixel_matrix[*height-1-i][*width-1-j];
                }
            }

            // Free the matrix copy
            free_pixels(max_size,&pixel_matrix);
        } 

        // Rotate to 270/-90 degrees
        else if(angle == 270 || angle == -90) {
         
            // Get the minimum square matrix necessary
            int max_size = *height;
            if (max_size < *width) max_size = *width;

            // Memory allocation for rotation
            unsigned char** pixel_matrix = (unsigned char**) calloc(max_size, sizeof(unsigned char*));
            for(int i=0;i<max_size;i++) 
                pixel_matrix[i] = (unsigned char*) calloc(max_size, sizeof(unsigned char));

            // Copy values in the matrix copy
            for(int i=0;i<*width;i++) {
                for(int j=0;j<*height;j++) {
                    pixel_matrix[i][j]=(*image)[j][*width-1-i];
                }
            
            }

            // Put the correct values in the original matrix
            *image=pixel_matrix;
            int aux = *width;
            *width=*height;
            *height=aux;
            *x2=*height;
            *y2=*width;

        }
    }

    printf("Rotated %d\n",angle);
}

// This function crops the image.
void CROP(int *x1, int *y1, int *x2,int *y2,int *width,int* height) {

    *height=*x2-*x1;
    *width=*y2-*y1;
    printf("Image cropped\n");
}

// This function will turn the image to grayscale format.
void GRAYSCALE(int *x1,int *y1,int *x2,int *y2,unsigned char*** image) {
    double RGB_2_GRAYSCALE=0.00;
    int RGB_int;
    for(int i=*x1;i<*x2;i++)
        for(int j=*y1;j<*y2;j=j+3) {

            // Formula for RGB
            RGB_2_GRAYSCALE=((*image)[i][j]+(*image)[i][j+1]+(*image)[i][j+2])/3.0;
            RGB_int = RGB_2_GRAYSCALE;
            (*image)[i][j]=(*image)[i][j+1]=(*image)[i][j+2]=RGB_int;
        }

    printf("Grayscale filter applied\n");
}

// This functions returns the lowest value from the comparison of two values
int minimum_value(int first_value, int second_value) {
    if(first_value  > second_value) return second_value;
    return first_value;
}

// This function will turn the image to sepia format.
void SEPIA(int *x1,int *y1,int *x2,int *y2,unsigned char*** image, const int my_image_max){
    double R,G,B;
    int R_int, G_int,B_int;
    for(int i=*x1;i<*x2;i++)
        for(int j=*y1;j<*y2;j=j+3) {
            
            // Formula for SEPIA red color.
            R=0.393*(*image)[i][j] + 0.769*(*image)[i][j+1] + 0.189* (*image)[i][j+2];
            R_int = R;
            if(R_int>my_image_max) R_int = minimum_value(R_int,my_image_max);

            // Formula for SEPIA green color.
            G=0.349*(*image)[i][j] + 0.686*(*image)[i][j+1] + 0.168* (*image)[i][j+2];
            G_int = G;
            if(G_int>my_image_max) G_int = minimum_value(G_int,my_image_max);

            // Formula for SEPIA blue color.
            B=0.272*(*image)[i][j] + 0.534*(*image)[i][j+1] + 0.131* (*image)[i][j+2];
            B_int = B;
            if(B_int>my_image_max) B_int = minimum_value(B_int,my_image_max);

            // Apply the new colors
            (*image)[i][j]=R_int;
            (*image)[i][j+1]=G_int;
            (*image)[i][j+2]=B_int;
        }
    printf("Sepia filter applied\n");
}

// This function saves the current image to a file in the specified format.
void SAVE(const char *file_name,unsigned char **image,int width, const int height, const int binary,const char type, int my_image_max) {

    FILE *new_file;
    
    // Open in binary mode
    if(binary == 1) {
        new_file=fopen(file_name,"wb");
        if(new_file == NULL)
            return;

        if(type=='5') {
            char Px[2]="P5";
            fwrite(Px,sizeof(char),2,new_file);
            fwrite(&width,sizeof(int),1,new_file);
            fwrite(&height,sizeof(int),1,new_file);
            fwrite(&my_image_max,sizeof(int),1,new_file);
            for(int i=0;i<height;i++)
                for(int j=0;j<width;j++)
                    fwrite(&image[i][j],sizeof(unsigned char),1,new_file);

          if(fclose(new_file)== EOF) {
              printf("Nu s-a inchis");
                return;
            }
        }
        else if(type=='6') {
            width=width/3;
            char Px[2]="P6";
            fwrite(Px,sizeof(char),2,new_file);
            fwrite(&width,sizeof(int),1,new_file);
            fwrite(&height,sizeof(int),1,new_file);
            fwrite(&my_image_max,sizeof(int),1,new_file);
            for(int i=0;i<height;i++)
                for(int j=0;j<width;j++)
                    fwrite(&image[i][j],sizeof(unsigned char),1,new_file);

          if(fclose(new_file)== EOF) {printf("Nu s-a inchis");
                return;
            }

        } 
    }
    // Open in ascii mode
    else if(binary == 0) {
        new_file=fopen(file_name,"wt");
        if(new_file == NULL)
            return;

        if(type=='2') {
            char Px[2]="P2";
            fprintf(new_file,"%s\n",Px);
            fprintf(new_file,"%d %d\n%d\n",width,height,my_image_max);
     
            for(int i=0;i<height;i++) {
                for(int j=0;j<width;j++)  fprintf(new_file,"%hhu ",image[i][j]);
                    fprintf(new_file,"\n");
                }
            
              if(fclose(new_file)== EOF) {printf("Nu s-a inchis");
                return;
            }
            
    }
        else if(type=='3') {
            char Px[2]="P3";
            width=width/3;
            fprintf(new_file,"%s\n",Px);
            fprintf(new_file,"%d %d\n%d\n",width,height,my_image_max);
     
            for(int i=0;i<height;i++) {
                for(int j=0;j<width;j++)  fprintf(new_file,"%hhu ",image[i][j]);
                    
                }

            if(fclose(new_file)== EOF) {printf("Nu s-a inchis");
                return;
            }

        }
    }

    printf("Saved %s\n",file_name);
}

// This function closes the program and frees the memory.
void EXIT(char ** input,unsigned char*** image,const int height){
    free(*input);
    free_pixels(height,image);
    exit(EXIT_SUCCESS);
}
  
// This functions checks if an valid command has been received
// and,if true, executes the corresponding function
void check_command(int command_value, int *width,  int *height, int *image_status,
int *x1, int *y1, int *x2, int *y2, unsigned char ***image, char** input,int* color_image,
char* type, int* my_image_max,int* no_image_loaded)
{
    // Check for wrong command
    if(command_value ==  -1) {
        char* error_input = (char*) malloc(100*sizeof(char));
        fgets(error_input,100,stdin);
        error_input[strlen(error_input)-1]='\0';
        printf("Invalid command\n");
        free(error_input);
        return;
    }
    
    // Declare variables
    char *file_name= (char*) malloc(NAME_LENGTH_MAX*sizeof(char));
    int replace1=0,replace2=0,replace3=0,replace4=0, angle=0;
    int whole_map_selected=0;
    char* input_save = (char*) malloc(100*sizeof(char));
    char* word, binary=0;
    char* new_file = (char*) malloc(100*sizeof(int));
    
    // If the command_value returned a number between 0-8
    // then we can call the corresponding function
    switch(command_value) {
        
        // FUNCTION: LOAD
        case 0:
            // Get file name
            scanf("%s",file_name);
            
            // Load the image in a dynamic matrix
            *image = LOAD(file_name,width,height,x1,y1,x2,y2,color_image,my_image_max,no_image_loaded,type);

            // Check image status
            if(*image != NULL)
                *image_status=UPP;

            break;

        // FUNCTION: SELECT
        case 1:
                // Get the coordinates given by select
                if((scanf("%d %d %d %d",&replace1,&replace2,&replace3,&replace4)) == 4 ) {
                    if(*image_status == UPP)
                    {
                        *x1=replace1;
                        *y1=replace2;
                        *x2=replace3;
                        *y2=replace4;
                        SELECT(x1,y1,x2,y2,width,height);
                    }
                    else  {
                        printf("No image loaded\n");
                        *no_image_loaded=1;
                    }
                    
                }
                else {
                    printf("Invalid set of coordinates\n");
                    *no_image_loaded=1;
                }

                break;     
                
        // FUNCTION: SELECT ALL
        case 2:   
            if(*image_status == UPP)
                SELECT_ALL(width,height,x1,y1,x2,y2);
            else {
                    printf("Invalid set of coordinates\n");
                    *no_image_loaded=1;
                }
            break;

        // FUNCTION: ROTATE    
        case 3:
               if(scanf("%d",&angle)) {
                   // If the image is loaded execute this. Else display "No image loaded"
                    if(*image_status == UPP) {
                        
                        //  Check for valid angle
                        if(angle != 90 && angle !=-90 && angle != 180 && angle !=-180 && angle !=270 && angle !=-270)
                            {printf("Unsupported rotation angle\n"); *no_image_loaded=1;}
                        
                        // Check if the coordinates form a square image
                        else if( ( (*x2-*x1) != (*y2-*y1)) && (*x1!=0 || *y1 !=0 || *x2!=*height || *y2 !=*width))
                            {printf("The selection must be square\n");*no_image_loaded=1;}
                        else {
                            //  Check if the coordinates form the whole image
                            if(*x1==0 && *y1==0 && *x2== *height && *y2 == *width)
                                whole_map_selected = 1;
                            ROTATE(angle, image,x1,y1,x2,y2,whole_map_selected,width,height);
                        }
                        
                    } else  {
                        printf("No image loaded\n");
                        *no_image_loaded=1;
                        }
                }
                break;

        // FUNCTION: CROP   
        case 4:
                if(*image_status == UPP)
                    CROP(x1,y1,x2,y2,width,height);
                else  {
                    printf("No image cropped\n");
                    *no_image_loaded=1;
                }

                break;
            
        // FUNCTION: GREYSCALE    
        case 5:
           if(*image_status == UPP) {
                // Apply GRAYSCALE filter only if the image is a color one
                if(*color_image == 1)
                    GRAYSCALE(x1,y1,x2,y2,image);
                else 
                    printf("Grayscale filter not available\n");      
           }     
            else  {
                printf("No image loaded\n");
                *no_image_loaded=1;
            }
                break;

        // FUNCTION: SEPIA    
        case 6:
            if(*image_status == UPP) {
                // Apply SEPIA filter only if the image is a color one
                if(*color_image == 1)
                    SEPIA(x1,y1,x2,y2,image,*my_image_max);
                else 
                    printf("Sepia filter not available\n");        
           }     
            else  {
                printf("No image loaded\n");
                *no_image_loaded=1;
            }
                break;
            
        // FUNCTION: SAVE    
        case 7:
            getc(stdin);
            fgets(input_save,100,stdin);
            word = strtok(input_save," ");
            strcpy(new_file,word);
            word = strtok(NULL," ");
            if ( word == NULL )
                binary=1;
            else binary=0;

            if(*image_status == UPP) {
                SAVE(new_file,*image,*width,*height,binary,*type,*my_image_max);
                printf("Am trimis %s %d %d %d %c %d",new_file,*width,*height,binary,*type,*my_image_max);
            }
            else  {
                printf("No image loaded\n");
                *no_image_loaded=1;
            }
            break;

        // FUNCTION: EXIT 
        case 8:
                EXIT(input,image,*height);
                break;

        // NO FUNCTION: "INVALID COMMAND"
        default:
            if(*no_image_loaded==1)
                printf("Invalid command\n");
            break;
        
    }

} 
