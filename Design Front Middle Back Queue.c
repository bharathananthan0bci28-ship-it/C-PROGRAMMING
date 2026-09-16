#include <stdio.h>
#include <stdlib.h>

// Node structure for the Doubly Linked List
typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

// Deque structure supporting front/back operations in O(1)
typedef struct {
    Node* head;
    Node* tail;
    int size;
} Deque;

typedef struct {
    Deque* left;
    Deque* right;
} FrontMiddleBackQueue;

// Helper to create a new node
Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Helper to initialize a Deque
Deque* createDeque() {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->head = NULL;
    dq->tail = NULL;
    dq->size = 0;
    return dq;
}

// Deque operations
void pushFront(Deque* dq, int val) {
    Node* node = createNode(val);
    if (dq->size == 0) {
        dq->head = dq->tail = node;
    } else {
        node->next = dq->head;
        dq->head->prev = node;
        dq->head = node;
    }
    dq->size++;
}

void pushBack(Deque* dq, int val) {
    Node* node = createNode(val);
    if (dq->size == 0) {
        dq->head = dq->tail = node;
    } else {
        node->prev = dq->tail;
        dq->tail->next = node;
        dq->tail = node;
    }
    dq->size++;
}

int popFront(Deque* dq) {
    if (dq->size == 0) return -1;
    Node* temp = dq->head;
    int val = temp->val;
    dq->head = dq->head->next;
    if (dq->head) dq->head->prev = NULL;
    else dq->tail = NULL;
    free(temp);
    dq->size--;
    return val;
}

int popBack(Deque* dq) {
    if (dq->size == 0) return -1;
    Node* temp = dq->tail;
    int val = temp->val;
    dq->tail = dq->tail->prev;
    if (dq->tail) dq->tail->next = NULL;
    else dq->head = NULL;
    free(temp);
    dq->size--;
    return val;
}

// Balance the two deques to maintain our size invariant
void balance(FrontMiddleBackQueue* obj) {
    if (obj->left->size > obj->right->size) {
        pushFront(obj->right, popBack(obj->left));
    } else if (obj->right->size > obj->left->size + 1) {
        pushBack(obj->left, popFront(obj->right));
    }
}

// Core Interface Functions
FrontMiddleBackQueue* frontMiddleBackQueueCreate() {
    FrontMiddleBackQueue* obj = (FrontMiddleBackQueue*)malloc(sizeof(FrontMiddleBackQueue));
    obj->left = createDeque();
    obj->right = createDeque();
    return obj;
}

void frontMiddleBackQueuePushFront(FrontMiddleBackQueue* obj, int val) {
    pushFront(obj->left, val);
    balance(obj);
}

void frontMiddleBackQueuePushMiddle(FrontMiddleBackQueue* obj, int val) {
    if (obj->left->size == obj->right->size) {
        pushFront(obj->right, val);
    } else {
        pushBack(obj->left, val);
    }
}

void frontMiddleBackQueuePushBack(FrontMiddleBackQueue* obj, int val) {
    pushBack(obj->right, val);
    balance(obj);
}

int frontMiddleBackQueuePopFront(FrontMiddleBackQueue* obj) {
    if (obj->left->size + obj->right->size == 0) return -1;
    int val = (obj->left->size > 0) ? popFront(obj->left) : popFront(obj->right);
    balance(obj);
    return val;
}

int frontMiddleBackQueuePopMiddle(FrontMiddleBackQueue* obj) {
    if (obj->left->size + obj->right->size == 0) return -1;
    int val;
    if (obj->left->size == obj->right->size) {
        val = popBack(obj->left);
    } else {
        val = popFront(obj->right);
    }
    return val;
}

int frontMiddleBackQueuePopBack(FrontMiddleBackQueue* obj) {
    if (obj->left->size + obj->right->size == 0) return -1;
    int val = popBack(obj->right);
    balance(obj);
    return val;
}

void frontMiddleBackQueueFree(FrontMiddleBackQueue* obj) {
    while (obj->left->size > 0) popFront(obj->left);
    while (obj->right->size > 0) popFront(obj->right);
    free(obj->left);
    free(obj->right);
    free(obj);
}
