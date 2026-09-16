#include <stdio.h>

int minKBitFlips(int* nums, int numsSize, int k) {
    int total_flips = 0;
    int current_flips = 0;

    for (int i = 0; i < numsSize; i++) {
        // If the sliding window has moved past a flip that started at index i - k,
        // remove its effect from current_flips.
        if (i >= k && nums[i - k] > 1) {
            current_flips--;
            nums[i - k] -= 2; // Restore original array values (optional cleanup)
        }

        // Check if the current bit needs to be flipped.
        // It needs a flip if its current value after previous flips is 0.
        // (nums[i] + current_flips) % 2 == 0 means it evaluates to 0.
        if ((nums[i] + current_flips) % 2 == 0) {
            // If we need to flip but there aren't enough elements left for a window of size k,
            // it's impossible to flip all 0s to 1s.
            if (i + k > numsSize) {
                return -1;
            }
            
            // Mark that a flip starts at index i by modifying the value in-place (+2)
            nums[i] += 2;
            current_flips++;
            total_flips++;
        }
    }

    return total_flips;
}
