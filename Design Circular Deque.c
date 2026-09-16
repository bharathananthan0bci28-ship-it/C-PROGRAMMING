#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} MyCircularDeque;

// Initializes the deque with a maximum size of k
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    obj->data = (int*)malloc(sizeof(int) * k);
    obj->front = 0;
    obj->rear = 0; // Points to the next available position at the back
    obj->size = 0;
    obj->capacity = k;
    return obj;
}

// Checks whether the circular deque is empty
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->size == 0;
}

// Checks whether the circular deque is full
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return obj->size == obj->capacity;
}

// Adds an item at the front of Deque. Returns true if successful
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    // Decrement front circularly
    obj->front = (obj->front - 1 + obj->capacity) % obj->capacity;
    obj->data[obj->front] = value;
    obj->size++;
    return true;
}

// Adds an item at the rear of Deque. Returns true if successful
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    // Insert at current rear, then increment rear circularly
    obj->data[obj->rear] = value;
    obj->rear = (obj->rear + 1) % obj->capacity;
    obj->size++;
    return true;
}

// Deletes an item from the front of Deque. Returns true if successful
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    // Increment front circularly
    obj->front = (obj->front + 1) % obj->capacity;
    obj->size--;
    return true;
}

// Deletes an item from the rear of Deque. Returns true if successful
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    // Decrement rear circularly
    obj->rear = (obj->rear - 1 + obj->capacity) % obj->capacity;
    obj->size--;
    return true;
}

// Returns the front item from Deque. Returns -1 if empty
int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    return obj->data[obj->front];
}

// Returns the last item from Deque. Returns -1 if empty
int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    // The last element resides at index (rear - 1)
    return obj->data[(obj->rear - 1 + obj->capacity) % obj->capacity];
}

// Frees the memory allocated for the deque
void myCircularDequeFree(MyCircularDeque* obj) {
    free(obj->data);
    free(obj);
}
