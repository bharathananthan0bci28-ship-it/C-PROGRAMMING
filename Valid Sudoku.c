#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    // Array registers to track seen numbers using bits (indices 0-8 represent rows/cols/boxes)
    int rows[9] = {0};
    int cols[9] = {0};
    int boxes[9] = {0};
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char val = board[i][j];
            
            // Skip empty cell positions
            if (val == '.') {
                continue;
            }
            
            // Convert character digit '1'-'9' to a 0-indexed integer 0-8
            int num = val - '1';
            int mask = 1 << num;
            
            // Calculate unique sub-box ID (0 to 8) from row and column indices
            int box_idx = (i / 3) * 3 + (j / 3);
            
            // If the bit at position 'num' is already set in any tracker, it's an invalid duplicate
            if ((rows[i] & mask) || (cols[j] & mask) || (boxes[box_idx] & mask)) {
                return false;
            }
            
            // Record the current number in our tracking bitmasks
            rows[i] |= mask;
            cols[j] |= mask;
            boxes[box_idx] |= mask;
        }
    }
    
    return true;
}
