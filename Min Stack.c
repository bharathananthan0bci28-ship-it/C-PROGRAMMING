#include <stdlib.h>

// Structure to store each element along with the minimum value at that state
typedef struct {
    int val;
    int min;
} StackNode;

typedef struct {
    StackNode* data;
    int top;
    int capacity;
} MinStack;

/** Initializes the stack object */
MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->capacity = 30000; // Sufficient initial capacity for typical constraints
    obj->data = (StackNode*)malloc(obj->capacity * sizeof(StackNode));
    obj->top = -1;
    return obj;
}

/** Pushes the element val onto the stack */
void minStackPush(MinStack* obj, int val) {
    obj->top++;
    
    // Resize dynamically if the stack runs out of capacity
    if (obj->top == obj->capacity) {
        obj->capacity *= 2;
        obj->data = (StackNode*)realloc(obj->data, obj->capacity * sizeof(StackNode));
    }
    
    obj->data[obj->top].val = val;
    
    // Update the minimum value for the current element
    if (obj->top == 0) {
        obj->data[obj->top].min = val;
    } else {
        int current_min = obj->data[obj->top - 1].min;
        obj->data[obj->top].min = (val < current_min) ? val : current_min;
    }
}

/** Removes the element on the top of the stack */
void minStackPop(MinStack* obj) {
    if (obj->top >= 0) {
        obj->top--;
    }
}

/** Gets the top element of the stack */
int minStackTop(MinStack* obj) {
    return obj->data[obj->top].val;
}

/** Retrieves the minimum element in the stack */
int minStackGetMin(MinStack* obj) {
    return obj->data[obj->top].min;
}

/** Deallocates the memory used by the stack */
void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj);
}
