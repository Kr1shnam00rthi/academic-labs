#include<stdio.h>
#define ROWS 5
#define COLS 10

void set_value(int m_array[5][10]){
    int row,col;
    for(row=0;row<ROWS;row++){
        for(col=0;col<COLS;col++){
            m_array[row][col]=1;
        }
    }
}
int main(){
    int multi[ROWS][COLS];
    set_value(multi);
    for(int row=0;row<ROWS;row++){
        for(int col=0;col<COLS;col++){
            printf("%d ",*(*(multi+row)+col));
        }
        printf("\n");
    }
    return 0;
}
