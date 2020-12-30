// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#define NAME_LENGTH_MAX 100

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
    FIle_CLOSE_ERROR = 5,
    SUCCESS = 0,
    ERROR = -1
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

// This functions frees the memory from the currently loaded image.
void free_pixels(const int my_image_height,unsigned char*** pixel_matrix)
{
    
    for(int i=0;i<my_image_height;i++) 
            free((*pixel_matrix)[i]);

    free(*pixel_matrix);
}

// This function loads the image from the file.
int LOAD(const char *file_name, int *width, int *height) {
    
    FILE *file = fopen(file_name,"rt");
    if(file==NULL) {
        printf("Failed to load %s\n",file_name);
        return ERROR;
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
        
        free_pixels(my_image.height,&pixels);
        if(fclose(file) == EOF)
            exit(FIle_CLOSE_ERROR);

        return SUCCESS;

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
        free_pixels(my_image.height,&pixels);
        if(fclose(file) == EOF)
            exit(FIle_CLOSE_ERROR);
        return SUCCESS;

    }

    else {
        ungetc(b,file);
        ungetc(c,file);

        if(fclose(file) == EOF)
            exit(FIle_CLOSE_ERROR);

        FILE *file_bin = fopen(file_name,"rb");
        if(file_bin==NULL) 
            exit(FILE_OPEN_ERROR);
        

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
               exit(FIle_CLOSE_ERROR);
            return SUCCESS;
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
                exit(FIle_CLOSE_ERROR);
            return SUCCESS;
        }
    }

    return SUCCESS;

}

// This function selects a part of the area.
void SELECT(int* x1, int* y1, int* x2, int* y2, int *width, int *height){
    if(*x1<0 || *x2 < 0 || *y1 < 0 || *y2 < 0) 
        printf("Invalid coordinates\n");
    else if(*x1>*height || *x2 > *height)
        printf("Invalid coordinates\n");
    else if(*y1>*width || *y2 > *width)
        printf("Invalid coordinates\n");
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
void SELECT_ALL(int *width, int *height){
    printf("SELECT ALL from %d to %d\n",*width,*height);
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
    exit(EXIT_SUCCESS);
}


  
// This functions checks if an valid command has been received
// and,if true, executes the corresponding function
void check_command(int command_value, int *width,  int *height, int *image_status,int *x1, int *y1, int *x2, int *y2)
{
    char *file_name= (char*) malloc(NAME_LENGTH_MAX*sizeof(char));

    switch(command_value) {
        
        // LOAD
        case 0:
            scanf("%s",file_name);
            if(LOAD(file_name,width,height)==SUCCESS) *image_status=UP;
            break;

        // SELECT
        case 1:
                // SELECT WITH COORDINATES
                if((scanf("%d %d %d %d",x1,y1,x2,y2)) == 4 ) {
                    if(*image_status == UP)
                        SELECT(x1,y1,x2,y2,width,height);
                    else 
                        printf("No image loaded\n");
                    break;     
                // SELECT ALL PIXELS
                } else {
                    SELECT_ALL(width,height);
                    break;            
                } 

        // CASE FOR SELECT ALL PIXELS  
        case 2:
            printf("Invalid command\n");
           
            break;

        // ROTATE    
        case 3:
                if(*image_status == UP)
                    ROTATE(45);
                else 
                        printf("No image loaded\n");
                break;

        // CROP   
        case 4:
                CROP();
                break;
            
        // GREYSCALE    
        case 5:
            if(*image_status == UP)
                GRAYSCALE();
            else 
                    printf("No image loaded\n");
                break;

        // SEPIA    
        case 6:
            if(*image_status == UP)
                SEPIA();
            else 
                    printf("No image loaded\n");
                break;
        // SAVE    
        case 7:
            if(*image_status == UP)
                SAVE();
            else 
                    printf("No image loaded\n");
                break;

        // EXIT 
        case 8:
                EXIT();
                break;

        // INVALID COMMAND
        default:
            printf("Invalid command\n");
            break;
        
    }

} 
