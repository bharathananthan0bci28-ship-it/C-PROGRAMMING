#include <stdio.h>

void calculate_the_maximum(int n, int k) {
    int max_and = 0;
    int max_or = 0;
    int max_xor = 0;

    // Iterate through all possible pairs (a, b) where 1 <= a < b <= n
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int current_and = i & j;
            int current_or = i | j;
            int current_xor = i ^ j;

            // Check and update maximums if the result is strictly less than k
            if (current_and < k && current_and > max_and) {
                max_and = current_and;
            }
            if (current_or < k && current_or > max_or) {
                max_or = current_or;
            }
            if (current_xor < k && current_xor > max_xor) {
                max_xor = current_xor;
            }
        }
    }

    // Print the maximum values on separate lines
    printf("%d\n%d\n%d\n", max_and, max_or, max_xor);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
    return 0;
}
