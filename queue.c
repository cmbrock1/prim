/*******************************************************************
*   queue.c
*   Cameron Brock
*   Programming Assignment 2 trees
*
*   This program is entirely my own work
*******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
#include "node.h"
#include "Fatal.h"
#include "vertex.h"

void initQueue(queue *q){
    q->head = q->tail = NULL;
}
queue *newQueue(void){
    queue *q;
    if ((q = (queue *)malloc(sizeof(queue))) == 0)
        Fatal("out of memory\n");
    initQueue(q);
    return q;
}
int EmptyQueue(queue *q){
    if(q->head == NULL && q->tail == NULL)
        return true;
    else
        return false;
}

void Enqueue(queue *q,vertex *v)
    {
    if (q->head == NULL && q->tail == NULL)
        {
        q->head = newNode(q->head,v);
        q->tail = q->head;
        }
    else
        {
        q->tail->next = newNode(q->tail->next,v);
        q->tail = q->tail->next;
        }
    }

vertex *Dequeue(queue *q)
    {
    	if(EmptyQueue(q))
            Fatal("Dequeue Empty Queue\n");
    	vertex *temp = (vertex *)q->head->value;
    	q->head = q->head->next;
    	if (q->head == NULL)
    		q->tail = NULL;
    	return temp;
    }
