#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 997 // Prime number larger than maximum constraint (N <= 300)

// Node structure for Hash Table chaining
typedef struct HashNode {
    int dx;
    int dy;
    int count;
    struct HashNode* next;
} HashNode;

// Euclidean algorithm to find Greatest Common Divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

// Simple hash function for pairs of integers
unsigned int hash_function(int dx, int dy) {
    unsigned int h = (unsigned int)dx * 31 + (unsigned int)dy;
    return h % HASH_SIZE;
}

int maxPoints(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize <= 2) {
        return pointsSize;
    }

    int max_global = 2;

    // Allocate array of pointers for the hash table buckets
    HashNode** hashTable = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));

    for (int i = 0; i < pointsSize; i++) {
        int current_max = 0;

        // Reset and clear the hash table entries from the previous anchor loop
        for (int h = 0; h < HASH_SIZE; h++) {
            HashNode* curr = hashTable[h];
            while (curr != NULL) {
                HashNode* temp = curr;
                curr = curr->next;
                free(temp);
            }
            hashTable[h] = NULL;
        }

        for (int j = i + 1; j < pointsSize; j++) {
            int dx = points[j][0] - points[i][0];
            int dy = points[j][1] - points[i][1];

            // Reduce fraction using GCD to handle slope precision perfectly
            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;

            // Standardize negative signs so (-1, 2) and (1, -2) hash identically
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
            }

            // Hash Table Lookup & Insertion
            unsigned int slot = hash_function(dx, dy);
            HashNode* curr = hashTable[slot];
            int found = 0;

            while (curr != NULL) {
                if (curr->dx == dx && curr->dy == dy) {
                    curr->count++;
                    if (curr->count > current_max) {
                        current_max = curr->count;
                    }
                    found = 1;
                    break;
                }
                curr = curr->next;
            }

            // If slope combination doesn't exist, create a new node
            if (!found) {
                HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
                newNode->dx = dx;
                newNode->dy = dy;
                newNode->count = 1;
                newNode->next = hashTable[slot];
                hashTable[slot] = newNode;

                if (1 > current_max) {
                    current_max = 1;
                }
            }
        }

        // Add 1 to include the current anchor point 'i' itself
        if (current_max + 1 > max_global) {
            max_global = current_max + 1;
        }
    }

    // Clean up allocated bucket shell memory
    for (int h = 0; h < HASH_SIZE; h++) {
        HashNode* curr = hashTable[h];
        while (curr != NULL) {
            HashNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(hashTable);

    return max_global;
}
