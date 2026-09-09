#include <stdlib.h>

// Helper function to find the bound (leftmost or rightmost index)
int findBound(int* nums, int numsSize, int target, int isLeft) {
    int left = 0;
    int right = numsSize - 1;
    int index = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            index = mid; // Record the potential answer
            if (isLeft) {
                right = mid - 1; // Keep searching left for the starting index
            } else {
                left = mid + 1;  // Keep searching right for the ending index
            }
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return index;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    // LeetCode expects us to set the return array size to 2
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    if (numsSize == 0) {
        result[0] = -1;
        result[1] = -1;
        return result;
    }
    
    // Find the first and last positions using the binary search helper
    result[0] = findBound(nums, numsSize, target, 1);
    result[1] = findBound(nums, numsSize, target, 0);
    
    return result;
}
