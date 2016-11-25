/*******************************************************************
*   binheap.h
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/

#ifndef BINHEAP_H
#define BINHEAP_H

struct typedef binheap{
    cdll *rootlist;
    int size;
    node *min;
    int(*comparator)(void *,void *);
}binheap;

binheap *newBinHeap(int (*)(void *,void *));
node *insertBinHeap(binheap *,void *);
node *decreaseKeyBinHeap(binheap *,node *,void *);
void *extractBinHeap(binheap *);

#endif // BINHEAP_H
