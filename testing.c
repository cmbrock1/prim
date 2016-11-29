#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cdll.h"
#include "vertex.h"
#include "node.h"
#include "binheap.h"
#include "scanner.h"
#include "graph.h"
#include "Fatal.h"

int getLargestVertexNum(FILE *fp);
void addToGraph(graph *g,int firstNum,int secondNum,int weight);
void processCorpus(graph *g,FILE *fp);
int testCdllAndBinheap();

int main(int argc,char **argv){
    testCdllAndBinheap();
    int i,j;
    FILE *corpus = fopen(argv[1], "r");
    if(corpus == NULL)
        Fatal("Failed to open %s",argv[1]);
    int largestVertexNum = getLargestVertexNum(corpus);
    printf("largestVertexNum = %d\n",largestVertexNum);
    if(fclose(corpus) != 0)
        Fatal("Failed to close %s",argv[1]);
    corpus = fopen(argv[1], "r");
    if(corpus == NULL)
        Fatal("Failed to open %s",argv[1]);
    printf("Creating and Initializing a Graph object\n");
    graph *g = newGraph(largestVertexNum);
    printf("Processing the Corpus and adding the verticies");
    printf("and edges to the graph\n");
    processCorpus(g,corpus);
    printf("Displaying the contents of the vertArray\n");
    for(i=0;i<largestVertexNum + 1;i++){
        if(g->vertArray[i] != NULL){
            printf("g->vertArray[%d] = ",i);
            displayVertex(g->vertArray[i]);
            printf("\n");
        }
        else{
            printf("g->vertArray[%d] = ",i);
            printf("NULL\n");
        }
    }
    printf("Displaying the contents of the adjMatrix\n");
    printf("Note a value of %d denotes the lack of an edge\n",INT_MAX);
    for(i=0;i<largestVertexNum + 1;i++){
        for(j=0;j<largestVertexNum + 1;j++){
            printf("g->adjMatrix[%d][%d] = ",i,j);
            printf("%d",g->adjMatrix[i][j]);
            printf("\n");
        }
    }
    if(fclose(corpus) != 0)
        Fatal("Failed to close %s",argv[1]);
    return 0;
}
int getLargestVertexNum(FILE *fp){
    int largestVertexNum = 0;
    char *token = readToken(fp);
    if(token == NULL) Fatal("Corpus is empty");
    while(token != NULL){
        if(token[0] != ';' && atoi(token) > largestVertexNum)
            largestVertexNum = atoi(token);
        token = readToken(fp);
    }
    return largestVertexNum;
}
void addToGraph(graph *g,int firstNum,int secondNum,int weight){
    vertex *firstVertex = NULL;
    vertex *secondVertex = NULL;
    firstVertex = newVertex(firstVertex,firstNum);
    secondVertex = newVertex(secondVertex,secondNum);
    g->vertArray[firstNum] = firstVertex;
    g->vertArray[secondNum] = secondVertex;
    g->adjMatrix[firstNum][secondNum] = weight;
    g->adjMatrix[secondNum][firstNum] = weight;
}
void processCorpus(graph *g,FILE *fp){
    char *token = NULL;
    int firstNum,secondNum,weight;
    token = readToken(fp);
    firstNum = atoi(token);
    token = readToken(fp);
    secondNum = atoi(token);
    token = readToken(fp);
    if(token[0] != ';'){
        weight = atoi(token);
        token = readToken(fp);
    	token = readToken(fp);
    }
    else{
        weight = 1;
        token = readToken(fp);
    }
    if(token == NULL) addToGraph(g,firstNum,secondNum,weight);
    while(token != NULL){
        addToGraph(g,firstNum,secondNum,weight);
        token = readToken(fp);
        firstNum = atoi(token);
        token = readToken(fp);
        secondNum = atoi(token);
        token = readToken(fp);
        if(token[0] != ';'){
            weight = atoi(token);
            token = readToken(fp);
        	token = readToken(fp);
        }
        else{
            weight = 1;
            token = readToken(fp);
        }
    }
}
int testCdllAndBinheap(){
    cdll *l1 = NULL;
    vertex *v1 = NULL,*v2 = NULL,*v3 = NULL;
    node *n1 = NULL,*n2 = NULL,*n3 = NULL;
    //binheap *b = NULL;
    printf("Creating Linked List\n");
    l1 = newCdll(l1);
    printf("Creating and Initializing Nodes to 1, 2, and 3\n");
    v1 = newVertex(v1,1);
    n1 = newNode(n1,v1);
    v2 = newVertex(v2,2);
    n2 = newNode(n2,v2);
    v3 = newVertex(v3,3);
    n3 = newNode(n3,v3);
    printf("Adding the first Node to the List\n");
    insertCdll(l1,n1);
    printf("The contents of the list: \n");
    displayCdll(l1);
    printf("Adding the second Node to the List\n");
    insertCdll(l1,n2);
    printf("The contents of the list: \n");
    displayCdll(l1);
    printf("Adding the third Node to the List\n");
    insertCdll(l1,n3);
    printf("The contents of the list: \n");
    displayCdll(l1);
    printf("Deleting n2 from the list\n");
    deleteCdll(l1,n2);
    printf("The contents of the list: \n");
    displayCdll(l1);
    printf("Deleting n3 from the list\n");
    deleteCdll(l1,n3);
    printf("The contents of the list: \n");
    displayCdll(l1);
    printf("Deleting last node from the list\n");
    deleteCdll(l1,n1);
    printf("Display empty list: \n");
    displayCdll(l1);
    printf("Adding the first Node back to the List\n");
    insertCdll(l1,n1);
    printf("The contents of the list: \n");
    displayCdll(l1);

    printf("Creating Binomial Heap\n");
    binheap *b = newBinHeap(comparator,informer);
    printf("Inserting a Vertex with key = 2\n");
    insertBinHeap(b,v2);
    printf("Min of Binomial Heap is : ");
    displayNode(b->min);
    printf("\nInserting a Vertex with key = 3\n");
    insertBinHeap(b,v3);
    printf("Min of Binomial Heap is : ");
    displayNode(b->min);
    printf("\nInserting a Vertex with key = 1\n");
    insertBinHeap(b,v1);
    printf("Min of Binomial Heap is : ");
    displayNode(b->min);
    printf("\n");
    return 0;
}
