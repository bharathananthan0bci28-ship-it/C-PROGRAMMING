#include <stdlib.h>

int boxDelivering(int** boxes, int boxesSize, int* boxesColSize, int portsCount, int maxBoxes, int maxWeight) {
    int n = boxesSize;
    
    // W[i] stores the prefix sum of weights for the first i boxes
    long long* W = (long long*)malloc((n + 1) * sizeof(long long));
    // P[i] stores the prefix sum of consecutive port changes up to the i-th box
    int* P = (int*)malloc((n + 1) * sizeof(int));
    
    W[0] = 0;
    P[0] = 0;
    for (int i = 0; i < n; ++i) {
        W[i + 1] = W[i] + boxes[i][1]; // boxes[i][1] is the weight
        P[i + 1] = P[i] + (i > 0 && boxes[i][0] != boxes[i - 1][0] ? 1 : 0); // boxes[i][0] is the port
    }
    
    // dp[i] represents the minimum trips to deliver the first i boxes
    int* dp = (int*)calloc(n + 1, sizeof(int));
    
    // Custom Deque (Monotonic Queue) array implementation
    int* dq = (int*)malloc((n + 1) * sizeof(int));
    int head = 0, tail = 0;
    dq[tail++] = 0; // Push initial candidate j = 0
    
    for (int i = 1; i <= n; ++i) {
        // 1. Pop indices from the front that violate maxBoxes or maxWeight constraints
        while (head < tail && (i - dq[head] > maxBoxes || W[i] - W[head] > maxWeight)) {
            // Note: Use W[dq[head]] to dynamically check the weight constraint
            if (W[i] - W[dq[head]] > maxWeight || i - dq[head] > maxBoxes) {
                head++;
            } else {
                break;
            }
        }
        
        // 2. The front element is our optimal index 'j'
        int j = dq[head];
        dp[i] = P[i] + 2 + dp[j] - P[j + 1];
        
        // 3. Maintain monotonic increasing order before adding current 'i'
        if (i < n) {
            while (head < tail && (dp[dq[tail - 1]] - P[dq[tail - 1] + 1] >= dp[i] - P[i + 1])) {
                tail--;
            }
            dq[tail++] = i;
        }
    }
    
    int result = dp[n];
    
    // Free allocated memory
    free(W);
    free(P);
    free(dp);
    free(dq);
    
    return result;
}
