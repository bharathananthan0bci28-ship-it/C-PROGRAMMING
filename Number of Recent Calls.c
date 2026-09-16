#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* requests;
    int front;
    int rear;
} RecentCounter;

// Initializes the counter with zero recent requests
RecentCounter* recentCounterCreate() {
    RecentCounter* obj = (RecentCounter*)malloc(sizeof(RecentCounter));
    // Based on problem constraints, ping is called at most 10,000 times per test case
    obj->requests = (int*)malloc(10005 * sizeof(int));
    obj->front = 0;
    obj->rear = 0;
    return obj;
}

// Adds a new request at time t and returns the number of requests in [t - 3000, t]
int recentCounterPing(RecentCounter* obj, int t) {
    // Append the current timestamp to the end of the queue
    obj->requests[obj->rear++] = t;
    
    // Invalidate and pop elements from the front that are older than t - 3000
    while (obj->requests[obj->front] < t - 3000) {
        obj->front++;
    }
    
    // The size of the remaining window represents the number of recent pings
    return obj->rear - obj->front;
}

// Frees the allocated memory
void recentCounterFree(RecentCounter* obj) {
    if (obj) {
        free(obj->requests);
        free(obj);
    }
}
