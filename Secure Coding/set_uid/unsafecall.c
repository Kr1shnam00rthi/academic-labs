#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *cat = "/bin/cat";
    if (argc < 2) {
        printf("Please type a file name\n");
        return 1;
    }

    // Allocate enough memory for the command string
    char *command = malloc(strlen(cat) + strlen(argv[1]) + 2);
    if (command == NULL) {
        perror("Unable to allocate memory");
        return 1;
    }

    // Construct the command string
    sprintf(command, "%s %s", cat, argv[1]);

    // Execute the command
    int result = system(command);

    // Free the allocated memory
    free(command);

    return result;
}

