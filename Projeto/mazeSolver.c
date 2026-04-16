#include "roap.h"
#include "LinkedList.h"

int maze_solver(FILE *fp_out, int *maze, int l, int c, int cells_number, int walls, int *walls_array, int a, int b)
{
    int i, rooms;

    /* Checking if the starting and end cells are white cells. If not, execution is ended */
    if (maze[conversion(a, b, l, c)] != 0 || maze[conversion(1, 1, l, c)] != 0)
    {
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }

    rooms = make_rooms(maze, l, c, cells_number, walls, walls_array);
    // se a casa de chegada ou de partida tiverem numa sala blindada a -1 (nesse caso não terão sido pintadas)
    if (maze[conversion(a, b, l, c)] == 0 || maze[conversion(1, 1, l, c)] == 0)
    {
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }
    // se a casa de partida e chegada tiverem na mesma sala
    if (maze[conversion(a, b, l, c)] == maze[conversion(1, 1, l, c)])
    {
        fprintf(fp_out, "%d\n", 0);
        return 0;
    }
    int final_vertex = abs(maze[conversion(a, b, l, c)]) - 2;
    int inicial_vertex = abs(maze[conversion(1, 1, l, c)]) - 2;

    LinkedList **adjList;
    adjList = fillAdjList(maze, l, c, walls, walls_array, a, b, rooms);

    int **result, *cost, *parent;
    result = dijkstras(adjList, maze, rooms, inicial_vertex, final_vertex);

    cost = result[0];
    parent = result[1];
    free(result);

    int final_cost = cost[final_vertex];

    if (final_cost == INT_MAX)
    {
        for (i = 0; i < rooms; i++)
            freeLinkedList(adjList[i]);
        free(adjList);
        free(cost);
        free(parent);
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }
    fprintf(fp_out, "%d\n", cost[final_vertex]);

    printPath(fp_out, l, c, adjList, maze, parent, final_vertex, 1);

    for (i = 0; i < rooms; i++)
        freeLinkedList(adjList[i]);

    free(adjList);
    free(cost);
    free(parent);

    return final_cost;
}

int make_rooms(int *maze, int l, int c, int cells_number, int walls, int *walls_array)
{
    int i, j, k = 0, a, b, src_x = 0, src_y = 0, *coord;
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    for (i = 0; i < walls; i++)
    {
        coord = inverted_conversion(walls_array[i], l, c);
        a = coord[0];
        b = coord[1];
        free(coord);
        for (j = 0; j < 4; j++)
        {
            src_x = a + rowNum[j];
            src_y = b + colNum[j];
            if (maze[conversion(src_x, src_y, l, c)] == 0)
            {
                bfs(maze, k, l, c, conversion(src_x, src_y, l, c));
                k++;
            }
        }
    }
    return k;
}

void bfs(int *maze, int k, int l, int c, int src) // BFS
{
    Queue *roomStack = NULL, *stackTail = NULL;
    int a, b, a1, b1, i, *coord;
    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    maze[src] = (-k - 2);

    push(&roomStack, &stackTail, src);

    while (isEmpty(roomStack) != 1)
    {
        // obter coordenadas da src
        coord = inverted_conversion(roomStack->vertex, l, c);
        a = coord[0];
        b = coord[1];
        free(coord);

        roomStack = pop(&roomStack); // pop esta bem feito?
        for (i = 0; i < 4; i++)
        {
            a1 = a + rowNum[i];
            b1 = b + colNum[i];
            if (maze[conversion(a1, b1, l, c)] == 0)
            {
                maze[conversion(a1, b1, l, c)] = (-k - 2);
                push(&roomStack, &stackTail, conversion(a1, b1, l, c));
            }
        }
    }
}

void printPath(FILE *fp_out, int l, int c, LinkedList **adjList, int *maze, int *parent, int j, int k)
{
    // Base Case : If j is source
    if (parent[j] == -1)
    {
        fprintf(fp_out, "%d\n", --k);
        return;
    }
    k++;
    printPath(fp_out, l, c, adjList, maze, parent, parent[j], k);

    LinkedList *Node = get_vertex(adjList[j], parent[j], -1);

    int *coord = inverted_conversion(Node->Wall, l, c);

    fprintf(fp_out, "%d %d %d\n", coord[0], coord[1], maze[Node->Wall]);
    free(coord);
}

void print_table(int *table, int l, int c)
{
    int i, j;
    for (i = 1; i <= 10; i++)
    {
        for (j = 1; j <= 10; j++)
        {
            if (table[conversion(i, j, l, c)] >= 0)
            {
                printf(" ");
            }
            printf("%d ", table[conversion(i, j, l, c)]);
        }
        printf("\n");
    }
    printf("\n");
}