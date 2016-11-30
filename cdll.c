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
#include <stdio.h>
#include "node.h"
#include "cdll.h"
#include "Fatal.h"
void initCdll(cdll *ll){
    ll->head = NULL;
    ll->size = 0;
}
cdll *newCdll(cdll *ll){
    if ((ll = (cdll *)malloc(sizeof(cdll))) == 0)
        Fatal("out of memory\n");
    initCdll(ll);
    return ll;
}
bool EmptyCdll(cdll *ll){
    if(ll->head == NULL)
        return true;
    else
        return false;
}
void unionCdll(cdll *A, cdll *B)
{
    if(B->size == 0)
        return;
    if(A->size == 0)
        A->head = B->head;
    else{
        node *temp = B->head->prev;
        B->head->prev->next = A->head;
        B->head->prev = A->head->prev;
        A->head->prev->next = B->head;
        A->head->prev = temp;
    }
    A->head->prev->next = B->head;
    B->head->prev = A->head->prev;
    A->head->prev = B->head->prev;
    A->size = A->size + B->size;
    B->head = 0;
    B->size = 0;
    return;
}
void insertCdll(cdll *ll,node *n){
    if(ll->head == NULL){
        n->prev = n;
        n->next = n;
        ll->head = n;
    }
    else{
        n->next = ll->head;
        n->prev = ll->head->prev;
        ll->head->prev->next = n;
        ll->head->prev = n;
        ll->head = n;
    }
    ll->size++;
}
void deleteCdll(cdll *ll,node *n){
	if(ll->head == NULL || n == NULL){
		fprintf(stderr,"deleting from empty CDLL\n");
		return;
	}
    if(ll->head == n && ll->head->prev == n){
        ll->head = NULL;
        ll->size = 0;
    }
    else{
    	n->prev->next = n->next;
    	n->next->prev = n->prev;
        if(ll->head == n)
            ll->head = ll->head->next;
        ll->size--;
    }
}
void displayCdll(cdll *ll){
    node *temp = ll->head;
    if(temp == NULL) return;
    do {
        displayNode(temp);
        printf(" ");
        temp = temp->next;
    }while(temp != ll->head);
    printf("\n");
}
