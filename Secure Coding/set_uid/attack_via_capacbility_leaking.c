#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *v[2];

    // Attempt to open /etc/zzz with read-write and append flags
    fd = open("/etc/zzz", O_RDWR | O_APPEND);
    if (fd == -1) {
        printf("Cannot open /etc/zzz\n");
        exit(0);
    }

    // Print out the file descriptor value
    printf("fd is %d\n", fd);

    // Downgrade privileges to the real user ID
    setuid(getuid());

    // Now execute a shell
    v[0] = "/bin/sh";
    v[1] = NULL;
    execve(v[0], v, NULL);
   // to solve the issue the file decsriptor should be closed before we downgrade privilege
    return 0;
}

