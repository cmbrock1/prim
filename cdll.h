#ifndef CDLL_H
#define CDLL_H
#include <stdbool.h>
typedef struct cdll{
    struct node *head;
    struct node *tail;
    int size;
}cdll;
void initCdll(cdll *ll);
cdll *newCdll(cdll *ll);
bool EmptyCdll(cdll *ll);
void unionCdll(cdll *A, cdll *B);
void pushCdll(cdll *ll,struct node *n);
void deleteCdll(cdll *ll,struct node *n);
#endif // CDLL_H
