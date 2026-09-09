#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper macro to find the minimum of two values
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        return 0;
    }
    
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int maxSide = 0;
    
    // DP array to store results of the current/previous row
    // Allocated with size cols + 1 to handle boundaries cleanly (1-indexed mapping)
    int* dp = (int*)calloc(cols + 1, sizeof(int));
    int prev = 0; // Stores the top-left neighbor value dp[i-1][j-1]
    
    for (int i = 0; i < rows; i++) {
        for (int j = 1; j <= cols; j++) {
            int temp = dp[j]; // Save the value before it gets overwritten
            
            if (matrix[i][j - 1] == '1') {
                // dp[j] is top, dp[j-1] is left, prev is top-left
                dp[j] = MIN(MIN(dp[j], dp[j - 1]), prev) + 1;
                if (dp[j] > maxSide) {
                    maxSide = dp[j];
                }
            } else {
                dp[j] = 0;
            }
            
            prev = temp; // Current old value becomes the top-left for the next cell
        }
        prev = 0; // Reset top-left baseline at the start of each row
    }
    
    free(dp);
    return maxSide * maxSide; // Return the area of the largest square
}
