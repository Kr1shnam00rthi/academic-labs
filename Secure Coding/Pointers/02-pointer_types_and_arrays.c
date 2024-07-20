#include<stdio.h>

int array[]={1,2,3,4,5,10};
int *ptr;

int main(){
    int i;
    ptr= &array[0]; // Stores the address of first element in a array
    //ptr=array; Same to above
    for(i=0;i<6;i++){
        printf("array[%d] = %d\n",i,array[i]);
        printf("ptr+%d = %d\n",i,*(ptr+i));// Pointer addition  
    } 
    return 0;
}
