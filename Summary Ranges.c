#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be logically allocated via malloc, assume caller frees it.
 */
char** summaryRanges(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    // Allocate memory for the maximum possible number of ranges (one per element)
    char** result = (char**)malloc(numsSize * sizeof(char*));
    int count = 0;

    int i = 0;
    while (i < numsSize) {
        int start = i;

        // Move the pointer forward as long as numbers are consecutive
        // Cast to long to prevent integer overflow during the addition check
        while (i + 1 < numsSize && (long)nums[i + 1] == (long)nums[i] + 1) {
            i++;
        }

        // Each formatted range string needs up to ~25 characters to safely hold 
        // two 32-bit signed integers along with the "->" characters and null terminator.
        result[count] = (char*)malloc(25 * sizeof(char));

        if (start == i) {
            // Single number range
            sprintf(result[count], "%d", nums[start]);
        } else {
            // Multi-number range
            sprintf(result[count], "%d->%d", nums[start], nums[i]);
        }
        
        count++;
        i++; // Move to the start of the next potential range
    }

    *returnSize = count;
    return result;
}
