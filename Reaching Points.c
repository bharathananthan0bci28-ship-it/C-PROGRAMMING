#include <stdio.h>
#include <stdbool.h>

bool reachingPoints(int sx, int sy, int tx, int ty) {
    // Move backward using modulo until we match or overshoot a starting coordinate
    while (tx > sx && ty > sy) {
        if (tx > ty) {
            tx %= ty;
        } else {
            ty %= tx;
        }
    }
    
    // Case 1: tx has reached sx. ty must be reducible to sy by subtracting tx
    if (tx == sx && ty >= sy) {
        return (ty - sy) % tx == 0;
    }
    
    // Case 2: ty has reached sy. tx must be reducible to sx by subtracting ty
    if (ty == sy && tx >= sx) {
        return (tx - sx) % ty == 0;
    }
    
    // If neither baseline coordinate can be matched
    return false;
}
