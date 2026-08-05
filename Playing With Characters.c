#include <stdio.h>

#define MAX_LEN 100

int main() {
    char ch;
    char s[MAX_LEN];
    char sen[MAX_LEN];

    // 1. Read a single character
    scanf("%c", &ch);

    // 2. Read a string (stops at the first space)
    scanf("%s", s);

    // 3. Clear the newline character from the buffer
    scanf("\n");

    // 4. Read the entire sentence until a newline is encountered
    scanf("%[^\n]%*c", sen);

    // Print the results on separate lines
    printf("%c\n", ch);
    printf("%s\n", s);
    printf("%s\n", sen);

    return 0;
}
