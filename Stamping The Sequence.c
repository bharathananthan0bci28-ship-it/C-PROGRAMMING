#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Returns true if stamp matches target at index 'start', counting wildcards '?' as matches
bool checkMatch(const char* target, int start, const char* stamp, int stampLen) {
    bool hasCharMatch = false;
    for (int i = 0; i < stampLen; i++) {
        if (target[start + i] == '?') {
            continue;
        }
        if (target[start + i] != stamp[i]) {
            return false;
        }
        hasCharMatch = true; // Found at least one actual non-? matching character
    }
    return hasCharMatch;
}

// Replaces matching non-'?' characters in target with '?' and returns total replaced count
int eraseCharacters(char* target, int start, int stampLen) {
    int replacedCount = 0;
    for (int i = 0; i < stampLen; i++) {
        if (target[start + i] != '?') {
            target[start + i] = '?';
            replacedCount++;
        }
    }
    return replacedCount;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* movesToStamp(char* stamp, char* target, int* returnSize) {
    int m = strlen(stamp);
    int n = strlen(target);
    
    // Allocate space for the results array (at most 10 * n moves allowed)
    int maxMoves = 10 * n;
    int* moves = (int*)malloc(maxMoves * sizeof(int));
    int totalMoves = 0;
    
    bool* visited = (bool*)calloc(n - m + 1, sizeof(bool));
    int totalQuestions = 0;
    
    // Keep scanning and removing stamps until the target is completely converted to '?'
    while (totalQuestions < n) {
        bool changedInThisRound = false;
        
        for (int i = 0; i <= n - m; i++) {
            if (!visited[i] && checkMatch(target, i, stamp, m)) {
                totalQuestions += eraseCharacters(target, i, m);
                moves[totalMoves++] = i;
                visited[i] = true;
                changedInThisRound = true;
                
                if (totalQuestions == n) {
                    break;
                }
            }
        }
        
        // If a full iteration occurs without making any changes, it's impossible to solve
        if (!changedInThisRound) {
            *returnSize = 0;
            free(moves);
            free(visited);
            return NULL;
        }
    }
    
    // Reverse the move log array since we found the steps backwards
    for (int i = 0; i < totalMoves / 2; i++) {
        int temp = moves[i];
        moves[i] = moves[totalMoves - 1 - i];
        moves[totalMoves - 1 - i] = temp;
    }
    
    *returnSize = totalMoves;
    free(visited);
    return moves;
}
