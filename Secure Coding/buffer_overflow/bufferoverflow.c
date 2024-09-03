#include <stdio.h>
#include <string.h>

// here the input argument 2 overflows the memory of authentication variable and instead of 0 and non- zero value presents which gives access to the granted portion
int main(int argc, char** argv)
{
    int authentication = 0; // Corrected initialization here
    char cUsername[10], cPassword[10];

    // Copying user input to cUsername and cPassword without bounds checking
    strcpy(cUsername, argv[1]);
    strcpy(cPassword, argv[2]);

    // Simple authentication check
    if(strcmp(cUsername, "admin") == 0 && strcmp(cPassword, "adminpass") == 0)
    {
        authentication = 1;
    }
    printf("%d",authentication);
    // Checking if authentication was successful
    if(authentication)
    {
        printf("Access granted\n");
    }
    else
    {
        printf("Wrong username and password\n");
    }

    return 0;
}


_________________________________________
	  |	      |			|
cUsername | cPassword | authentication[]|

now the large value in cPassword variable overflows next memory location / access the memory of authentication and changes the value in it 
