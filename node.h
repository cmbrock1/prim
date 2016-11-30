/*******************************************************************
*   node.h
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#ifndef NODE_H
#define NODE_H
#include "cdll.h"

struct cdll;
typedef struct node{
    struct node *next;
    struct node *prev;
    struct node *parent;
    cdll *children;
    void *value;
}node;

void initNode(node *n,void *val);
node *newNode(node *n,void *value);
void displayNode(node *n);

#endif // NODE_H
