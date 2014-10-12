#include "sys/queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

Queue* queueCreate()
{
    Queue *q;
    q = malloc(sizeof(Queue));
    q->head = NULL;
    return q;
}

void queuePrint(Queue *q)
{
    Node *c;

    if (q->head == NULL)
    {
        printf("empty queue\n\r");
        return;
    }
    
    c = q->head;
    while (c != NULL)
    {
        printf("%d, ", c->val);
        c = c->next;
    }
    printf("\r\n");
}

void enqueue(Queue *q, int v)
{
    Node *n, *c;
    n = malloc(4);
    n->val = v;
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

int dequeue(Queue *q)
{
    Node *n;
    if (q->head == NULL)            /* empty queue */
        return NULL;
    n = q->head;

    q->head = q->head->next;
    return n->val;
}
