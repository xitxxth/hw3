#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////
#define MAX_VERTICES 10000 // 10000 vertices
#define MAX_EDGES 50000000 // 50000000 edges
typedef struct {
    int from;
    int to;
    int cost;
}Edge;
typedef Edge* edgePointer;
typedef struct Node{
    int vertex;
    struct Node* link;
}Node;
typedef struct Node* nodePointer;
edgePointer minHeap[MAX_EDGES];
nodePointer graph[MAX_VERTICES];
int numVer;
int numEdz;
int minHeapSize=1;
int visited[MAX_VERTICES];
int parent[MAX_VERTICES];


void heapInsert(edgePointer newNode)
{
    minHeap[minHeapSize++] = newNode;
    int iter = minHeapSize-1;
    while(iter > 1){
        if(newNode->cost < minHeap[iter/2]->cost){
            minHeap[iter] = minHeap[iter/2];
            iter /= 2;
        }
        else    break;
    }
    minHeap[iter] = newNode;
};

edgePointer heapDel(void)
{
    int parent=1, child=2;
    edgePointer target = minHeap[1];
    edgePointer tmp = minHeap[--minHeapSize];
    while(child < minHeapSize){
        if((child < minHeapSize) && (minHeap[child]->cost > minHeap[child+1]->cost))    child++;
        if(tmp->cost <= minHeap[child]->cost)  break;
        minHeap[parent] = minHeap[child];
        parent = child;
        child *= 2;
    }
    minHeap[parent] = tmp;
    return target;
};