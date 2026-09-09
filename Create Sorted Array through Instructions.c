#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 100005
#define MOD 1000000007

int bit[MAX_VAL];

// Add 1 to the frequency of element 'idx' in the Fenwick Tree
void update(int idx, int val) {
    while (idx < MAX_VAL) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}

// Query the total count of elements from 1 up to 'idx'
int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += bit[idx];
        idx -= idx & (-idx);
    }
    return sum;
}

int createSortedArray(int* instructions, int instructionsSize) {
    // Reset the BIT array for execution
    for (int i = 0; i < MAX_VAL; i++) {
        bit[i] = 0;
    }
    
    long long totalCost = 0;
    
    for (int i = 0; i < instructionsSize; i++) {
        int x = instructions[i];
        
        // 1. Elements strictly less than x
        int less_than = query(x - 1);
        
        // 2. Elements strictly greater than x
        // Total elements inserted so far is 'i'
        int greater_than = i - query(x);
        
        // 3. Find the minimum cost and accumulate
        int cost = (less_than < greater_than) ? less_than : greater_than;
        totalCost = (totalCost + cost) % MOD;
        
        // 4. Insert current element into the Fenwick tree
        update(x, 1);
    }
    
    return (int)totalCost;
}
