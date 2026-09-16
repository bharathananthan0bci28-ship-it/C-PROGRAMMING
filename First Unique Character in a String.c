int firstUniqChar(char* s) {
    // Array to store the frequency of each lowercase English letter
    int count[26] = {0};
    
    // First pass: count the frequency of each character
    for (int i = 0; s[i] != '\0'; i++) {
        count[s[i] - 'a']++;
    }
    
    // Second pass: find the first character with a frequency of 1
    for (int i = 0; s[i] != '\0'; i++) {
        if (count[s[i] - 'a'] == 1) {
            return i; // Return the 0-indexed position
        }
    }
    
    // Return -1 if no unique character exists
    return -1;
}
