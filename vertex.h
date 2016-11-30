/*******************************************************************
*   vertex.h
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#ifndef VERTEX_H
#define VERTEX_H
#include "cdll.h"

typedef struct vertex{
    int key;
    int num;
    struct vertex *predecessor;
    struct node *owner;
}vertex;

vertex *newVertex(vertex *v,int num);
void displayVertex(vertex *v,int weight);
void informer(void *a,void *b);
int comparator(void *a, void *b);
int numComparator(void *a, void *b);

#endif // VERTEX
