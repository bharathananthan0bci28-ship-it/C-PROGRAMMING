#include <stdio.h>
#include <stdlib.h>

// Structure to store a point alongside its pre-calculated squared distance
typedef struct {
    int x;
    int y;
    int dist_sq;
} PointDist;

// Comparator function for qsort (sorts in ascending order of squared distance)
int compare(const void *a, const void *b) {
    PointDist *p1 = (PointDist *)a;
    PointDist *p2 = (PointDist *)b;
    return p1->dist_sq - p2->dist_sq;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be highly allocated on the heap.
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {
    // 1. Create a temporary array of structures to hold points and their distances
    PointDist* arr = (PointDist*)malloc(pointsSize * sizeof(PointDist));
    for (int i = 0; i < pointsSize; i++) {
        arr[i].x = points[i][0];
        arr[i].y = points[i][1];
        // Calculate squared distance: x^2 + y^2
        arr[i].dist_sq = points[i][0] * points[i][0] + points[i][1] * points[i][1];
    }

    // 2. Sort the array using the built-in quicksort algorithm
    qsort(arr, pointsSize, sizeof(PointDist), compare);

    // 3. Allocate memory for the final output array (K points)
    int** result = (int**)malloc(k * sizeof(int*));
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    *returnSize = k;

    // 4. Fill the result array with the top K closest points
    for (int i = 0; i < k; i++) {
        result[i] = (int*)malloc(2 * sizeof(int));
        result[i][0] = arr[i].x;
        result[i][1] = arr[i].y;
        (*returnColumnSizes)[i] = 2; // Each point has 2 dimensions (x, y)
    }

    // Free the temporary helper array
    free(arr);

    return result;
}
