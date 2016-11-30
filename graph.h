/*******************************************************************
*   graph.h
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph{
    int **adjMatrix;
    struct vertex **vertArray;
    int largestVertexNum;
}graph;
graph *newGraph(int numNodes);
#endif // GRAPH_H
