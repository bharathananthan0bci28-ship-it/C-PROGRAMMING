#include <stdio.h>
#include <stdlib.h>

// Comparison function for sorting integers in ascending order
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int minRectanglesToCoverPoints(int** points, int pointsSize, int* pointsColSize, int w) {
    if (pointsSize == 0) return 0;

    // Step 1: Extract all the x-coordinates into a dynamic array
    int* x_coords = (int*)malloc(pointsSize * sizeof(int));
    for (int i = 0; i < pointsSize; i++) {
        x_coords[i] = points[i][0];
    }

    // Step 2: Sort the x-coordinates
    qsort(x_coords, pointsSize, sizeof(int), compare_ints);

    // Step 3: Use a greedy approach to find the minimum number of rectangles
    int rectangles_count = 0;
    int i = 0;

    while (i < pointsSize) {
        rectangles_count++;
        // The current rectangle starts at x_coords[i] and covers up to x_coords[i] + w
        int max_x_covered = x_coords[i] + w;

        // Skip all points that are already covered by this rectangle
        while (i < pointsSize && x_coords[i] <= max_x_covered) {
            i++;
        }
    }

    // Free allocated memory
    free(x_coords);

    return rectangles_count;
}
