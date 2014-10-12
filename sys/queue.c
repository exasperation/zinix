#include "sys/queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

queue_t* queueCreate()
{
    queue_t *q;
    q = malloc(sizeof(queue_t));
    q->head = NULL;
    return q;
}

void queuePrint(queue_t *q)
{
    qnode_t *c;

    if (q->head == NULL)
    {
        printf("empty queue\n\r");
        return;
    }
    
    c = q->head;
    while (c != NULL)
    {
        printf("%x, ", c->v);
        c = c->next;
    }
    printf("\r\n");
}

void enqueue(queue_t *q, void* p)
{
    qnode_t *n, *c;
    n = malloc(4);
    n->v = p;
    n->next = NULL;
    
    if (q->head == NULL)
    {
        q->head = n;
        return;
    }
    c = q->head;
    while (c->next != NULL)
    {
        c = c->next;
    }
    c->next = n;
    return;
}

void* dequeue(queue_t *q)
{
    qnode_t *n;
    if (q->head == NULL)            /* empty queue */
        return NULL;
    n = q->head;

    q->head = q->head->next;
    free (n);
    return n->v;
}
