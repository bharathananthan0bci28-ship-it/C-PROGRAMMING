#include <stdio.h>
#include <stdlib.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    // Create a prefix sum array using 'long long' to prevent integer overflow
    long long* P = (long long*)malloc((numsSize + 1) * sizeof(long long));
    P[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        P[i + 1] = P[i] + nums[i];
    }

    // Allocate space for the monotonic deque to store indices
    int* deque = (int*)malloc((numsSize + 1) * sizeof(int));
    int head = 0; // Front pointer of the deque
    int tail = 0; // Back pointer of the deque
    int minLen = numsSize + 1;

    for (int i = 0; i <= numsSize; i++) {
        // 1. If the current prefix sum minus the smallest prefix sum in the deque is >= k,
        // we found a valid subarray. Update minLen and pop the front element.
        while (head < tail && P[i] - P[deque[head]] >= k) {
            int currentLen = i - deque[head];
            if (currentLen < minLen) {
                minLen = currentLen;
            }
            head++; // pop_front
        }

        // 2. Maintain a strictly increasing order of prefix sums in the deque.
        // If the current prefix sum is smaller than or equal to the back element,
        // the back element is no longer useful as a starting point.
        while (head < tail && P[i] <= P[deque[tail - 1]]) {
            tail--; // pop_back
        }

        // 3. Add the current index to the deque
        deque[tail++] = i; // push_back
    }

    // Free the dynamically allocated memory
    free(P);
    free(deque);

    // If minLen was updated, return it; otherwise, return -1
    return (minLen <= numsSize) ? minLen : -1;
}
