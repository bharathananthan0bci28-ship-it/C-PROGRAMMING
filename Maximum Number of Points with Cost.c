#include <stdio.h>
#include <stdlib.h>

long long maxPoints(int** points, int pointsSize, int* pointsColSize) {
    int m = pointsSize;
    int n = pointsColSize[0];
    
    // DP array to store the maximum points up to the current row
    long long* dp = (long long*)malloc(n * sizeof(long long));
    long long* next_dp = (long long*)malloc(n * sizeof(long long));
    long long* left = (long long*)malloc(n * sizeof(long long));
    long long* right = (long long*)malloc(n * sizeof(long long));
    
    // Initialize DP array with the values of the first row
    for (int j = 0; j < n; j++) {
        dp[j] = points[0][j];
    }
    
    // Process row by row
    for (int i = 1; i < m; i++) {
        // Left-to-right pass: handles optimal choices where previous column <= current column
        left[0] = dp[0];
        for (int j = 1; j < n; j++) {
            long long optimal_prev = left[j - 1] - 1;
            left[j] = (dp[j] > optimal_prev) ? dp[j] : optimal_prev;
        }
        
        // Right-to-left pass: handles optimal choices where previous column >= current column
        right[n - 1] = dp[n - 1];
        for (int j = n - 2; j >= 0; j--) {
            long long optimal_next = right[j + 1] - 1;
            right[j] = (dp[j] > optimal_next) ? dp[j] : optimal_next;
        }
        
        // Calculate the maximum points for the current row's cells
        for (int j = 0; j < n; j++) {
            long long best_prev_score = (left[j] > right[j]) ? left[j] : right[j];
            next_dp[j] = points[i][j] + best_prev_score;
        }
        
        // Move next_dp values into dp for the next iteration step
        long long* temp = dp;
        dp = next_dp;
        next_dp = temp;
    }
    
    // Find the absolute maximum score across all columns in the final row
    long long max_score = dp[0];
    for (int j = 1; j < n; j++) {
        if (dp[j] > max_score) {
            max_score = dp[j];
        }
    }
    
    // Free allocated helper arrays
    free(dp);
    free(next_dp);
    free(left);
    free(right);
    
    return max_score;
}
