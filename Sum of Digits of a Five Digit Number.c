#include <stdio.h>

int main() {
    int n;
    int sum = 0;

    // Read the five-digit integer from standard input
    scanf("%d", &n);

    // Loop through each digit until the number becomes 0
    while (n > 0) {
        sum += n % 10;  // Extract the last digit and add to sum
        n /= 10;        // Remove the last digit
    }

    // Print the final computed sum
    printf("%d\n", sum);

    return 0;
}
