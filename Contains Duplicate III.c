#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define HASH_SIZE 10007 // Size of the hash table map

// Hash map entry structure to hold bucket information
typedef struct HashEntry {
    long long bucketId;
    long long value;
    struct HashEntry* next;
} HashEntry;

// Simple hash map implementation
typedef struct {
    HashEntry* buckets[HASH_SIZE];
} HashMap;

// Hash function handling negative bucket IDs safely
int getHash(long long bucketId) {
    int hash = bucketId % HASH_SIZE;
    if (hash < 0) hash += HASH_SIZE;
    return hash;
}

// Insert or update a bucket ID with a value
void mapPut(HashMap* map, long long bucketId, long long value) {
    int idx = getHash(bucketId);
    HashEntry* curr = map->buckets[idx];
    while (curr != NULL) {
        if (curr->bucketId == bucketId) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }
    HashEntry* newEntry = (HashEntry*)malloc(sizeof(HashEntry));
    newEntry->bucketId = bucketId;
    newEntry->value = value;
    newEntry->next = map->buckets[idx];
    map->buckets[idx] = newEntry;
}

// Search for a bucket ID and get its stored value
bool mapGet(HashMap* map, long long bucketId, long long* outputVal) {
    int idx = getHash(bucketId);
    HashEntry* curr = map->buckets[idx];
    while (curr != NULL) {
        if (curr->bucketId == bucketId) {
            *outputVal = curr->value;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Remove a bucket ID when it falls out of the sliding window
void mapRemove(HashMap* map, long long bucketId) {
    int idx = getHash(bucketId);
    HashEntry* curr = map->buckets[idx];
    HashEntry* prev = NULL;
    while (curr != NULL) {
        if (curr->bucketId == bucketId) {
            if (prev == NULL) {
                map->buckets[idx] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Free memory allocated for the hash map
void freeMap(HashMap* map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashEntry* curr = map->buckets[i];
        while (curr != NULL) {
            HashEntry* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}

// Helper to map a number to its bucket ID
long long getBucketId(long long val, long long w) {
    // If val is negative, adjust division behavior to align properly into buckets
    return val < 0 ? (val + 1) / w - 1 : val / w;
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int indexDiff, int valueDiff) {
    if (numsSize < 2 || indexDiff <= 0 || valueDiff < 0) return false;
    
    HashMap map = {0}; // Initialize buckets to NULL
    long long w = (long long)valueDiff + 1;
    
    for (int i = 0; i < numsSize; i++) {
        long long val = nums[i];
        long long bucketId = getBucketId(val, w);
        long long outVal;
        
        // Condition 1: Check if current bucket already contains an element
        if (mapGet(&map, bucketId, &outVal)) {
            freeMap(&map);
            return true;
        }
        
        // Condition 2: Check adjacent left bucket
        if (mapGet(&map, bucketId - 1, &outVal) && llabs(val - outVal) <= valueDiff) {
            freeMap(&map);
            return true;
        }
        
        // Condition 3: Check adjacent right bucket
        if (mapGet(&map, bucketId + 1, &outVal) && llabs(val - outVal) <= valueDiff) {
            freeMap(&map);
            return true;
        }
        
        // Put the current element into its bucket
        mapPut(&map, bucketId, val);
        
        // Maintain sliding window size <= indexDiff
        if (i >= indexDiff) {
            long long oldBucketId = getBucketId(nums[i - indexDiff], w);
            mapRemove(&map, oldBucketId);
        }
    }
    
    freeMap(&map);
    return false;
}
