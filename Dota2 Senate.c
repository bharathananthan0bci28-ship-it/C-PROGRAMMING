#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->size = capacity;
    return q;
}

void enqueue(Queue* q, int val) {
    q->data[q->rear++] = val;
}

int dequeue(Queue* q) {
    return q->data[q->front++];
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void freeQueue(Queue* q) {
    free(q->data);
    free(q);
}

char* predictPartyVictory(char* senate) {
    int n = strlen(senate);
    
    Queue* radiant = createQueue(n);
    Queue* dire = createQueue(n);
    
    for (int i = 0; i < n; i++) {
        if (senate[i] == 'R') {
            enqueue(radiant, i);
        } else {
            enqueue(dire, i);
        }
    }
    
    while (!isEmpty(radiant) && !isEmpty(dire)) {
        int r_idx = dequeue(radiant);
        int d_idx = dequeue(dire);
        
        if (r_idx < d_idx) {
            // Radiant bans Dire. Radiant senator goes to the next round.
            enqueue(radiant, r_idx + n);
        } else {
            enqueue(dire, d_idx + n);
        }
    }
    
    char* winner = isEmpty(radiant) ? "Dire" : "Radiant";
    
    freeQueue(radiant);
    freeQueue(dire);
    
    return winner;
}
