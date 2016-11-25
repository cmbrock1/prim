/*******************************************************************
*   binheap.c
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include "binheap.h"
#include "node.h"
#include "cdll.h"
#include "Fatal.h"
binheap *newBinHeap(int (*c)(void *,void *)){
    binheap *b;
    cdll *ll;
    if(b = malloc(sizeof(binheap)) == 0)
        Fatal("out of memory\n");
    b->comparator = c;
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
    void *temp = n->value;
    n->value = n->parent->value;
    n->parent->value = temp->value;
    return bubbleUp(b,n->parent);
}
node *decreaseKeyBinHeap(binheap *b,node *n,void *nv){
    n->value = nv;
    node *newNode = bubbleUp(b,n);
    //b->min = extractMin(b);
    return newNode;
}
void unionBinheap(binheap *b,binheap *donor){
    cdll *ll;
    unionCdll(b->rootlist,donor->rootlist);
    b->size += donor->size;
    donor->rootlist = newCdll(ll);
    donor->size = 0;
    donor->min = NULL;
    consolidate(b);
}
node *insertBinHeap(binheap *b,void *val){
    cdll *ll;
    node *n = newNode(val,n);
    n->parent = n;
    n->children = newCdll(ll);
    insertCdll(b->rootlist,n);
    b->size++;
    consolidate(b);
    return n;
}
void deleteBinheap(binheap *b,node *n){
    decreaseKeyBinHeap(b,n,NULL);
    extractMinBinHeap(b);
}
void *extractMin(b){
    node *y = min->b;
    deleteCdll(b,y);
    // the children of y are a linked list
    node *temp = y->children->head;
    do {
        temp->parent = temp;
        temp = temp->next;
    }while(temp1 != y->children->head);
    unionCdll(b->rootlist,y->children);
    consolidate(b);
    b->size--;
    return y->value;
}

void consolidate(binheap *b){
    int i; node *temp; node *spot;
    //create the consolidation array D
    int dsize = log2(b->size) + 1;
    node **d = (node **)malloc(sizeof(node *) * dsize);
    if (d == NULL) Fatal("out of memory\n");
    for(i=0;i < dsize;i++)
        d[i] = NULL;
    temp = b->rootlist->head;
    do{
        spot = b->rootlist->head;
        deleteCdll(b->rootlist,spot);
        updateConsolidationArray(b,d,spot);
        temp = temp->next;
    }while(temp != b->rootlist->head);
    b->min = NULL;
    for (i = 0; i < dsize; i++){
        if (d[i] != NULL){
            insertCdll(b->rootlist,d[i]);
            if(b->min == NULL || (b->comparator(b->min->value,d[i]->value) > 0));
                b->min = d[i];
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
    if (b->comparator(x,y) < 0){
        insertCdll(x->children,y);
        y->parent = x;
        return x
    }
    else {
        insertCdll(x,y->children);
        x->parent = y;
        return y
    }
}
