#include <stdio.h>

int uniquePaths(int m, int n) {
    // To minimize the number of iterations, choose the smaller step count
    int N = m + n - 2;
    int K = (m < n) ? m - 1 : n - 1;
    
    long long res = 1;
    
    // Calculate combination C(N, K) = N! / (K! * (N - K)!)
    // We compute this iteratively to prevent integer overflow
    for (int i = 1; i <= K; i++) {
        res = res * (N - K + i) / i;
    }
    
    return (int)res;
}
