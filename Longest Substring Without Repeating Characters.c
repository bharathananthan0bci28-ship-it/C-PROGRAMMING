#include <string.h>

int lengthOfLongestSubstring(char* s) {
    // Array to store the last seen position of all ASCII characters
    // Initialized to -1 to represent that the character hasn't been seen yet
    int lastSeen[128];
    memset(lastSeen, -1, sizeof(lastSeen));
    
    int maxLength = 0;
    int left = 0;
    int len = strlen(s);
    
    for (int right = 0; right < len; right++) {
        unsigned char currentChar = s[right];
        
        // If the character was seen inside the current sliding window boundary,
        // move the left boundary to the right of its previous occurrence
        if (lastSeen[currentChar] >= left) {
            left = lastSeen[currentChar] + 1;
        }
        
        // Record the latest index of this character
        lastSeen[currentChar] = right;
        
        // Update max length of the substring found so far
        int currentWindowLength = right - left + 1;
        if (currentWindowLength > maxLength) {
            maxLength = currentWindowLength;
        }
    }
    
    return maxLength;
}
