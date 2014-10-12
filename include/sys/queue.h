#include "debug.h"
#include <stdio.h>

typedef struct qnode_t
{
    struct qnode_t *next;
    void* v;
} qnode_t;

typedef struct queue_t
{
    int count;
    qnode_t *head;
} queue_t;

queue_t* queueCreate();

void queueDestroy(queue_t *q);
void queueClear(queue_t *q);

void queuePrint(queue_t *q);

void* dequeue(queue_t *q);
void enqueue(queue_t *q, void *v);
