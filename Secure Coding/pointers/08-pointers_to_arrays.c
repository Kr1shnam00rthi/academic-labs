#include<stdio.h>

void a_func(int p[]){  

    for (int i=0;i<3;i++){
        printf("%d ",*(p+i));
    }
    printf("\n");
}
void b_func(int *p){

    for(int i=0;i<3;i++){
        printf("%d ",*(p+i));
    }
    printf("\n");
}

// Both the functions are same
// int *p == int p[]
int main(){
    int a[]={1,2,3};
    a_func(a);
    b_func(a);
}
