/*******************************************************************
*   binheap.c
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "binheap.h"
#include "node.h"
#include "cdll.h"
#include "Fatal.h"

void consolidate(binheap *);
void updateConsolidationArray(binheap *, node **,node *);
node *combine(binheap *,node *,node *);
binheap *newBinHeap(int (*c)(void *,void *),void (*i)(void *,void *)){
    binheap *b = NULL;
    cdll *ll = NULL;
    if((b = (binheap *)malloc(sizeof(binheap))) == 0)
        Fatal("out of memory\n");
    b->comparator = c;
    b->informer = i;
    b->rootlist = newCdll(ll);
    b->min = NULL;
    b->size = 0;
    return b;
}
node *bubbleUp(binheap *b, node *n){
    if(n == n->parent)
        return n;
    if(b->comparator(n->value,n->parent->value) >= 0)
        return n;
    //inform the value of n that n's parent is the new owner
    //inform the value of n's parent that n is the new owner
    b->informer(n->value,n->parent->value);
    void *temp = n->value;
    n->value = n->parent->value;
    n->parent->value = temp;
    return bubbleUp(b,n->parent);
}
node *decreaseKeyBinHeap(binheap *b,node *n,void *nv){
	int i;
    n->value = nv;
    node *newNode = bubbleUp(b,n);
    node *temp = b->rootlist->head;
    for (i = 0; i < b->rootlist->size; i++){
        if((b->comparator(b->min->value,temp->value) > 0)){
            b->min = temp;
            if(b->min == NULL) Fatal("DecreaseKeyERROR");
        }
        temp = temp->next;
    }
    return newNode;
}
void unionBinheap(binheap *b,binheap *donor){
    cdll *ll = NULL;
    unionCdll(b->rootlist,donor->rootlist);
    b->size += donor->size;
    donor->rootlist = newCdll(ll);
    donor->size = 0;
    donor->min = NULL;
    consolidate(b);
}
node *insertBinHeap(binheap *b,void *val){
    cdll *ll = NULL;
    node *n = NULL;
    n = newNode(n,val);
    n->parent = n;
    n->children = newCdll(ll);
    insertCdll(b->rootlist,n);
    b->size++;
    consolidate(b);
    return n;
}
void deleteBinheap(binheap *b,node *n){
    decreaseKeyBinHeap(b,n,NULL);
    extractBinHeap(b);
}
void *extractBinHeap(binheap *b){
    int i;
	if(b->size == 0)
		Fatal("Extract from empty binheap");
	else if(b->min == NULL && b->size != 0)
		Fatal("Invalid Condition in extractBinheap");
    node *y = b->min;
    deleteCdll(b->rootlist,y);
    // the children of y are a linked list
    node *temp = y->children->head;
    for (i = 0; i < y->children->size; i++){
        temp->parent = temp;
        temp = temp->next;
    }
    unionCdll(b->rootlist,y->children);
    consolidate(b);
    b->size--;
    return y->value;
}

void consolidate(binheap *b){
    int i; node *spot;
    //create the consolidation array D
    int dsize = log2(b->size) + 1;
    node **d = (node **)malloc(sizeof(node *) * dsize);
    if (d == NULL) Fatal("out of memory\n");
    for(i=0;i < dsize;i++)
        d[i] = NULL;
    while(b->rootlist->size > 0){
        spot = b->rootlist->head;
        deleteCdll(b->rootlist,spot);
        updateConsolidationArray(b,d,spot);
    }
    b->min = NULL;
    for (i = 0; i < dsize; i++){
        if (d[i] != NULL){
            insertCdll(b->rootlist,d[i]);
            if((b->min == NULL) || (b->comparator(b->min->value,d[i]->value) > 0)){
                b->min = d[i];
            }
        }
    }
}
void updateConsolidationArray(binheap *b, node **d,node *spot){
    int degree = spot->children->size;
    while (d[degree] != NULL){
        spot = combine(b,spot,d[degree]);
        d[degree] = NULL;
        degree++;
    }
    d[degree] = spot;
}
node *combine(binheap *b,node *x,node *y){
    if (b->comparator(x->value,y->value) < 0){
        insertCdll(x->children,y);
        y->parent = x;
        return x;
    }
    else {
        insertCdll(y->children,x);
        x->parent = y;
        return y;
    }
}
