#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph{
    int **adjMatrix;
    struct vertex **vertArray;
    int largestVertexNum;
}graph;
graph *newGraph(int numNodes);
#endif // GRAPH_H
