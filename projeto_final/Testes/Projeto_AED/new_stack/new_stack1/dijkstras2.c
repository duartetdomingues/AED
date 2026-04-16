#include "roap2.h"
#include "LinkedList.h"

/************************************************ Dijkstra *************************************************/
int** dijkstra(LinkedList** adjList, int* maze,int src,int V)
{
    // dist values used to pick
    // minimum weight edge in cut

    int *dist;
    dist = (int *)malloc(V*sizeof(int));  

    int *parent;
    parent = (int *)malloc(V*sizeof(int)); 
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,dist[v]);
        minHeap->pos[v] = v;
        parent[v]=-1;
    }
 
    // Make dist value of src vertex
    // as 0 so that it is extracted first
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]); 
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!is_Empty(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode* minHeapNode =extractMin(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->v;
        
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values

        struct LinkedList* pCrawl;
        pCrawl = adjList[u];

        while (pCrawl != NULL)
        {
            int v = pCrawl->Vertix;
 
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && maze[pCrawl->Weight] + dist[u] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + maze[pCrawl->Weight];
                //printf("dist[v]=%d,dist[u]=%d,weight=%d\n",dist[v], dist[u],maze[pCrawl->Weight]);
 
                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
        free(minHeapNode);
    }

    free(minHeap->pos);
    free(minHeap->array);
    free(minHeap);

    int **result;
    result = (int **)malloc(2*sizeof(int*));  
    //printf("%ls -- %ls\n\n\n\n\n", &dist[0], &parent[0]);
    result[0]= dist;
    result[1]= parent;
    
    return result;
    
}


struct MinHeap* createMinHeap(int capacity){
    struct MinHeap* minHeap =(struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(struct MinHeapNode**)malloc(capacity *sizeof(struct MinHeapNode*));
    return minHeap;
}

struct MinHeapNode* newMinHeapNode(int v,int dist)
{
    struct MinHeapNode* minHeapNode =(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

void decreaseKey(struct MinHeap* minHeap,int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =(i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
struct MinHeapNode* extractMin(struct MinHeap*minHeap)
{
    if (is_Empty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}

int is_Empty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap,int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist <
         minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist <
         minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode =minHeap->array[smallest];
        struct MinHeapNode *idxNode =minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                         &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
