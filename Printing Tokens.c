#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *s;
    s = malloc(1024 * sizeof(char));
    
    // Read the complete sentence including spaces
    if (scanf("%[^\n]", s) == 1) {
        // Tokenize the string using space as a delimiter
        char *token = strtok(s, " ");
        
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, " ");
        }
    }
    
    free(s);
    return 0;
}
