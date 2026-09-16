#include <stdio.h>
#include <stdlib.h>

int minKBitFlips(int* nums, int numsSize, int k) {
    // isFlipped[i] will be 1 if a flip started at index i
    int* isFlipped = (int*)calloc(numsSize, sizeof(int));
    int totalFlips = 0;
    int currentFlips = 0; // Number of active flips affecting the current index

    for (int i = 0; i < numsSize; i++) {
        // Remove the effect of the flip that started at index (i - k)
        if (i >= k) {
            currentFlips ^= isFlipped[i - k];
        }

        // If the current bit is 0 after considering all active flips, we must flip
        if ((nums[i] ^ currentFlips) == 0) {
            // If there's not enough room to flip a subarray of length k, it's impossible
            if (i + k > numsSize) {
                free(isFlipped);
                return -1;
            }

            // Record a new flip starting at index i
            isFlipped[i] = 1;
            currentFlips ^= 1;
            totalFlips++;
        }
    }

    free(isFlipped);
    return totalFlips;
}
