#include<stdio.h>
#define ROWS 5
#define COLS 10

int multi[ROWS][COLS];

int main(){
    int row,col;
    for (row=0;row<ROWS;row++){
        for(col=0;col<COLS;col++){
            multi[row][col]=row*col;
        }
    }
    for(row=0;row<ROWS;row++){
        for(col=0;col<COLS;col++){
            printf("%d ",*(*(multi+row)+col)); // 2D array is a pointer to a pointer
        }
        printf("\n");
    }
    return 0;
}
