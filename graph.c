/*******************************************************************
*   graph.c
*   Cameron Brock
*   Programming Assignment 3 prim
*
*   This program is entirely my own work
*******************************************************************/

#include <limits.h>
#include <stdlib.h>
#include "vertex.h"
#include "graph.h"
#include "Fatal.h"
int **newAdjMatrix(int largestVertexNum){
    int **arr; int i,j;
    if((arr = (int **)malloc((largestVertexNum+1) * sizeof(int *))) == 0)
        Fatal("out of memory\n");
    for (i=0; i<largestVertexNum+1; i++){
        if((arr[i] = (int *)malloc((largestVertexNum+1) * sizeof(int))) == 0)
            Fatal("out of memory\n");
    }
    for(i=0;i<largestVertexNum+1;i++){
        for(j=0;j<largestVertexNum+1;j++)
            arr[i][j] = INT_MAX;
    }
    return arr;
}
vertex **newVertexArray(int largestVertexNum){
    vertex **arr; int i;
    if((arr = malloc((largestVertexNum+1) * sizeof(vertex *))) == 0)
        Fatal("out of memory\n");
    for(i=0;i<largestVertexNum+1;i++)
        arr[i] = NULL;
    return arr;
}
graph *newGraph(int largestVertexNum){
    graph *g;
    int **adjMatrix;
    vertex **vertArray;
    if((g = (graph *)malloc(sizeof(graph))) == 0)
        Fatal("out of memory\n");
    adjMatrix = newAdjMatrix(largestVertexNum);
    vertArray = newVertexArray(largestVertexNum);
    g->largestVertexNum = largestVertexNum;
    g->adjMatrix = adjMatrix;
    g->vertArray = vertArray;
    return g;
}
