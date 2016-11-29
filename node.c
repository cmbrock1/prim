#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "node.h"
#include "Fatal.h"
#include "vertex.h"
void initNode(node *n,void *val){
    n->next = NULL;
    n->prev = NULL;
    n->parent = NULL;
    n->children = NULL;
    n->value = val;
}
node *newNode(node *n,void *value){
    if ((n = (node *)malloc(sizeof(node))) == 0)
        Fatal("out of memory\n");
    initNode(n,value);
    return n;
}
void displayNode(node *n){
    vertex *val = (vertex *)n->value;
    displayVertex(val);
}
