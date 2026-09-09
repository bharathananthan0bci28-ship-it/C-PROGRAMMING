#include <stdio.h>
#include <stdlib.h>

// Structure to represent an event (building edge)
typedef struct {
    int x;
    int height; // Negative for start edge, positive/0 for end edge
    int right;  // The right boundary of the building (only valid for start edges)
    int id;     // Unique identifier for the building to track pairs
} Event;

// Structure for the Max-Heap elements
typedef struct {
    int height;
    int right;
} HeapNode;

// Comparator function for sorting events
int compareEvents(const void* a, const void* b) {
    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    
    if (e1->x != e2->x) {
        return e1->x - e2->x;
    }
    
    // Tie-breaking rules when x-coordinates are identical:
    // 1. Both are starts: process the taller one first (more negative)
    // 2. Both are ends: process the shorter one first (smaller right boundary/height)
    // 3. One start and one end: process the start first
    int h1 = e1->height;
    int h2 = e2->height;
    return h1 - h2;
}

// Max-Heap Functions
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(HeapNode* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[idx].height > heap[parent].height) {
            swap(&heap[idx], &heap[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(HeapNode* heap, int size, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < size && heap[left].height > heap[largest].height) {
        largest = left;
    }
    if (right < size && heap[right].height > heap[largest].height) {
        largest = right;
    }
    if (largest != idx) {
        swap(&heap[idx], &heap[largest]);
        heapifyDown(heap, size, largest);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned arrays and *returnColumnSizes must be logically allocated.
 */
int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize, int* returnSize, int** returnColumnSizes) {
    if (buildingsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int numEvents = buildingsSize * 2;
    Event* events = (Event*)malloc(numEvents * sizeof(Event));
    
    // Step 1: Generate Events
    int eventIdx = 0;
    for (int i = 0; i < buildingsSize; i++) {
        events[eventIdx++] = (Event){buildings[i][0], -buildings[i][2], buildings[i][1], i}; // Start
        events[eventIdx++] = (Event){buildings[i][1], buildings[i][2], buildings[i][1], i};  // End
    }
    
    // Step 2: Sort Events
    qsort(events, numEvents, sizeof(Event), compareEvents);
    
    // Step 3: Initialize Heap and Result Allocations
    HeapNode* maxHeap = (HeapNode*)malloc((buildingsSize + 1) * sizeof(HeapNode));
    int heapSize = 0;
    
    // Push ground level baseline
    maxHeap[heapSize++] = (HeapNode){0, 2e9}; // Extreme right boundary
    
    int** result = (int**)malloc(numEvents * sizeof(int*));
    *returnColumnSizes = (int*)malloc(numEvents * sizeof(int));
    int resultCount = 0;
    
    int prevMaxHeight = 0;
    
    // Step 4: Process Sweepline Events
    for (int i = 0; i < numEvents; i++) {
        Event currEvent = events[i];
        
        if (currEvent.height < 0) {
            // Start event: insert into max-heap
            maxHeap[heapSize] = (HeapNode){-currEvent.height, currEvent.right};
            heapifyUp(maxHeap, heapSize);
            heapSize++;
        }
        
        // Clean up out-of-bounds nodes from the top of the heap
        while (heapSize > 0 && maxHeap[0].right <= currEvent.x) {
            maxHeap[0] = maxHeap[heapSize - 1];
            heapSize--;
            heapifyDown(maxHeap, heapSize, 0);
        }
        
        int currMaxHeight = maxHeap[0].height;
        
        // If height changes, record a key point
        if (currMaxHeight != prevMaxHeight) {
            // Overwrite if the x coordinate matches the last recorded point to avoid vertical line duplicates
            if (resultCount > 0 && result[resultCount - 1][0] == currEvent.x) {
                result[resultCount - 1][1] = currMaxHeight;
            } else {
                result[resultCount] = (int*)malloc(2 * sizeof(int));
                result[resultCount][0] = currEvent.x;
                result[resultCount][1] = currMaxHeight;
                (*returnColumnSizes)[resultCount] = 2;
                resultCount++;
            }
            prevMaxHeight = currMaxHeight;
        }
    }
    
    // Clean up auxiliary allocations
    free(events);
    free(maxHeap);
    
    *returnSize = resultCount;
    return result;
}
