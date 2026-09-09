#include <stdio.h>

// Helper function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to reverse an array segment in-place
void reverse(int* nums, int start, int end) {
    while (start < end) {
        swap(&nums[start], &nums[end]);
        start++;
        end--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    if (numsSize <= 1) return;

    // Step 1: Find the first decreasing element from the right
    int i = numsSize - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }

    // Step 2: If a decreasing element is found, find its next larger element to swap with
    if (i >= 0) {
        int j = numsSize - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        swap(&nums[i], &nums[j]);
    }

    // Step 3: Reverse the suffix sequence to get the lexicographically smallest arrangement
    reverse(nums, i + 1, numsSize - 1);
}
