/*
1. cost_min_heap
2. put a min_value and consist graph
3. loop it
*/
#include "hw3.h"
int simpleFind(int i) {
    for( ; parent[i] >= 0; i = parent[i])
        ;
    return i;
}

void weightedUnion(int i, int j) {
    int temp = parent[i] + parent[j];
    if(parent[i] > parent[j]) {
        parent[i] = j;
        parent[j] = temp;
    } else {
        parent[j] = i;
        parent[i] = temp;
    }
}
int main(int argc, char* argv[])
{
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &numVer);
    fscanf(input, "%d", &numEdz);
    for(int i=0; i<numVer; i++) graph[i]=NULL;
    for(int i=0; i<numEdz; i++){
        //insert_min_heap
        edgePointer newEdge = (edgePointer)malloc(sizeof(Edge));
        fscanf(input, "%d %d %d", &newEdge->from, &newEdge->to, &newEdge->cost);
        heapInsert(newEdge);
        //serve a ptr, compare cost
    }
    for(int i=0; i<numVer; i++) parent[i]=-1;
    for(int i=0; i<numEdz; i++){
        edgePointer deleted = heapDel();
        printf("%d ", deleted->cost);
        if(simpleFind(deleted->from)==simpleFind(deleted->to) && simpleFind(deleted->from)!=-1) continue;
        else    weightedUnion(simpleFind(deleted->from), simpleFind(deleted->to));
        nodePointer prev=NULL;
        nodePointer ptr = graph[deleted->from];
        if(ptr){
        for(; ptr; ptr=ptr->link){
            prev=ptr;
            if(ptr->vertex==deleted->to) break;
        }
        if(!ptr){
            ptr = (nodePointer)malloc(sizeof(Node));
            ptr->vertex = deleted->to;
            prev->link = ptr;
            ptr->link = NULL;
        }
        }
        else{
            ptr = (nodePointer)malloc(sizeof(Node));
            ptr->vertex = deleted->to;
            ptr->link = NULL;
            graph[deleted->from] = ptr;
        }
        ptr = graph[deleted->to];
        if(ptr){
        for(; ptr; ptr=ptr->link){
            prev=ptr;
            if(ptr->vertex==deleted->from) break;
        }
        if(!ptr){
            ptr = (nodePointer)malloc(sizeof(Node));
            ptr->vertex = deleted->from;
            prev->link=ptr;
            ptr->link = NULL;
        }
        }
        else{
            ptr = (nodePointer)malloc(sizeof(Node));
            ptr->vertex = deleted->from;
            ptr->link = NULL;
            graph[deleted->to] = ptr;
        }
        }
    printf("\n");
    for(int i=0; i<numVer; i++){
        nodePointer ptr = graph[i];
        printf("%d: ", i);
        for(; ptr; ptr=ptr->link){
            printf("%d ", ptr->vertex);
        }
        printf("\n");
    }
    for(int i=0; i<numVer; i++) printf("%d ", visited[i]);
    /*edgePointer j = heapDel();
    printf("del: %d\n", j->cost);
    for(int i=1; i<minHeapSize; i++){
        printf("%d %d %d\n", minHeap[i]->from, minHeap[i]->to, minHeap[i]->cost);
    }*/
    printf("\n");
    fclose(input);
    return 0;
}

    /*nodePointer ptr = graph[newNode->from];
        for(; ptr->link; ptr=ptr->link){
            if(ptr->vertex==newNode->to) break;
        }
        if(!ptr->link){
            ptr->link = (nodePointer)malloc(sizeof(Node));
            ptr->link->vertex = newNode->to;
            ptr->link->link = NULL;
        }*/