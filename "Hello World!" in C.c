#include <stdio.h>

int main() {
    // Array to store the input string
    char s[100];
    
    // Read the input string until a newline is hit
    scanf("%[^\n]%*c", s);
    
    // Print the required text and the input string
    printf("Hello, World!\n");
    printf("%s\n", s);
    
    return 0;
}
