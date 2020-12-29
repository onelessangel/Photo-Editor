#include <stdio.h>

void LOAD(const char *file_name){
    printf("LOADED %s\n",file_name);
}
void SELECT(int x1, int y1, int x2, int y2){
    printf("SELECTED %d %d %d %d\n",x1,y1,x2,y2);
}

void SELECT_ALL(void){
    printf("SELECT ALL\n");
}

void ROTATE(const int angle){
    printf("ROTATE by %d\n",angle);
}

void CROP(void){
    printf("CROP\n");
}

void GREYSCALE(void){
    printf("GREYSCALE\n");
}

void SEPIA(void){
    printf("SEPIA\n");
}

void SAVE(void){
    printf("SAVE\n");
}

void EXIT(void){
    printf("EXIT\n");
}