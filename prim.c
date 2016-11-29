#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
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

int main(int argc,char **argv){
    int i,j;
    FILE *corpus = fopen(argv[1], "r");
    if(corpus == NULL)
        Fatal("Failed to open %s",argv[1]);
    int largestVertexNum = getLargestVertexNum(corpus);
    if(fclose(corpus) != 0)
        Fatal("Failed to close %s",argv[1]);
    //printf("largestVertexNum = %d\n",largestVertexNum);
    corpus = fopen(argv[1], "r");
    if(corpus == NULL)
        Fatal("Failed to open %s",argv[1]);
    graph *g = newGraph(largestVertexNum);
    processCorpus(g,corpus);
    for(i=0;i<largestVertexNum + 1;i++){
        printf("g->vertArray[%d] = ",i);
        if(g->vertArray[i] != NULL)
            displayVertex(g->vertArray[i]);
        else
            printf("NULL");
       printf("\n");
    }
    for(i=0;i<largestVertexNum + 1;i++){
        for(j=0;j<largestVertexNum + 1;j++){
        //if(g->adjMatrix[i][j] != NULL){
            printf("g->adjMatrix[%d][%d] = ",i,j);
            printf("%d",g->adjMatrix[i][j]);
            printf("\n");
        //}
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
