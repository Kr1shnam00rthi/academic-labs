#include<stdio.h>

char strA[80]="A string to be used for demonstration purposes";
char strB[80];

char my_strcpy(char *destination,char *source){
    char *p=destination;
    while(*source!='\0'){
        *p++=*source++;
    }
    *p='\0';
}
int main(){
    printf("String B: %s\n",strB);
    my_strcpy(strB,strA);
    //puts(strB);
    printf("String B: %s",strB);
}
