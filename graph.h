#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph{
    int **adjMatrix;
    struct vertex **vertArray;
}graph;
graph *newGraph(int numNodes);
#endif // GRAPH_H
