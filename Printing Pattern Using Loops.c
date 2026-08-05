#include <stdio.h>

int main() {
    int n;
    // Read the input value n
    if (scanf("%d", &n) != 1) return 1;

    int size = 2 * n - 1;

    // Loop through each row and column of the grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Find the minimum distance to any of the four edges
            int top = i;
            int left = j;
            int bottom = size - 1 - i;
            int right = size - 1 - j;

            int min = top;
            if (left < min) min = left;
            if (bottom < min) min = bottom;
            if (right < min) min = right;

            // The value at this position is n minus the minimum distance
            printf("%d ", n - min);
        }
        printf("\n");
    }

    return 0;
}
