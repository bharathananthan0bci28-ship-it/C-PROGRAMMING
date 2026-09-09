#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    // Check if all digits are 9
    int allNines = 1;
    for (int i = 0; i < digitsSize; i++) {
        if (digits[i] != 9) {
            allNines = 0;
            break;
        }
    }

    // Case 1: All digits are 9 (e.g., 999 -> 1000)
    if (allNines) {
        *returnSize = digitsSize + 1;
        int* result = (int*)malloc((*returnSize) * sizeof(int));
        
        result[0] = 1;
        for (int i = 1; i < *returnSize; i++) {
            result[i] = 0;
        }
        return result;
    } 
    
    // Case 2: Normal increment with standard carry propagation
    *returnSize = digitsSize;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    int carry = 1;
    
    for (int i = digitsSize - 1; i >= 0; i--) {
        int sum = digits[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    
    return result;
}
