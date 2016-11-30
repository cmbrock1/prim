/*******************************************************************
*   queue.h
*   Cameron Brock
*   Programming Assignment 2 trees
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

extern queue *newQueue();
extern int EmptyQueue(queue *q);
extern int FullQueue(queue *q);
extern void Enqueue(queue *q,vertex *v);
extern vertex *Dequeue(queue *q);
extern void DestroyQueue(queue *q);
extern void printQueue(queue *q,FILE *fp);
extern int queueSize(queue *q);
#endif // QUEUE_H
