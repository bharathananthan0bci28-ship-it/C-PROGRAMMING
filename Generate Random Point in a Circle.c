#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define the Solution structure to hold object state
typedef struct {
    double radius;
    double x_center;
    double y_center;
} Solution;

// Initializes the object with radius and center coordinates
Solution* solutionCreate(double radius, double x_center, double y_center) {
    Solution* obj = (Solution*)malloc(sizeof(Solution));
    obj->radius = radius;
    obj->x_center = x_center;
    obj->y_center = y_center;
    return obj;
}

// Returns a uniform random point inside the circle [x, y]
double* solutionRandPoint(Solution* obj, int* returnSize) {
    // Generate a uniform random double between 0.0 and 1.0
    double u = (double)rand() / RAND_MAX;
    // Generate a uniform random angle between 0 and 2*PI
    double theta = ((double)rand() / RAND_MAX) * 2.0 * M_PI;
    
    // Use the square root of 'u' to maintain a uniform area distribution
    double r = obj->radius * sqrt(u);
    
    // Allocate space for the returning coordinate pair [x, y]
    double* result = (double*)malloc(2 * sizeof(double));
    result[0] = obj->x_center + r * cos(theta);
    result[1] = obj->y_center + r * sin(theta);
    
    *returnSize = 2; // LeetCode specification array length
    return result;
}

// Frees the dynamically allocated memory
void solutionFree(Solution* obj) {
    free(obj);
}
