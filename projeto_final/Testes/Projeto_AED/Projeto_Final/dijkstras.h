#ifndef __dijkstras__
#define __dijkstras__

typedef struct minHeap
{
    int size;    
    int free; 
    int *pos;
}MinHeap;

MinHeap* createMinHeap(unsigned capacity);
void PQinsert(MinHeap *minHeap,int * cost, int v);
void FixUp(MinHeap *minHeap, int *maze,int Idx);
void FixDown(MinHeap *minHeap, int *cost, int Idx, int V);
bool PQEmpty(int free);
int PQdelmax(MinHeap *minHeap,int * cost);
void PQdec(MinHeap *minHeap,int* maze, int *Weight, int wall);
bool less(int x, int y);



#endif    /* __dijkstras__ */