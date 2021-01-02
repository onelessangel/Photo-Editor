// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Memory.h"

// This function loads the image from the file.
unsigned char** LOAD(const char *file_name, int *width, int *height, int* x1, int* y1, int* x2, int* y2,int* color_image,char *type) {
    
    FILE *file = fopen(file_name,"rt");
    if(file==NULL) {
        printf("Failed to load %s\n",file_name);
        return (unsigned char**) ERR;
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
        *color_image=0;
        *type='t';
        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        return pixels;
    //free_pixels(my_image.height,&pixels);

    }

    else if(c=='3') {
        // DO STUFF WITH RGB ASCII
    
        fscanf(file,"%d %d %d",&my_image.width,&my_image.height,&my_image.max_value);
        unsigned char** pixels = read_pixels(my_image.width*3,my_image.height,file); 
        if(pixels != NULL)
            printf("Loaded %s\n",file_name);

        // COD SUPLIMENTAR
        *width = my_image.width*3;
        *height = my_image.height;
        *x1  = 0;
        *y1=0;
        *x2=my_image.height;
        *y2=my_image.width*3;
        *color_image=1;
        *type='t';
        if(fclose(file) == EOF)
            return (unsigned char**) FILE_CLOSE_ERROR;

        return pixels;

        //free_pixels(my_image.height,&pixels);

     }

    else {
        *type='b';
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
            // P5 - > *color_image=0;
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
//*color_image=0;
      //  free_pixels(my_image.height,&pixels);
        //*width = my_image.width;
       // *height = my_image.height;
            if(fclose(file_bin) == EOF)
               return (unsigned char**) FILE_CLOSE_ERROR;

            return (unsigned char**)SUCC;
        }
        else if(c=='4') {
        //    if(pixels != NULL)
        //      printf("Loaded %s\n",file_name);
            // DO STUFF WITH PPM - BINARY
            // READ SIZE
            // ALLOC SIZE
            // FREE SIZE
            // P6 ->// P5 - > *color_image=0;
//*color_image=1;
   // *width = my_image.width;
      //  *height = my_image.height;
            if(fclose(file_bin) == EOF)
               return (unsigned char**) FILE_CLOSE_ERROR;

            return (unsigned char**) SUCC;
        }
    }

    return (unsigned char**) SUCC;

}

// This function selects a part of the area.
void SELECT(int* x1, int* y1, int* x2, int* y2, int *width, int *height){

        if(*x1<0 || *x2 < 0 || *y1 < 0 || *y2 < 0) 
            printf("Invalid coordinates\n");
        else if(*x1> *height || *x2 > *height)
            printf("Invalid coordinates\n");
        else if(*y1> *width || *y2 > *width)
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
void CROP(int *x1, int *y1, int *x2,int *y2,int *width,int* height) {
    *height=*x2-*x1;
    *width=*y2-*y1;
    printf("Image cropped\n");
}

// This function will turn the image to grayscale format.
void GRAYSCALE(int *x1,int *y1,int *x2,int *y2,unsigned char*** image) {
    double RGB_2_GRAYSCALE=0.00;
    for(int i=*x1;i<*x2;i++)
        for(int j=*y1;j<*y2;j=j+3) {
            RGB_2_GRAYSCALE=((*image)[i][j]+(*image)[i][j+1]+(*image)[i][j+2])/3.0;
            (*image)[i][j]=(*image)[i][j+1]=(*image)[i][j+2]=RGB_2_GRAYSCALE;
        }

    printf("Grayscale filter applied\n");
}

// This function will turn the image to sepia format.
void SEPIA(int *x1,int *y1,int *x2,int *y2,unsigned char*** image){
    int R,G,B;
    for(int i=*x1;i<*x2;i++)
        for(int j=*y1;j<*y2;j=j+3) {

            R=0.393*(*image)[i][j] + 0.769*(*image)[i][j+1] + 0.189* (*image)[i][j+2];
            if(R>255) R = 255;

            G=0.349*(*image)[i][j] + 0.686*(*image)[i][j+1] + 0.168* (*image)[i][j+2];
            if(G>255) G = 255;

            B=0.272*(*image)[i][j] + 0.534*(*image)[i][j+1] + 0.131* (*image)[i][j+2];
            if(B>255) B = 255;

            (*image)[i][j]=R;
            (*image)[i][j+1]=G;
            (*image)[i][j+2]=B;
        }
    printf("Sepia filter applied\n");
}

// This function saves the current image to a file in the specified format.
void SAVE(const char *file_name,const char* type,unsigned char **image,const int width, const int height) {

    FILE *new_file;
    if(*type == 'b')
        new_file=fopen(file_name,"wb");
    else if(*type == 't')
        new_file=fopen(file_name,"wt");
    
    if(new_file == NULL)
        return;
    
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++)  fprintf(new_file,"%hhu ",image[i][j]);
        fprintf(new_file,"\n");
    }

    if(fclose(new_file) == EOF)
            return;

    printf("Saved %s\n",file_name);
}

// This function closes the program.
void EXIT(char ** input){
    free(*input);
    exit(EXIT_SUCCESS);
}
  
// This functions checks if an valid command has been received
// and,if true, executes the corresponding function
void check_command(int command_value, int *width,  int *height, int *image_status,
int *x1, int *y1, int *x2, int *y2, unsigned char ***image, char** input,int* color_image, char *type)
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
            *image = LOAD(file_name,width,height,x1,y1,x2,y2,color_image,type);
            if(*image != NULL)
                *image_status=UPP;

            break;

       // SELECT
        case 1:
                // SELECT WITH COORDINATES
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
                    if(*image_status == UPP) {
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
                if(*image_status == UPP)
                    CROP(x1,y1,x2,y2,width,height);
                else  {
                    printf("No image loaded\n");
                    no_image_loaded=1;
                }

                break;
            
        // GREYSCALE    
        case 5:
           if(*image_status == UPP) {
                if(*color_image == 1)
                    GRAYSCALE(x1,y1,x2,y2,image);
                else 
                    printf("Grayscale filter not available");      
           }     
            else  {
                printf("No image loaded\n");
                no_image_loaded=1;
            }
                break;

        // SEPIA    
        case 6:
            if(*image_status == UPP) {
                if(*color_image == 1)
                    SEPIA(x1,y1,x2,y2,image);
                else 
                    printf("Sepia filter not available");        
           }     
            else  {
                printf("No image loaded\n");
                no_image_loaded=1;
            }
                break;
            
        // SAVE    
        case 7:
            if(*image_status == UPP)
                SAVE(file_name,type,*image,*width,*height);
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
