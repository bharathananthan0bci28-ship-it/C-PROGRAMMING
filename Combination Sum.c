#include <stdio.h>
#include <stdlib.h>

// Comparison function to sort candidates in ascending order
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void backtrack(int* candidates, int candidatesSize, int target, int start, 
               int* current, int currentSize, int*** result, int* returnSize, 
               int** returnColumnSizes, int* capacity) {
    // Base Case: valid combination found
    if (target == 0) {
        // Double capacity if the results storage array is full
        if (*returnSize >= *capacity) {
            *capacity *= 2;
            *result = (int**)realloc(*result, (*capacity) * sizeof(int*));
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, (*capacity) * sizeof(int));
        }
        
        // Deep copy the valid combination into our result list
        (*result)[*returnSize] = (int*)malloc(currentSize * sizeof(int));
        for (int i = 0; i < currentSize; i++) {
            (*result)[*returnSize][i] = current[i];
        }
        (*returnColumnSizes)[*returnSize] = currentSize;
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize; i++) {
        // Pruning: Since candidates are sorted, if the current element exceeds 
        // the remaining target, all subsequent elements will too.
        if (candidates[i] > target) {
            break;
        }

        // Action: Include candidate[i] into the current track
        current[currentSize] = candidates[i];

        // Recurse: Maintain index 'i' because the same element can be reused infinitely
        backtrack(candidates, candidatesSize, target - candidates[i], i, 
                  current, currentSize + 1, result, returnSize, returnColumnSizes, capacity);

        // Backtrack / Undo choice implicitly by letting the next loop override current[currentSize]
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned arrays and *returnColumnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    // Sort to enable efficient sequential pruning
    qsort(candidates, candidatesSize, sizeof(int), compare);

    int capacity = 50; // Initial capacity configuration
    *returnSize = 0;
    
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    
    // Temporary working buffer to hold current path elements
    // Max size of a combination path cannot exceed target / minimum_element (minimum element >= 1)
    int* current = (int*)malloc(target * sizeof(int));

    backtrack(candidates, candidatesSize, target, 0, current, 0, &result, returnSize, returnColumnSizes, &capacity);

    free(current);
    return result;
}
