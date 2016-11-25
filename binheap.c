/*******************************************************************
*   binheap.c
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#include "binheap.h"
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

function consolidate(b){
    int i; node *temp;
    //create the consolidation array D
    int dsize = log2(b->size) + 1;
    node **d = (node **)malloc(sizeof(node *) * dsize);
    for(i=0;i < dsize-1;i++)
        d[i] = NULL;
    temp = b->rootlist->head;
    do{
        temp = temp->next;
    }while(temp != b->rootlist->head);
    calculate D's size: (log (base 2) of b's size) + 1
    set a variable D to the allocation of an array of D's size
    initialize the D array to nulls
    //place all the subheaps in the D array, combining as necessary */
    while b's root list is not empty{
        set a variable spot to the head node in b's root list
        remove spot from the root list (via linked-list remove)
        update the D array with spot
    }
    //transfer the D array back to the heap, keeping track of the extreme value
    set b's extreme pointer to null
    for (i = 0; i < D's size; ++i){
        if D[i] not equal to null{
            insert D[i] into b's root list (via the linked-list's insert method)
            update b's extreme pointer if it's null or b's comparator indicates that D[i] is more extreme
        }
    }
    free the D array (if needed)
}
