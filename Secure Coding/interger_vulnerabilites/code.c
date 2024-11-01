
#include <stdio.h>
#include <stdint.h>

void f(void) {
    char *ptr = "example"; // Pointer to a string
    uintptr_t number = (uintptr_t)ptr; // Compliant conversion
    printf("Number: %zu\n", number);
}

int main() {
    f();
    return 0;
}

