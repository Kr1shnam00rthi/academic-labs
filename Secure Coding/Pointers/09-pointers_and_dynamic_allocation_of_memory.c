#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int **rptr;
    int *aptr;
    int *testptr;
    int k;
    int nrows = 5; /* Both nrows and ncols could be evaluated */
    int ncols = 8; /* or read in at run time */
    int row, col;

    /* Allocate the memory for the array */
    aptr = malloc(nrows * ncols * sizeof(int));
    if (aptr == NULL)
    {
        puts("\nFailure to allocate room for the array");
        exit(0);
    }

    /* Allocate room for the pointers to the rows */
    rptr = malloc(nrows * sizeof(int *));
    if (rptr == NULL)
    {
        puts("\nFailure to allocate room for pointers");
        free(aptr);  // Free the previously allocated memory to avoid memory leak
        exit(0);
    }

    /* Set up the row pointers */
    for (row = 0; row < nrows; row++)
    {
        rptr[row] = aptr + row * ncols;
    }

    printf("\n\nIllustrating how row pointers are incremented");
    printf("\n\nIndex Pointer(hex) Diff.(dec)");
    for (row = 0; row < nrows; row++)
    {
        printf("\n%d %p", row, rptr[row]);
        if (row > 0)
            printf(" %d", (rptr[row] - rptr[row - 1]));
    }

    printf("\n\nAnd now we print out the array\n");
    for (row = 0; row < nrows; row++)
    {
        for (col = 0; col < ncols; col++)
        {
            rptr[row][col] = row + col;
            printf("%d ", rptr[row][col]);
        }
        putchar('\n');
    }
    puts("\n");

    /* Demonstrate that the 2D array is a contiguous block of memory */
    printf("And now we demonstrate that they are contiguous in memory\n");
    testptr = aptr;
    for (row = 0; row < nrows; row++)
    {
        for (col = 0; col < ncols; col++)
        {
            printf("%d ", *(testptr++));
        }
        putchar('\n');
    }

    /* Free allocated memory */
    free(rptr);
    free(aptr);

    return 0;
}

