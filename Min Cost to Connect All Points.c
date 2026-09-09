#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Helper function to calculate Manhattan distance
int getManhattanDistance(int* p1, int* p2) {
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize <= 1) return 0;

    // min_dist[i] stores the minimum cost to connect point i to the MST
    int* min_dist = (int*)malloc(pointsSize * sizeof(int));
    // visited[i] tracks whether point i is already part of our MST
    int* visited = (int*)calloc(pointsSize, sizeof(int));

    // Initialize all distances to Infinity
    for (int i = 0; i < pointsSize; i++) {
        min_dist[i] = INT_MAX;
    }

    // Start with the first point (index 0)
    min_dist[0] = 0;
    int total_cost = 0;

    for (int step = 0; step < pointsSize; step++) {
        int curr_node = -1;
        int min_val = INT_MAX;

        // Find the unvisited node with the smallest edge distance to the current MST
        for (int i = 0; i < pointsSize; i++) {
            if (!visited[i] && min_dist[i] < min_val) {
                min_val = min_dist[i];
                curr_node = i;
            }
        }

        // Add the minimum edge weight to the running total cost
        visited[curr_node] = 1;
        total_cost += min_val;

        // Update distances from the newly added node to all remaining unvisited nodes
        for (int next_node = 0; next_node < pointsSize; next_node++) {
            if (!visited[next_node]) {
                int dist = getManhattanDistance(points[curr_node], points[next_node]);
                if (dist < min_dist[next_node]) {
                    min_dist[next_node] = dist;
                }
            }
        }
    }

    // Clean up allocated memory
    free(min_dist);
    free(visited);

    return total_cost;
}
