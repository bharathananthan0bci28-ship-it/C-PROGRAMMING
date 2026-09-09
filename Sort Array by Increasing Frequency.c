#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global frequency array to handle LeetCode constraints: -100 <= nums[i] <= 100
// Index mapping uses an offset of 100 to handle negative values safely.
int frequency[201];

// Custom comparator function for qsort
int compare(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    
    int freq_a = frequency[val_a + 100];
    int freq_b = frequency[val_b + 100];
    
    // 1. If frequencies are different, sort in ascending order of frequency
    if (freq_a != freq_b) {
        return freq_a - freq_b;
    }
    
    // 2. If frequencies match, sort in descending order of actual values
    return val_b - val_a;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* frequencySort(int* nums, int numsSize, int* returnSize) {
    // Reset global frequency tracker array for each test execution
    memset(frequency, 0, sizeof(frequency));
    
    // Step 1: Count frequency of each integer
    for (int i = 0; i < numsSize; i++) {
        frequency[nums[i] + 100]++;
    }
    
    // Step 2: Sort the array using the custom comparator
    qsort(nums, numsSize, sizeof(int), compare);
    
    // Step 3: Populate return requirements
    *returnSize = numsSize;
    return nums;
}
