#include "roap.h"

#define swap(x, y)    \
    {                 \
        int temp = x; \
        x = y;        \
        y = temp;     \
    }

int **dijkstras(LinkedList **adjList, int *maze, int n_vertex, int final_vertex)
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

    cost[0] = 0;
    //parent[0] = 0;
    PQinsert(minHeap, cost, 0);

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
            v = list->Vertix;

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

MinHeap *createMinHeap(unsigned capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));

    minHeap->size = capacity;
    minHeap->free = 0;
    return minHeap;
}

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

void FixUp(MinHeap *minHeap, int *cost, int Idx)
{
    while (Idx > 0 && less(cost[minHeap->pos[Idx]], cost[minHeap->pos[(Idx - 1) / 2]]))
    {
        swap(minHeap->pos[Idx], minHeap->pos[(Idx - 1) / 2]);
        Idx = (Idx - 1) / 2;
    }
}

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

bool PQEmpty(int free)
{
    return free == 0 ? true : false;
}

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