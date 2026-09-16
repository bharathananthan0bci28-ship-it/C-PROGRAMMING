#include <stdbool.h>
#include <stdlib.h>

// --- Helper Queue Implementation ---
typedef struct {
    int *data;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;
    return q;
}

void enQueue(Queue* q, int val) {
    q->data[q->rear++] = val;
}

int deQueue(Queue* q) {
    return q->data[q->front++];
}

int peekQueue(Queue* q) {
    return q->data[q->front];
}

bool isQueueEmpty(Queue* q) {
    return q->front == q->rear;
}

void resetQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

void freeQueue(Queue* q) {
    free(q->data);
    free(q);
}


// --- MyStack Implementation ---
typedef struct {
    Queue* q1;
    Queue* q2;
} MyStack;

/** Initializes your data structure here. */
MyStack* myStackCreate() {
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    // Predefining a maximum capacity for simplicity (adjust as needed)
    int max_capacity = 1000; 
    stack->q1 = createQueue(max_capacity);
    stack->q2 = createQueue(max_capacity);
    return stack;
}

/** Pushes element x to the top of the stack. */
void myStackPush(MyStack* obj, int x) {
    // 1. Push new element into q2
    enQueue(obj->q2, x);
    
    // 2. Push all remaining elements from q1 to q2
    while (!isQueueEmpty(obj->q1)) {
        enQueue(obj->q2, deQueue(obj->q1));
    }
    
    // 3. Swap q1 and q2 so that q1 always holds the current stack elements
    Queue* temp = obj->q1;
    obj->q1 = obj->q2;
    obj->q2 = temp;
    
    // Reset q2 to prevent memory overflow index bounds
    resetQueue(obj->q2);
}

/** Removes the element on the top of the stack and returns it. */
int myStackPop(MyStack* obj) {
    return deQueue(obj->q1);
}

/** Returns the element on the top of the stack. */
int myStackTop(MyStack* obj) {
    return peekQueue(obj->q1);
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    return isQueueEmpty(obj->q1);
}

/** Frees the memory allocated for the stack. */
void myStackFree(MyStack* obj) {
    if (obj) {
        freeQueue(obj->q1);
        freeQueue(obj->q2);
        free(obj);
    }
}
