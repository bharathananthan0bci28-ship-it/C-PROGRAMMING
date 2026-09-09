#include <stdlib.h>

#define HASH_SIZE 9973 // A prime number for simple hashing

// Node for tracking individual number frequencies (Hash map item)
typedef struct HashNode {
    int key;
    int count;
    struct HashNode* next;
} HashNode;

// Simple Node for individual stacks
typedef struct StackNode {
    int val;
    struct StackNode* next;
} StackNode;

// Structure for the Frequency Stack
typedef struct {
    HashNode** freqMap;      // Hash table to track counts of each element
    StackNode** groupMap;    // Array of stacks, where index = frequency
    int maxFreq;            // Highest frequency currently in the stack
    int groupCapacity;       // Allocated size for groupMap
} FreqStack;

// --- Helper Functions for Hash Map ---
int hash(int key) {
    int h = key % HASH_SIZE;
    return h < 0 ? h + HASH_SIZE : h;
}

int getFreq(HashNode** table, int key) {
    int idx = hash(key);
    HashNode* curr = table[idx];
    while (curr) {
        if (curr->key == key) return curr->count;
        curr = curr->next;
    }
    return 0;
}

void incFreq(HashNode** table, int key) {
    int idx = hash(key);
    HashNode* curr = table[idx];
    while (curr) {
        if (curr->key == key) {
            curr->count++;
            return;
        }
        curr = curr->next;
    }
    // Key not found, create a new entry
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->count = 1;
    newNode->next = table[idx];
    table[idx] = newNode;
}

void decFreq(HashNode** table, int key) {
    int idx = hash(key);
    HashNode* curr = table[idx];
    while (curr) {
        if (curr->key == key) {
            curr->count--;
            return;
        }
        curr = curr->next;
    }
}

// --- FreqStack Implementation ---

FreqStack* freqStackCreate() {
    FreqStack* obj = (FreqStack*)malloc(sizeof(FreqStack));
    
    // Initialize Frequency Map
    obj->freqMap = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    
    // Initialize Group Map stacks dynamically
    obj->groupCapacity = 2000; 
    obj->groupMap = (StackNode**)calloc(obj->groupCapacity, sizeof(StackNode*));
    
    obj->maxFreq = 0;
    return obj;
}

void freqStackPush(FreqStack* obj, int val) {
    incFreq(obj->freqMap, val);
    int f = getFreq(obj->freqMap, val);
    
    if (f > obj->maxFreq) {
        obj->maxFreq = f;
    }
    
    // Resize group map stacks if maxFreq hits capacity limits
    if (f >= obj->groupCapacity) {
        int oldCap = obj->groupCapacity;
        obj->groupCapacity *= 2;
        obj->groupMap = (StackNode**)realloc(obj->groupMap, obj->groupCapacity * sizeof(StackNode*));
        for (int i = oldCap; i < obj->groupCapacity; i++) {
            obj->groupMap[i] = NULL;
        }
    }
    
    // Push onto the stack corresponding to frequency 'f'
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->val = val;
    newNode->next = obj->groupMap[f];
    obj->groupMap[f] = newNode;
}

int freqStackPop(FreqStack* obj) {
    // Get the element at the top of the max frequency stack
    StackNode* topNode = obj->groupMap[obj->maxFreq];
    int val = topNode->val;
    
    // Pop from stack
    obj->groupMap[obj->maxFreq] = topNode->next;
    free(topNode);
    
    // Decrement element's tracked frequency
    decFreq(obj->freqMap, val);
    
    // Re-adjust maxFreq down if the current level's stack becomes empty
    if (obj->groupMap[obj->maxFreq] == NULL) {
        obj->maxFreq--;
    }
    
    return val;
}

void freqStackFree(FreqStack* obj) {
    // Free Hash map allocations
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* curr = obj->freqMap[i];
        while (curr) {
            HashNode* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(obj->freqMap);
    
    // Free remain stack groups
    for (int i = 0; i <= obj->groupCapacity; i++) {
        if (i < obj->groupCapacity) {
            StackNode* curr = obj->groupMap[i];
            while (curr) {
                StackNode* tmp = curr;
                curr = curr->next;
                free(tmp);
            }
        }
    }
    free(obj->groupMap);
    free(obj);
}
