#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* convert(char* s, int numRows) {
    // Edge cases: if numRows is 1 or greater than/equal to the string length,
    // the zigzag pattern is identical to the original string.
    int len = strlen(s);
    if (numRows <= 1 || numRows >= len) {
        char* duplicate = (char*)malloc((len + 1) * sizeof(char));
        strcpy(duplicate, s);
        return duplicate;
    }

    // Allocate memory for the final output string
    char* result = (char*)malloc((len + 1) * sizeof(char));
    int resultIdx = 0;

    // The full step size of one complete "V" cycle in the zigzag pattern
    int cycleLen = 2 * numRows - 2;

    // Process row by row to build the result string sequentially
    for (int r = 0; r < numRows; r++) {
        for (int i = 0; i + r < len; i += cycleLen) {
            // Append the primary character falling vertically down in the current cycle
            result[resultIdx++] = s[i + r];

            // For interior rows (not top or bottom), append the diagonal upward character
            if (r != 0 && r != numRows - 1 && i + cycleLen - r < len) {
                result[resultIdx++] = s[i + cycleLen - r];
            }
        }
    }

    // Explicitly add the null terminator at the end of the string
    result[resultIdx] = '\0';
    return result;
}
