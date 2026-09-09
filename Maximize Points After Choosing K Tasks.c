#include <stdio.h>
#include <stdlib.h>

// Comparison function to sort integers in descending order
int compareDescending(const void* a, const void* b) {
    int val1 = *(const int*)a;
    int val2 = *(const int*)b;
    if (val1 < val2) return 1;
    if (val1 > val2) return -1;
    return 0;
}

long long maxPoints(int* technique1, int technique1Size, int* technique2, int technique2Size, int k) {
    int n = technique1Size;
    int* diffs = (int*)malloc(n * sizeof(int));
    long long total_points = 0;
    
    // Step 1: Base score assuming everything uses technique 2, and calculate point advantage
    for (int i = 0; i < n; i++) {
        total_points += technique2[i];
        diffs[i] = technique1[i] - technique2[i];
    }
    
    // Step 2: Sort differences in descending order to prioritize optimal technique 1 choices
    qsort(diffs, n, sizeof(int), compareDescending);
    
    // Step 3: Mandatorily take the top k tasks with technique 1
    for (int i = 0; i < k; i++) {
        total_points += diffs[i];
    }
    
    // Step 4: For the rest, choose technique 1 only if it increases total points
    for (int i = k; i < n; i++) {
        if (diffs[i] > 0) {
            total_points += diffs[i];
        }
    }
    
    // Free dynamic array allocation
    free(diffs);
    
    return total_points;
}
