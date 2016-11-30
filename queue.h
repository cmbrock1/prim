/*******************************************************************
*   queue.h
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include "vertex.h"

typedef struct queue{
    node *head;
    node *tail;
}queue;

queue *newQueue();
int EmptyQueue(queue *q);
int FullQueue(queue *q);
void Enqueue(queue *q,vertex *v);
vertex *Dequeue(queue *q);
void DestroyQueue(queue *q);
void printQueue(queue *q,FILE *fp);

#endif // QUEUE_H
