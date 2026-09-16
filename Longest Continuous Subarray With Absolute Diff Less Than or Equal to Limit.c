#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int longestSubarray(int* nums, int numsSize, int limit) {
    // Deque to maintain the maximum elements in decreasing order
    int* max_deque = (int*)malloc(numsSize * sizeof(int));
    int max_head = 0, max_tail = 0;

    // Deque to maintain the minimum elements in increasing order
    int* min_deque = (int*)malloc(numsSize * sizeof(int));
    int min_head = 0, min_tail = 0;

    int left = 0;
    int max_len = 0;

    for (int right = 0; right < numsSize; right++) {
        // Maintain max_deque (decreasing order)
        while (max_head < max_tail && nums[max_deque[max_tail - 1]] <= nums[right]) {
            max_tail--;
        }
        max_deque[max_tail++] = right;

        // Maintain min_deque (increasing order)
        while (min_head < min_tail && nums[min_deque[min_tail - 1]] >= nums[right]) {
            min_tail--;
        }
        min_deque[min_tail++] = right;

        // If the current window violates the condition, shrink it from the left
        while (nums[max_deque[max_head]] - nums[min_deque[min_head]] > limit) {
            left++;
            // Remove elements that fall outside the new window boundaries
            if (max_deque[max_head] < left) {
                max_head++;
            }
            if (min_deque[min_head] < left) {
                min_head++;
            }
        }

        // Calculate the maximum valid window size found so far
        max_len = MAX(max_len, right - left + 1);
    }

    free(max_deque);
    free(min_deque);

    return max_len;
}
