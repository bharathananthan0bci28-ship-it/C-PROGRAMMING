#include <stdbool.h>

bool isPalindrome(int x) {
    // Negative numbers are not palindromes.
    // Numbers ending in 0 (except 0 itself) are also not palindromes.
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int reversedHalf = 0;
    
    // Process digits until we hit or pass the middle point of the number
    while (x > reversedHalf) {
        reversedHalf = reversedHalf * 10 + (x % 10);
        x /= 10;
    }

    // For even-length numbers, x should equal reversedHalf (e.g., 1221 -> x = 12, reversedHalf = 12)
    // For odd-length numbers, we get rid of the middle digit by doing reversedHalf / 10 (e.g., 12321 -> x = 12, reversedHalf = 123)
    return x == reversedHalf || x == reversedHalf / 10;
}
