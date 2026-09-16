#include <stdbool.h>
#include <stdlib.h>

#define MAX_CAPACITY 100 // Adjust capacity based on constraints (LeetCode uses up to 100 calls)

typedef struct {
    int* in_stack;
    int* out_stack;
    int in_top;
    int out_top;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));
    obj->in_stack = (int*)malloc(MAX_CAPACITY * sizeof(int));
    obj->out_stack = (int*)malloc(MAX_CAPACITY * sizeof(int));
    obj->in_top = -1;
    obj->out_top = -1;
    return obj;
}

void myQueuePush(MyQueue* obj, int x) {
    obj->in_top++;
    obj->in_stack[obj->in_top] = x;
}

void moveElements(MyQueue* obj) {
    if (obj->out_top == -1) {
        while (obj->in_top != -1) {
            obj->out_top++;
            obj->out_stack[obj->out_top] = obj->in_stack[obj->in_top];
            obj->in_top--;
        }
    }
}

int myQueuePop(MyQueue* obj) {
    moveElements(obj);
    int front_element = obj->out_stack[obj->out_top];
    obj->out_top--;
    return front_element;
}
int myQueuePeek(MyQueue* obj) {
    moveElements(obj);
    return obj->out_stack[obj->out_top];
}

bool myQueueEmpty(MyQueue* obj) {
    return (obj->in_top == -1 && obj->out_top == -1);
}

void myQueueFree(MyQueue* obj) {
    free(obj->in_stack);
    free(obj->out_stack);
    free(obj);
}
