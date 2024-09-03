#include <stdio.h>   // For printf function
#include <unistd.h>  // For execve function

int main(int argc, char *argv[]) {
    char *v[3];

    // Corrected the if condition syntax
    if (argc < 2) {
        printf("Please type a file name\n");
        return 1;
    }

    v[0] = "/bin/cat";  // Assuming you meant "cat" instead of "car"
    v[1] = argv[1];
    v[2] = NULL;  // NULL-terminate the argument list

    execve(v[0], v, NULL);

    // If execve returns, there was an error
    perror("execve failed");
    return 1;
}

