#include <stdio.h>

int numberOfPoints(int** nums, int numsSize, int* numsColSize) {
    // Array to track covered points. 
    // Size 101 handles coordinates up to 100 (1-indexed).
    int covered[101] = {0}; 
    
    // Step 1: Mark all points covered by each car
    for (int i = 0; i < numsSize; i++) {
        int start = nums[i][0];
        int end = nums[i][1];
        
        for (int j = start; j <= end; j++) {
            covered[j] = 1;
        }
    }
    
    // Step 2: Count the total unique covered points
    int unique_points_count = 0;
    for (int i = 1; i <= 100; i++) {
        if (covered[i] == 1) {
            unique_points_count++;
        }
    }
    
    return unique_points_count;
}
