#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize, int k) {
    // Deque stores the indices of candidate points 'i'
    int* deque = (int*)malloc(pointsSize * sizeof(int));
    int head = 0, tail = 0;
    
    int max_val = INT_MIN;

    for (int j = 0; j < pointsSize; j++) {
        int xj = points[j][0];
        int yj = points[j][1];

        // 1. Remove points from the front that are outside the window constraint (xj - xi > k)
        while (head < tail && xj - points[deque[head]][0] > k) {
            head++;
        }

        // 2. If the deque is not empty, the front element maximizes (yi - xi)
        if (head < tail) {
            int i = deque[head];
            int current_value = (points[i][1] - points[i][0]) + (yj + xj);
            max_val = MAX(max_val, current_value);
        }

        // 3. Maintain the monotonic property (decreasing order of y_i - x_i)
        // Remove indices from the back whose (yi - xi) value is <= the current point's value
        int current_diff = yj - xj;
        while (head < tail) {
            int last_idx = deque[tail - 1];
            int last_diff = points[last_idx][1] - points[last_idx][0];
            if (last_diff <= current_diff) {
                tail--;
            } else {
                break;
            }
        }

        // 4. Push the current index onto the deque
        deque[tail++] = j;
    }

    free(deque);
    return max_val;
}
