#include <stdio.h>

int main() {
    int a, b;
    scanf("%d\n%d", &a, &b);

    const char *digits[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (int n = a; n <= b; n++) {
        if (n >= 1 && n <= 9) {
            printf("%s\n", digits[n - 1]);
        } else if (n % 2 == 0) {
            printf("even\n");
        } else {
            printf("odd\n");
        }
    }

    return 0;
}
