#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int constrainedSubsetSum(int* nums, int numsSize, int k) {
    // dp[i] stores the maximum subsequence sum ending at index i
    int* dp = (int*)malloc(numsSize * sizeof(int));
    
    // Deque to store indices of the dp array. 
    // It will keep the indices of maximum dp values within the window of size k.
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int head = 0, tail = 0; // Pointers for the front and back of the deque

    int max_sum = nums[0];

    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices that are out of the valid sliding window [i - k, i - 1]
        if (head < tail && deque[head] < i - k) {
            head++;
        }

        // 2. Compute dp[i]. If the maximum available sum in the window is positive, add it.
        int max_prev = (head < tail) ? dp[deque[head]] : 0;
        dp[i] = nums[i] + MAX(0, max_prev);

        // Update the global maximum subsequence sum found so far
        max_sum = MAX(max_sum, dp[i]);

        // 3. Maintain the monotonic property of the deque (descending order of dp values)
        // Remove elements from the back that are smaller than or equal to the current dp[i]
        while (head < tail && dp[deque[tail - 1]] <= dp[i]) {
            tail--;
        }

        // 4. Add the current index to the deque
        deque[tail++] = i;
    }

    // Free allocated memory
    free(dp);
    free(deque);

    return max_sum;
}
