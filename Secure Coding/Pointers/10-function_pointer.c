#include <stdio.h>
#include <string.h>

#define MAX_BUF 256  // Define a maximum buffer size for swapping

// Arrays to be sorted
long arr[10] = {3, 6, 1, 2, 3, 8, 4, 1, 7, 2};
char arr2[5][20] = {
    "Mickey Mouse",
    "Donald Duck",
    "Minnie Mouse",
    "Goofy",
    "Ted Jensen"
};

// Bubble sort function prototype
void bubble(void *p, int width, int N, int (*fptr)(const void *, const void *));

// Comparison functions
int compare_string(const void *m, const void *n);
int compare_long(const void *m, const void *n);

int main(void) {
    int i;

    // Display the arrays before sorting
    puts("\nBefore Sorting:\n");
    for (i = 0; i < 10; i++) {
        printf("%ld ", arr[i]);  // Print long integers
    }
    puts("\n");
    for (i = 0; i < 5; i++) {
        printf("%s\n", arr2[i]);  // Print strings
    }

    // Sort the long integers
    bubble(arr, sizeof(long), 10, compare_long);
    // Sort the strings
    bubble(arr2, sizeof(arr2[0]), 5, compare_string);

    // Display the arrays after sorting
    puts("\n\nAfter Sorting:\n");
    for (i = 0; i < 10; i++) {
        printf("%ld ", arr[i]);  // Print sorted long integers
    }
    puts("\n");
    for (i = 0; i < 5; i++) {
        printf("%s\n", arr2[i]);  // Print sorted strings
    }

    return 0;
}

// Bubble sort implementation
void bubble(void *p, int width, int N, int (*fptr)(const void *, const void *)) {
    int i, j;
    unsigned char buf[MAX_BUF];  // Buffer to hold temporary data
    unsigned char *bp = p;

    for (i = N - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            // Compare elements using the provided comparison function
            if (fptr(bp + width * j, bp + width * (j + 1)) > 0) {
                // Swap elements
                memcpy(buf, bp + width * j, width);
                memcpy(bp + width * j, bp + width * (j + 1), width);
                memcpy(bp + width * (j + 1), buf, width);
            }
        }
    }
}

// Comparison function for strings
int compare_string(const void *m, const void *n) {
    return strcmp(*(const char **)m, *(const char **)n);  // Compare strings lexicographically
}

// Comparison function for long integers
int compare_long(const void *m, const void *n) {
    long l1 = *(const long *)m;
    long l2 = *(const long *)n;
    return (l1 > l2) - (l1 < l2);  // Compare long integers
}
