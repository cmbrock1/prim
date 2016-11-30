/*******************************************************************
*   vertex.c
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Fatal.h"
#include "vertex.h"
#include "node.h"

vertex *newVertex(vertex *v,int num){
    if ((v = (vertex *)malloc(sizeof(vertex))) == 0)
        Fatal("out of memory\n");
    v->num = num;
    v->key = INT_MAX;
    v->predecessor = NULL;
    v->owner = NULL;
    return v;
}
void displayVertex(vertex *v,int weight){
	if(v == NULL)
		Fatal("Displaying NULL Vertex");
    printf(" %d",v->num);
    if(v->predecessor != NULL){
        printf("(%d)",v->predecessor->num);
        printf("%d",weight);
    }
}
void informer(void *a,void *b){
    vertex *x = (vertex *)a;
    vertex *y = (vertex *)b;
    node *temp = x->owner;
    x->owner = y->owner;
    y->owner = temp;
}
int numComparator(void *a, void *b){
    vertex *v = (vertex *) a;
    vertex *w = (vertex *) b;
    return v->num - w->num;
}
int comparator(void *a, void *b){
    vertex *v = (vertex *) a;
    vertex *w = (vertex *) b;
    if((v->key - w->key) == 0){
        if(v->predecessor != NULL && w->predecessor != NULL &&
            (v->predecessor->num - w->predecessor->num) != 0) {
            return v->predecessor->num - w->predecessor->num;
        }
        else
            return v->num - w->num;
    }
    else
        return v->key - w->key;
}
