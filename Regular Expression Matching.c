#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isMatch(char* s, char* p) {
    int sLen = strlen(s);
    int pLen = strlen(p);

    // Dynamically allocate rows for the 2D DP table
    bool** dp = (bool**)malloc((sLen + 1) * sizeof(bool*));
    for (int i = 0; i <= sLen; i++) {
        dp[i] = (bool*)calloc((pLen + 1), sizeof(bool));
    }

    // Base Case: Empty string matches empty pattern
    dp[0][0] = true;

    // Handle patterns like a*, a*b*, or .* which can match an empty string s
    for (int j = 1; j <= pLen; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    // Fill the DP table
    for (int i = 1; i <= sLen; i++) {
        for (int j = 1; j <= pLen; j++) {
            // Case 1: Current characters match, or pattern contains '.'
            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } 
            // Case 2: Pattern contains '*'
            else if (p[j - 1] == '*') {
                // Subcase A: Count '*' as zero occurrences of the preceding element
                dp[i][j] = dp[i][j - 2];
                
                // Subcase B: Count '*' as one or more occurrences of the preceding element
                // (only valid if preceding character matches s[i-1] or is '.')
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }

    bool result = dp[sLen][pLen];

    // Free the allocated memory
    for (int i = 0; i <= sLen; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}
