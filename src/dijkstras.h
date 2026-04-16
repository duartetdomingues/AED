/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Nov. 2021-11-12
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 *      Function declarations for roap problems.
 *
 ******************************************************************************/
#ifndef __dijkstras__
#define __dijkstras__

/******************************************************************************
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *      1) Integer to store size of Heap.
 *      2) Integer to tell whether Heap is free or not.
 *      3) Integer with its position.
 * 
 *****************************************************************************/

typedef struct minHeap
{
    int size;    
    int free; 
    int *pos;
}MinHeap;

MinHeap* createMinHeap(unsigned capacity);
int** dijkstras(LinkedList **adjList, int *maze, int n_vertex, int inicial_vertex, int final_vertex);
void PQinsert(MinHeap *minHeap,int * cost, int v);
void FixUp(MinHeap *minHeap, int *maze,int Idx);
void FixDown(MinHeap *minHeap, int *cost, int Idx, int V);
bool PQEmpty(int free);
int PQdelmax(MinHeap *minHeap,int * cost);
void PQdec(MinHeap *minHeap,int* maze, int *Weight, int wall);
bool less(int x, int y);

#endif    /* __dijkstras__ */