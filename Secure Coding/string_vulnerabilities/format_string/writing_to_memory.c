#include<stdio.h>
int main(int argc, char * argv[]){
	int i;
	printf(argv[1],(int *)&i);
	printf("Value of i:  %d",i);
}
