/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Nov. 2021-11-12
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 *      Program that implements the Dijkstras algorithm, providing the 
 *      shortest path with the lowest cost.
 *
 ******************************************************************************/

#include "roap.h"

#define swap(x, y)    \
    {                 \
        int temp = x; \
        x = y;        \
        y = temp;     \
    }

int **dijkstras(LinkedList **adjList, int *maze, int n_vertex, int inicial_vertex,int final_vertex)
{
    int *cost,*parent,u,v;
    LinkedList *list;

    cost = (int *)malloc(n_vertex * sizeof(int));
    parent = (int *)malloc(n_vertex * sizeof(int));

    MinHeap *minHeap = createMinHeap(n_vertex);
    for (int i = 0; i < n_vertex; i++)
    {
        cost[i] = INT_MAX;
        parent[i] = -1;
    }

    cost[inicial_vertex] = 0;
    PQinsert(minHeap, cost, inicial_vertex);

    while (!PQEmpty(minHeap->free))
    {
        u = PQdelmax(minHeap, cost);

        if (u == final_vertex)
        {
            free(minHeap->pos);
            free(minHeap);

            int **result;
            result = (int **)malloc(2 * sizeof(int *));
            result[0] = cost;
            result[1] = parent;
            return result;
        }

        for (list = adjList[u]; list != NULL; list = list->next)
        {
            v = list->Vertex;

            if (cost[v] != INT_MAX && less(maze[list->Wall] + cost[u], cost[v]))
            {
                parent[v] = u;
                cost[v] = cost[u] + maze[list->Wall];
                PQdec(minHeap, maze, cost, v);
            }
            else if (cost[v] == INT_MAX)
            {
                parent[v] = u;
                cost[v] = cost[u] + maze[list->Wall];
                PQinsert(minHeap, cost, v);
            }
        }
    }
    free(minHeap->pos);
    free(minHeap);

    int **result;
    result = (int **)malloc(2 * sizeof(int *));
    result[0] = cost;
    result[1] = parent;
    return result;
}

/******************************************************************************
 * createMinHeap()
 *
 * Arguments: capacity
 * Returns: minHeap
 *
 * Description: This function creates the Heap.
 * 
 *****************************************************************************/
MinHeap *createMinHeap(unsigned capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));

    minHeap->size = capacity;
    minHeap->free = 0;
    return minHeap;
}

/******************************************************************************
 * PQinsert()
 *
 * Arguments: minHeap, cost, v
 * Returns: head->next
 *
 * Description: Insertion of Heap in V position.
 * 
 *****************************************************************************/
void PQinsert(MinHeap *minHeap, int *cost, int v)
{
    // elemento inserido sempre na primeira posição livre
    if (less(minHeap->free + 1, minHeap->size))
    {
        minHeap->pos[minHeap->free] = v;
        FixUp(minHeap, cost, minHeap->free);
        minHeap->free += 1;
    }
}

/******************************************************************************
 * FixUp()
 *
 * Arguments: minHeap, cost, Idx
 * Returns: -
 *
 * Description: If a node's priority is increased, while it is not
 * reestablished the heap condition or reached the root, 
 * change with the ascendant's node.
 * 
 *****************************************************************************/
void FixUp(MinHeap *minHeap, int *cost, int Idx)
{
    while (Idx > 0 && less(cost[minHeap->pos[Idx]], cost[minHeap->pos[(Idx - 1) / 2]]))
    {
        swap(minHeap->pos[Idx], minHeap->pos[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
}

/******************************************************************************
 * FixDown()
 *
 * Arguments: minHeap, cost, Idx, V
 * Returns: -
 *
 * Description: If a node's priority is lowered, while not re-establishing the
 * heap condition or reaching a leaf, swap with the highest descendant.
 * 
 *****************************************************************************/
void FixDown(MinHeap *minHeap, int *cost, int Idx, int V)
{
    int Child;
    while (less(2 * Idx, V - 1))
    {
        Child = 2 * Idx + 1;
        if (less(Child, V - 1) && less(cost[minHeap->pos[Child + 1]], cost[minHeap->pos[Child]]))
            Child++;
        if (less(cost[minHeap->pos[Idx]], cost[minHeap->pos[Child]]))
            break;
        swap(minHeap->pos[Idx], minHeap->pos[Child]);
        Idx = Child;
    }
}

/******************************************************************************
 * PQEmpty()
 *
 * Arguments: free
 * Returns: 1 or 0
 *
 * Description: If free is set to 0 this function returns 1, and vice-versa.
 * 
 *****************************************************************************/
bool PQEmpty(int free)
{
    return free == 0 ? true : false;
}

/******************************************************************************
 * PQdelmax()
 *
 * Arguments: minHeap, cost
 * Returns: minHeap->pos[--minHeap->free]
 *
 * Description: Swap largest element with last in table and reorder 
 * with FixDown.
 * 
 *****************************************************************************/
int PQdelmax(MinHeap *minHeap, int *cost)
{
    swap(minHeap->pos[0], minHeap->pos[minHeap->free - 1]);
    FixDown(minHeap, cost, 0, minHeap->free - 1);
    return minHeap->pos[--minHeap->free];
}

void PQdec(MinHeap *minHeap, int *maze, int *cost, int wall)
{
    for (int j = 0; j < minHeap->free; j++)
    {
        if (minHeap->pos[j] == wall)
        {
            FixUp(minHeap, cost, j);
            return;
        }
    }
}

bool less(int x, int y)
{
    return x < y ? true : false;
}