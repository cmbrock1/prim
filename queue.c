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

void initQueue(queue *q){
    q->head = q->tail = NULL;
}
void initQNode(qNode *n){
    n->data = NULL;
    n->next = NULL;
}
qNode *newQNode(vertex *data){
    qNode *n;
    if ((n = (qNode *)malloc(sizeof(qNode))) == 0)
        Fatal("out of memory\n");
    initQNode(n);
    n->data = data;
    return n;
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
int FullQueue(queue *q){
    return false;
}
void Enqueue(queue *q,node *n)
    {
    if (q->head == NULL && q->tail == NULL)
        {
        q->head = newQNode(n);
        q->tail = q->head;
        }
    else
        {
        q->tail->next = newQNode(n);
        q->tail = q->tail->next;
        }
    }

node *Dequeue(queue *q)
    {
    	if(EmptyQueue(q))
            Fatal("Dequeue Empty Queue\n");
    	node *temp = q->head->data;
    	q->head = q->head->next;
    	if (q->head == NULL)
    		q->tail = NULL;
    	return temp;
    }
