#include "node.h"
#include "cdll.h"
typedef struct vertex{
    int key;
    int num;
    struct vertex *predecessor;
    node *owner;
}vertex;
vertex *newVertex(vertex *v,int num);
void displayVertex(vertex *v);
void informer(void *a,void *b);
int comparator(void *a, void *b);
