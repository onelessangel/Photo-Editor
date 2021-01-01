// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LENGTH_MAX 100
#define TRUE 1
#define FALSE 0
/*
    TO DO:
    *CHECK FOR MORE OUTPUT --- LOAD <file> <trash> -> error
    *CHECK FOR COMMENTS (only on the line before the matrix) -- use this: all values are less or equal to 255
    *CHECK FOR BINARY FILES
    *FREE MEMORY WHERE POSSIBLE
*/

// Image properties
typedef struct {
    int type;
    int width;
    int height;
    int max_value;
} image_t;

// File status
enum {
    FILE_OPEN_ERROR = 4,
    FILE_CLOSE_ERROR = 5,
    SUCCESS = 0,
    ERROR = -1,
};

// Image status
enum {
    DOWN=0,
    UP=1
};

// This functions allocates the memory for the image pixels
// and saves the pixels in a matrix shape
unsigned char** read_pixels(const int my_image_width,const int my_image_height, FILE* file) {

    unsigned char** pixel_matrix = (unsigned char**) malloc(my_image_width * sizeof(unsigned char*));

    for(int i=0;i<my_image_height;i++) pixel_matrix[i] = (unsigned char*) malloc(my_image_height * sizeof(unsigned char));

    for(int i=0;i<my_image_height;i++) 
        pixel_matrix[i] = malloc(my_image_width * sizeof(unsigned char));
    
    for(int i=0;i<my_image_height;i++) 
        for(int j=0;j<my_image_width;j++) 
            fscanf(file,"%hhu",&pixel_matrix[i][j]);

    return pixel_matrix; 
}

// This functions creates a copy of the current selection
unsigned char** copy_pixels_selection(const int x1, const int y1, const int x2, const int y2, unsigned char*** image) {

    // Memory allocation
    int my_image_width=y2-y1;
    int my_image_height=x2-x1;

    unsigned char** pixel_matrix = (unsigned char**) malloc((my_image_width)* sizeof(unsigned char*));
    for(int i=0;i<my_image_height;i++) 
        pixel_matrix[i] = (unsigned char*) malloc((my_image_height) * sizeof(unsigned char));
    
    // Copy values
    for(int i=0;i<my_image_height;i++) 
        for(int j=0;j<my_image_width;j++) 
            pixel_matrix[i][j]=(*image)[x1+i][y1+j];

    return pixel_matrix; 
}

// This functions frees the memory from the currently loaded image.
void free_pixels(const int my_image_height,unsigned char*** pixel_matrix)
{
    
    for(int i=0;i<my_image_height;i++) 
            free((*pixel_matrix)[i]);

    free(*pixel_matrix);
}

// This function loads the image from the file.
unsigned char** LOAD(const char *file_name, int *width, int *height, int* x1, int* y1, int* x2, int* y2) {
    
    FILE *file = fopen(file_name,"rt");
    if(file==NULL) {
        printf("Failed to load %s\n",file_name);
        return (unsigned char**) ERROR;
    }


    char b,c;
    fscanf(file,"%c",&b);
    fscanf(file,"%c",&c);
    image_t my_image;

    if(c=='2') {
        // DO STUFF WITH GRAYSCALE - ASCII
        
        fscanf(file,"%d %d %d",&my_image.width,&my_image.height,&my_image.max_value);
      
        unsigned char** pixels = read_pixels(my_image.width,my_image.height,file); 
        if(pixels != NULL)
            printf("Loaded %s\n",file_name);

        // COD SUPLIMENTAR
        *width = my_image.width;
        *height = my_image.height;
        *x1=0;
        *y1=0;
        *x2=my_image.height;
        *y2=my_image.width;
        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        return pixels;
    //free_pixels(my_image.height,&pixels);

    }

    else if(c=='3') {
        // DO STUFF WITH RGB ASCII
    
        fscanf(file,"%d %d %d",&my_image.width,&my_image.height,&my_image.max_value);
        unsigned char** pixels = read_pixels(my_image.width,my_image.height,file); 
        if(pixels != NULL)
            printf("Loaded %s\n",file_name);

        // COD SUPLIMENTAR
        *width = my_image.width;
        *height = my_image.height;
        *x1  = 0;
        *y1=0;
        *x2=my_image.height;
        *y2=my_image.width;

        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        return pixels;

        //free_pixels(my_image.height,&pixels);

     }

    else {
        ungetc(b,file);
        ungetc(c,file);

        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        FILE *file_bin = fopen(file_name,"rb");
        if(file_bin==NULL) 
            return (unsigned char**) FILE_OPEN_ERROR;
        

        for(int i=0;i<5;i++) 
            fread(&c,sizeof(char),1,file_bin);

        getc(file_bin);

        if(c=='3') {
            // DO STUFF WITH PGM - BINARY
            // READ SIZE
            // ALLOC SIZE
            // FREE SIZE
            
         //  if(pixels != NULL)
        //    printf("Loaded %s\n",file_name);
            // unsigned char a,b,c;
            // fread(&a,sizeof(unsigned char),1,file_bin);
            // fread(&b,sizeof(unsigned char),1,file_bin);
            // fread(&c,sizeof(unsigned char),1,file_bin);

            // printf("%hhu %hhu %hhu",a,b,c);
        //unsigned char** pixels = read_pixels(my_image.width,my_image.height,file); 
      //  if(pixels != NULL)
        //    printf("Loaded %s\n",file_name);

        // COD SUPLIMENTAR

      //  free_pixels(my_image.height,&pixels);
        //*width = my_image.width;
       // *height = my_image.height;
            if(fclose(file_bin) == EOF)
               return (unsigned char**) FILE_CLOSE_ERROR;

            return (unsigned char**)SUCCESS;
        }
        else if(c=='4') {
        //    if(pixels != NULL)
        //      printf("Loaded %s\n",file_name);
            // DO STUFF WITH PPM - BINARY
            // READ SIZE
            // ALLOC SIZE
            // FREE SIZE

   // *width = my_image.width;
      //  *height = my_image.height;
            if(fclose(file_bin) == EOF)
               return (unsigned char**) FILE_CLOSE_ERROR;

            return (unsigned char**) SUCCESS;
        }
    }

    return (unsigned char**) SUCCESS;

}

// This function selects a part of the area.
void SELECT(int* x1, int* y1, int* x2, int* y2, int *width, int *height){
    if(*x1<0 || *x2 < 0 || *y1 < 0 || *y2 < 0) 
        printf("Invalid coordinates1\n");
    else if(*x1> *height || *x2 > *height)
        printf("Invalid coordinates2\n");
    else if(*y1> *width || *y2 > *width)
        printf("Invalid coordinates3 %d %d -> %d\n",*y1,*y2,*width);
    else
        printf("Selected %d %d %d %d\n",*x1,*y1,*x2,*y2);

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

// This function rotates the image by a certain angle.
void ROTATE(int angle, unsigned char*** image, int *x1, int *y1, int *x2, int *y2, const int whole_map_selected, int *width, int *height) {
    
    if(!whole_map_selected) {

        // Create copy of the current selection
        unsigned char** pixels = copy_pixels_selection(*x1,*y1,*x2,*y2,image); 
        if( pixels == NULL) 
            return;

        if(angle == 90 || angle == -270) {
            for(int i=0;i<(*x2-*x1);i++) 
                for(int j=0;j<(*y2-*y1);j++) 
                    (*image)[*x1+i][*y1+j]=pixels[*x2-1-j][*y1+i];
        }
        else if(angle == 180 || angle == -180) {
            for(int i=0;i<(*x2-*x1);i++) 
                for(int j=0;j<(*y2-*y1);j++) 
                    (*image)[*x1+i][*y1+j]=pixels[*x2-1-i][*y2-1-j];
        } 
        else if(angle == 270 || angle == -90) {
            for(int i=0;i<(*x2-*x1);i++) 
                for(int j=0;j<(*y2-*y1);j++) 
                    (*image)[*x2-1-j][*y1+i]=pixels[*x1+i][*y1+j];
        }  
        free_pixels((*x2-*x1),&pixels);
    }

    else if(whole_map_selected) {

        if(angle == 90 || angle == -270) {
            
            // Memory allocation
            int max_size = *height;
            if (max_size < *width) max_size = *width;

            unsigned char** pixel_matrix = (unsigned char**) calloc(max_size, sizeof(unsigned char*));

            for(int i=0;i<max_size;i++) 
                pixel_matrix[i] = (unsigned char*) calloc(max_size, sizeof(unsigned char));

            // Copy values
            int p=0;
            for(int i=0;i<*width;i++) {
                for(int j=0;j<*height;j++) {
                    pixel_matrix[i][j]=(*image)[*height -1 - j][p];
                    if(j==(*height-1)) p++;
                }
            
            }

            *image=pixel_matrix;
            int aux = *width;
            *width=*height;
            *height=aux;
            *x2=*height;
            *y2=*width;

        }

        else if(angle == 180 || angle == -180) {
            // Memory allocation
            unsigned char** pixel_matrix = (unsigned char**) malloc(*width * sizeof(unsigned char*));

            for(int i=0;i<*width;i++) 
                pixel_matrix[i] = (unsigned char*) malloc(*height * sizeof(unsigned char));

            // Copy values
            for(int i=0;i<*height;i++) {
                for(int j=0;j<*width;j++) {
                    pixel_matrix[i][j]=(*image)[i][j];
                }
            }

            for(int i=0;i<*height;i++) {
                for(int j=0;j<*width;j++) {
                (*image)[i][j]=pixel_matrix[*height-1-i][*width-1-j];

                }
            }

        } 

        else if(angle == 270 || angle == -90) {
            // Memory allocation
            int max_size = *height;
            if (max_size < *width) max_size = *width;

            unsigned char** pixel_matrix = (unsigned char**) calloc(max_size, sizeof(unsigned char*));

            for(int i=0;i<max_size;i++) 
                pixel_matrix[i] = (unsigned char*) calloc(max_size, sizeof(unsigned char));

            // Copy values
            for(int i=0;i<*width;i++) {
                for(int j=0;j<*height;j++) {
                    pixel_matrix[i][j]=(*image)[j][*width-1-i];
                }
            
            }

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
void EXIT(char ** input){
    free(*input);
    exit(EXIT_SUCCESS);
}


  
// This functions checks if an valid command has been received
// and,if true, executes the corresponding function
void check_command(int command_value, int *width,  int *height, int *image_status,int *x1, int *y1, int *x2, int *y2, unsigned char ***image, char** input)
{
    if(command_value ==  -1) {
        char error_input[100];
        fgets(error_input,100,stdin);
        error_input[strlen(error_input)-1]='\0';
        printf("Invalid command\n");
        return;

    }
    
    char *file_name= (char*) malloc(NAME_LENGTH_MAX*sizeof(char));
    int replace1=0,replace2=0,replace3=0,replace4=0, angle=0;
    int no_image_loaded=0;
    int whole_map_selected=0;
    
    switch(command_value) {
        
        // LOAD
        case 0:
        
            scanf("%s",file_name);
            *image = LOAD(file_name,width,height,x1,y1,x2,y2);
            if(*image != NULL)
                *image_status=UP;

            break;

       // SELECT
        case 1:
                // SELECT WITH COORDINATES
                if((scanf("%d %d %d %d",&replace1,&replace2,&replace3,&replace4)) == 4 ) {
                    if(*image_status == UP)
                    {
                        *x1=replace1;
                        *y1=replace2;
                        *x2=replace3;
                        *y2=replace4;
                        SELECT(x1,y1,x2,y2,width,height);
                    }
                    else  {
                        printf("No image loaded\n");
                        no_image_loaded=1;
                    }
                    
                }
                break;     
                
        // SELECT ALL
        case 2:   
            SELECT_ALL(width,height,x1,y1,x2,y2);
            break;

        // ROTATE    
        case 3:
               if(scanf("%d",&angle)) {
                    if(*image_status == UP) {
                        if(angle != 90 && angle !=-90 && angle != 180 && angle !=-180 && angle !=270 && angle !=-270)
                            {printf("Invalid parameters\n"); no_image_loaded=1;}
                        else if( ( (*x2-*x1) != (*y2-*y1)) && (*x1!=0 || *y1 !=0 || *x2!=*height || *y2 !=*width))
                            {printf("The selection must be square\n");no_image_loaded=1;}
                        else {
                            if(*x1==0 && *y1==0 && *x2== *height && *y2 == *width)
                                whole_map_selected = 1;
                            ROTATE(angle, image,x1,y1,x2,y2,whole_map_selected,width,height);
                        }
                        
                    } else  {
                        printf("No image loaded\n");
                        no_image_loaded=1;
                        }
                }
                break;

        // CROP   
        case 4:
                CROP();
                break;
            
        // GREYSCALE    
        case 5:
           if(*image_status == UP)
                GRAYSCALE();
            else  {
                printf("No image loaded\n");
                no_image_loaded=1;
            }
                break;

        // SEPIA    
        case 6:
            if(*image_status == UP)
                SEPIA();
            else  {
                printf("No image loaded\n");
                no_image_loaded=1;
            }
            break;
            
        // SAVE    
        case 7:
            if(*image_status == UP)
                SAVE();
            else  {
                printf("No image loaded\n");
                no_image_loaded=1;
            }
            break;

        // EXIT 
        case 8:
                EXIT(input);
                break;

        // INVALID COMMAND
        default:
            if(no_image_loaded==1)
                printf("Invalid command\n");
            break;
        
    }

} 
