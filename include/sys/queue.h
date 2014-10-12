#include "debug.h"
#include <stdio.h>

typedef struct Node
{
    struct Node *next;
    int val;
} Node;

typedef struct Queue
{
    int count;
    Node *head;
} Queue;

Queue* queueCreate();

void queueDestroy(Queue *q);
void queueClear(Queue *q);

void queuePrint(Queue *q);

int dequeue(Queue *q);
void enqueue(Queue *q, int v);
