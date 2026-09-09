#include <stdio.h>

// Helper function to swap two integers in place
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int firstMissingPositive(int* nums, int numsSize) {
    // Step 1: Cycle Sort - Place each number in its correct bucket index if possible
    for (int i = 0; i < numsSize; i++) {
        // Correct target index for value nums[i] is nums[i] - 1
        while (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1]) {
            swap(&nums[i], &nums[nums[i] - 1]);
        }
    }
    
    // Step 2: Scan the array to locate the first mismatch index
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1; // The missing positive number
        }
    }
    
    // Step 3: If all spots 1 to n match perfectly, the first missing is n + 1
    return numsSize + 1;
}
