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
#include "queue.h"
#include "Fatal.h"

int getLargestVertexNum(FILE *fp);
void addToGraph(graph *g,int firstNum,int secondNum,int weight);
void processCorpus(graph *g,FILE *fp);
void printTree(vertex *v,graph *g);
void printSpanningForest(graph *g);
void prim(graph *g);

int main(int argc,char **argv){
    //int i,j;
    if(argc != 2)
        Fatal("Too few arguments");
    FILE *corpus = fopen(argv[1], "r");
    if(corpus == NULL)
        Fatal("Failed to open %s",argv[1]);
    int largestVertexNum = getLargestVertexNum(corpus);
    if(fclose(corpus) != 0)
        Fatal("Failed to close %s",argv[1]);
    corpus = fopen(argv[1], "r");
    if(corpus == NULL)
        Fatal("Failed to open %s",argv[1]);
    graph *g = newGraph(largestVertexNum);
    processCorpus(g,corpus);
    prim(g);
    printSpanningForest(g);
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
    if(token == NULL) Fatal("Corpus is empty");
    firstNum = atoi(token);
    token = readToken(fp);
    if(token == NULL) Fatal("Invalid Input");
    secondNum = atoi(token);
    token = readToken(fp);
    if(token == NULL) Fatal("Invalid Input");
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
        if(token == NULL) Fatal("Invalid Input");
        firstNum = atoi(token);
        token = readToken(fp);
        if(token == NULL) Fatal("Invalid Input");
        secondNum = atoi(token);
        token = readToken(fp);
        if(token == NULL) Fatal("Invalid Input");
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
void prim(graph *g){
    binheap *b = newBinHeap(comparator,informer);
    int i = 0;
    vertex *u;
    while(i < (g->largestVertexNum+1)){
        if(g->vertArray[i] != NULL) break;
        i++;
    }
    g->vertArray[i]->key = 0;
    for(i = 0;i < (g->largestVertexNum+1);i++){
        if(g->vertArray[i] != NULL)
            g->vertArray[i]->owner = insertBinHeap(b,g->vertArray[i]);
    }
    while(b->size != 0){
    	if(b->min == NULL && b->size != 0)
    	                    	   Fatal("PrimERROR");
        u = (vertex *)extractBinHeap(b);
        if(b->min == NULL && b->size != 0)
                    	   Fatal("PrimERROR");
        for(i=0;i<(g->largestVertexNum+1);i++){
            if(g->vertArray[i] != NULL && g->vertArray[i]->owner != NULL &&
               g->adjMatrix[u->num][i] < g->vertArray[i]->key){
               g->vertArray[i]->predecessor = u;
               g->vertArray[i]->key = g->adjMatrix[u->num][i];
               decreaseKeyBinHeap(b,g->vertArray[i]->owner,g->vertArray[i]);
           }
        }
    }

}
void printSpanningForest(graph *g){
    int i;
    for(i=0;i<(g->largestVertexNum+1);i++)
        if(g->vertArray[i] != NULL && g->vertArray[i]->predecessor == NULL)
            printTree(g->vertArray[i],g);
}
void printTree(vertex *v,graph *g){
    bool newlevel = true; int i; int level = 0; int weight = 0;
    queue *q = newQueue();
    binheap *b = newBinHeap(numComparator,informer);
    vertex *temp;
    Enqueue(q,v);
    Enqueue(q,NULL);
    while(q->head != NULL){
        if(newlevel){
            while(b->size != 0){
                temp = extractBinHeap(b);
                displayVertex(temp,temp->key);
                if(b->size == 0) printf(",");
            }
            if (level > 0)
                printf(";\n");
            printf("%d :",level);
            newlevel = false;
        }
        temp = Dequeue(q);
        if(temp == NULL){
            level++;
            newlevel = true;
            if (q->head != NULL)
                Enqueue(q,NULL);
        }
        else {
		    insertBinHeap(b,temp);
		    if(temp->predecessor != NULL)
                weight += temp->key;
            for(i=0;i<(g->largestVertexNum+1);i++)
                if(g->vertArray[i] != NULL && g->vertArray[i]->predecessor == temp)
                    Enqueue(q,g->vertArray[i]);
        }
    }
    while(b->size != 0){
        temp = extractBinHeap(b);
        displayVertex(temp,temp->key);
        if(b->size == 0) printf(",");
    }
    printf(";\nweight: %d\n",weight);
}
