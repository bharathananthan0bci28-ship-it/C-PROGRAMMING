#include <stdio.h>

int main() {
    char num[1005];
    int frequency[10] = {0};

    // Read the input string
    scanf("%s", num);

    // Count the occurrences of each digit
    for (int i = 0; num[i] != '\0'; i++) {
        if (num[i] >= '0' && num[i] <= '9') {
            frequency[num[i] - '0']++;
        }
    }

    // Print the frequencies separated by a space
    for (int i = 0; i < 10; i++) {
        printf("%d ", frequency[i]);
    }
    printf("\n");

    return 0;
}
