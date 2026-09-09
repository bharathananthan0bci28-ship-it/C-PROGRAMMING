#include <string.h>
#include <stdlib.h>

// Helper function to expand around a center and return the length of the palindrome
int expandAroundCenter(char* s, int left, int right, int len) {
    while (left >= 0 && right < len && s[left] == s[right]) {
        left--;
        right++;
    }
    // Length of the palindrome found is right - left - 1
    return right - left - 1;
}

char* longestPalindrome(char* s) {
    if (s == NULL || strlen(s) < 1) {
        char* empty = (char*)malloc(sizeof(char));
        empty[0] = '\0';
        return empty;
    }

    int len = strlen(s);
    int start = 0;
    int maxLength = 0;

    for (int i = 0; i < len; i++) {
        // Case 1: Odd-length palindromes (centered at character i)
        int len1 = expandAroundCenter(s, i, i, len);
        
        // Case 2: Even-length palindromes (centered between character i and i+1)
        int len2 = expandAroundCenter(s, i, i + 1, len);
        
        // Find the longer of the two
        int currentMax = (len1 > len2) ? len1 : len2;

        // If a new longest palindrome is found, update tracking pointers
        if (currentMax > maxLength) {
            maxLength = currentMax;
            start = i - (currentMax - 1) / 2;
        }
    }

    // Allocate memory for the result string (+1 for null terminator)
    char* result = (char*)malloc((maxLength + 1) * sizeof(char));
    strncpy(result, s + start, maxLength);
    result[maxLength] = '\0'; // Explicitly add null terminator

    return result;
}
