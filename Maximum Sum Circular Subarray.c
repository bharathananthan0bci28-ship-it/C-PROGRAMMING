#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maxSubarraySumCircular(int* nums, int numsSize) {
    int totalSum = 0;
    int maxSum = nums[0], currentMax = 0;
    int minSum = nums[0], currentMin = 0;

    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];

        // Standard Kadane's to find maximum subarray sum
        currentMax = MAX(nums[i], currentMax + nums[i]);
        maxSum = MAX(maxSum, currentMax);

        // Modified Kadane's to find minimum subarray sum
        currentMin = MIN(nums[i], currentMin + nums[i]);
        minSum = MIN(minSum, currentMin);
    }

    // Edge case: If all numbers are negative, maxSum will hold the largest single negative value.
    // totalSum - minSum would equal 0 (empty subarray), which is invalid since the subarray must be non-empty.
    if (maxSum < 0) {
        return maxSum;
    }

    return MAX(maxSum, totalSum - minSum);
}
