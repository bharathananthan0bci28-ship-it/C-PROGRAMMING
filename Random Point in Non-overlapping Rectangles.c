#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** rects;
    int rectsSize;
    int* prefix_sums;
    int total_points;
} Solution;

Solution* solutionCreate(int** rects, int rectsSize, int* rectsColSize) {
    Solution* obj = (Solution*)malloc(sizeof(Solution));
    obj->rects = rects;
    obj->rectsSize = rectsSize;
    obj->prefix_sums = (int*)malloc(rectsSize * sizeof(int));
    
    int current_sum = 0;
    for (int i = 0; i < rectsSize; i++) {
        long long width = (long long)rects[i][2] - rects[i][0] + 1;
        long long height = (long long)rects[i][3] - rects[i][1] + 1;
        current_sum += (int)(width * height);
        obj->prefix_sums[i] = current_sum;
    }
    obj->total_points = current_sum;
    return obj;
}

int* solutionPick(Solution* obj, int* retSize) {
    *retSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    // Pick a random point index from [0, total_points - 1]
    int target = rand() % obj->total_points;
    
    // Binary search to find the correct rectangle
    int low = 0, high = obj->rectsSize - 1;
    int idx = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (obj->prefix_sums[mid] > target) {
            idx = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    int* r = obj->rects[idx];
    
    // Map the random value back to 2D coordinates within the chosen rectangle
    int width = r[2] - r[0] + 1;
    int height = r[3] - r[1] + 1;
    
    result[0] = r[0] + (rand() % width);
    result[1] = r[1] + (rand() % height);
    
    return result;
}

void solutionFree(Solution* obj) {
    if (obj) {
        free(obj->prefix_sums);
        free(obj);
    }
}
