#include <stdio.h>
#include <stdlib.h>

// Comparison function for non-increasing order (descending)
int cmp_desc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

// Comparison function for non-decreasing order (ascending)
int cmp_asc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** sortMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    
    *returnSize = n;
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    int** res = (int**)malloc(n * sizeof(int*));
    
    // Allocate memory and copy original grid values into the result matrix
    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = n;
        res[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            res[i][j] = grid[i][j];
        }
    }
    
    // 1. Bottom-left triangle including the main diagonal (starts at grid[i][0] for i = 0 to n-1)
    // These must be sorted in non-increasing (descending) order.
    for (int i = 0; i < n; i++) {
        int len = n - i; // Length of this diagonal
        int* temp = (int*)malloc(len * sizeof(int));
        
        for (int k = 0; k < len; k++) {
            temp[k] = res[i + k][k];
        }
        
        qsort(temp, len, sizeof(int), cmp_desc);
        
        for (int k = 0; k < len; k++) {
            res[i + k][k] = temp[k];
        }
        free(temp);
    }
    
    // 2. Top-right triangle excluding the main diagonal (starts at grid[0][j] for j = 1 to n-1)
    // These must be sorted in non-decreasing (ascending) order.
    for (int j = 1; j < n; j++) {
        int len = n - j; // Length of this diagonal
        int* temp = (int*)malloc(len * sizeof(int));
        
        for (int k = 0; k < len; k++) {
            temp[k] = res[k][j + k];
        }
        
        qsort(temp, len, sizeof(int), cmp_asc);
        
        for (int k = 0; k < len; k++) {
            res[k][j + k] = temp[k];
        }
        free(temp);
    }
    
    return res;
}
