#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    char *w[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    if (n >= 1 && n <= 9) {
        printf("%s\n", w[n - 1]);
    } else {
        printf("Greater than 9\n");
    }
    return 0;
}
