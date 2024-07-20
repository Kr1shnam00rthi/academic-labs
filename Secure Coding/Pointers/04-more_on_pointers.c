#include<stdio.h>

char strA[80]="A string to be used for demonstration purposes";
char strB[80];

char my_strcpy(char destination[],char source[]){
int i=0;
while(source[i]!='\0'){
destination[i]=source[i];
i++;
}
destination[i]='\0';
}
int main(){
printf("String B: %s\n",strB);
my_strcpy(strB,strA);
//puts(strB);
printf("String B: %s",strB);

char a[5]="12345";
    a[3]='x';
    printf("%c\n",*(a+3));
    puts(a);
    3[a]='y';
    // 3[a] == a[3] == *(a+3) == *(3+a)
    puts(a);
}
