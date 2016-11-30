/*******************************************************************
*   cdll.c
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/
#ifndef CDLL_H
#define CDLL_H
#include <stdbool.h>

typedef struct cdll{
    struct node *head;
    int size;
}cdll;

void initCdll(cdll *ll);
cdll *newCdll(cdll *ll);
bool EmptyCdll(cdll *ll);
void unionCdll(cdll *A, cdll *B);
void insertCdll(cdll *ll,struct node *n);
void deleteCdll(cdll *ll,struct node *n);
void displayCdll(cdll *ll);

#endif // CDLL_H
