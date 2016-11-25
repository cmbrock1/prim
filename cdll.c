/*******************************************************************
*   cdll.c
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "node.h"
#include "cdll.h"
#include "Fatal.h"
void initCdll(cdll *ll){
    ll->head = ll->tail = NULL;
    ll->size = 0;
}
cdll *newCdll(cdll *ll){
    if ((ll = (cdll *)malloc(sizeof(cdll))) == 0)
        Fatal("out of memory\n");
    initCdll(ll);
    return ll;
}
bool EmptyCdll(cdll *ll){
    if(ll->head == NULL && ll->tail == NULL)
        return true;
    else
        return false;
}
void unionCdll(cdll *A, cdll *B)
{
    A->tail->next = B->head;
    B->head->prev = A->tail;
    A->tail = B->tail
    A->size = A->size + B->size;
    B->head = 0;
    B->tail = 0;
    B->size = 0;
    return;
}
void pushCdll(cdll *ll,node *n){
    node *temp;
    if(EmptyCdll(ll)){
        ll->head = ll->tail = n;
        ll->head->prev = ll->tail;
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->tail->next = ll->head;
    }
    else{
        ll->head->prev = n;
        n->next = ll->head;
        n->prev = ll->tail;
        ll->tail->next = n;
        ll->head = n;
    }
    ll->size++;
}
void deleteCdll(cdll *ll,node *n){
    if(ll->head == n){
        ll->head = NULL;
        ll->head->prev = NULL;
        ll->head->next = NULL;
    }
    else{
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    ll->size--;
}
