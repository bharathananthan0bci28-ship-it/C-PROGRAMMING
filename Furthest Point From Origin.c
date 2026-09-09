#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int furthestDistanceFromOrigin(char* moves) {
    int count_L = 0;
    int count_R = 0;
    int count_underscore = 0;
    
    // Single pass to count all move characters
    for (int i = 0; moves[i] != '\0'; i++) {
        if (moves[i] == 'L') {
            count_L++;
        } else if (moves[i] == 'R') {
            count_R++;
        } else if (moves[i] == '_') {
            count_underscore++;
        }
    }
    
    // Calculate maximum absolute distance by adding wildcards to the dominant direction
    return abs(count_R - count_L) + count_underscore;
}
