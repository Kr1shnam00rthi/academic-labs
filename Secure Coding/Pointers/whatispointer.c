#include<stdio.h>

int j,k;
int *ptr; //pointer variable

int main(){
    j=1;
    k=2;
    ptr=&k;  // & Uniary reference operator to fetch address
    printf("j has a value %d and is stored at  %p\n", j, &j); 
    printf("k has a value %d and is stored at  %p\n", k, &k);
    printf("ptr has a value %p and is stored at %p\n", ptr, &ptr);
    printf("The value of the integer pointed by ptr is %d\n",*ptr); // * Dereference operator
}
