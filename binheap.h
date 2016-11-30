/*******************************************************************
*   binheap.h
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#ifndef BINHEAP_H
#define BINHEAP_H
#include "cdll.h"
#include "node.h"

typedef struct binheap{
    cdll *rootlist;
    int size;
    node *min;
    int(*comparator)(void *,void *);
    void(*informer)(void *,void *);
}binheap;

binheap *newBinHeap(int (*)(void *,void *),void (*)(void *,void *));
node *insertBinHeap(binheap *,void *);
node *decreaseKeyBinHeap(binheap *,node *,void *);
void *extractBinHeap(binheap *);

#endif // BINHEAP_H
