#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort cards in increasing order
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* deckRevealedIncreasing(int* deck, int deckSize, int* returnSize) {
    // 1. Sort the deck in ascending order
    qsort(deck, deckSize, sizeof(int), compare);
    
    // 2. Allocate the result array
    int* result = (int*)malloc(deckSize * sizeof(int));
    *returnSize = deckSize;
    
    // 3. Create a circular queue to simulate card index movements
    int* queue = (int*)malloc((deckSize * 2) * sizeof(int)); // Extra space for queue operations
    int front = 0;
    int rear = 0;
    
    // Populate the queue with initial indices
    for (int i = 0; i < deckSize; i++) {
        queue[rear++] = i;
    }
    
    // 4. Distribute the sorted cards into their correct positions
    for (int i = 0; i < deckSize; i++) {
        // Reveal the top card's position index and assign the sorted card
        int targetIdx = queue[front++];
        result[targetIdx] = deck[i];
        
        // If there are still card positions left, move the next index to the bottom
        if (front < rear) {
            queue[rear++] = queue[front++];
        }
    }
    
    // Clean up temporary queue memory
    free(queue);
    
    return result;
}
