/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Nov. 2021-11-12
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 *      Main program to read the given file and call the makeRooms, fillAdjList 
 *      and Dijkstras function. This function will conclude the solution to the 
 *      given maze.
 *
 ******************************************************************************/

#include "roap.h"

int maze_solver(FILE *fp_out, int *maze, int l, int c, int cells_number, int walls, int *walls_array, int a, int b)
{
    LinkedList **adjList;
    int i, rooms, inicial_vertex, final_vertex, **result, *cost, *parent, final_cost;
    
    /* Checking if the starting and end cells are white cells. If not, execution is ended */
    if (maze[conversion(a, b, l, c)] != 0 || maze[conversion(1, 1, l, c)] != 0)
    {
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }

    /* 'Painting' the rooms with different negative numbers and counting the number of rooms */
    rooms = makeRooms(maze, l, c, cells_number,walls,walls_array);

    /* Checking if the starting and end cells are in the same room */
    if (maze[conversion(a, b, l, c)] == maze[conversion(1, 1, l, c)])
    {
        fprintf(fp_out, "%d\n", 0);
        return 0;
    }

    if (maze[conversion(a, b, l, c)] == 0)
    {
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }

    /* Assuming the room numer of starting and ending cell */
    inicial_vertex = abs(maze[conversion(1, 1, l, c)]) - 2;
    final_vertex = abs(maze[conversion(a, b, l, c)]) - 2;

    /* Filling the Adjacent List */
    adjList = fillAdjList(maze, l, c, walls, walls_array, a, b, rooms);

    /* In the cases where the starting or ending cell are in isolated rooms (impossible path) */
    if(adjList[final_vertex]==NULL || adjList[inicial_vertex]==NULL){
        for (i = 0; i < rooms; i++)
            freeLinkedList(adjList[i]);
        free(adjList);
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }

    /* Running Dijkstras algorithm on the adjacency list and calculating its cost and parent */
    result = dijkstras(adjList, maze, rooms, inicial_vertex, final_vertex);
    cost = result[0];
    parent = result[1];

    free(result);

    /* Assuming its final cost and checking if the algorithm ran out of possibilities or not */
    final_cost = cost[final_vertex];
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
    /* printing the cost, if its valid */
    fprintf(fp_out, "%d\n", cost[final_vertex]);

    /* printing the path */
    printPath(fp_out, l, c, adjList, maze, parent, final_vertex, 1);

    /* Freeing the data structure */
    for (i = 0; i < rooms; i++)
        freeLinkedList(adjList[i]);

    free(adjList);
    free(cost);
    free(parent);

    return 1;
}

/******************************************************************************
 * makeRooms()
 *
 * Arguments: maze, l, c, cells_number
 * Returns: k (number of rooms)
 *
 * Description: This algorithm is very similar to BFS. Our maze is transversed 
 * in order to find new source cells for each iteration.
 *  
 *****************************************************************************/
int makeRooms(int *maze, int l, int c, int cells_number, int walls, int *walls_array)
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

    if(maze[conversion(1,1,l,c)]==0){
        bfs(maze, k, l, c, conversion(1, 1, l, c));
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

/******************************************************************************
 * freeQueue()
 *
 * Arguments: head
 * Returns: -
 *
 * Description: Frees the BFS' queue.
 *****************************************************************************/
void freeQueue(Queue *head){
    Queue *aux;
    while(head!=NULL){
        aux=head;
        head=head->next;
        free(aux);
    }
}

/******************************************************************************
 * isEmpty()
 *
 * Arguments: aux
 * Returns: 0 or 1.
 *
 * Description: Returns 1 if stack is empty and vice-versa.
 *****************************************************************************/
int isEmpty(Queue *aux){
    if(aux==NULL)
        return 1;

    return 0;
}

/******************************************************************************
 * push()
 *
 * Arguments: head, final, new_vertex
 *
 * Description: Push new_vertex to the queue.
 *****************************************************************************/
void push(Queue **head,Queue **final,int new_vertex)
{
    Queue *new= NULL;
    new = (Queue*)malloc(sizeof(Queue));

    new->next=NULL;
    new->vertex=new_vertex;

    if(*head==NULL){  
        *head=new;
        *final=*head;
    }
    else{
        (*final)->next=new;
        *final=new;
    }
    return;
}

/******************************************************************************
 * pop()
 *
 * Arguments: queue
 * Returns: queue head's pointer
 *
 * Description: Pop vertex from the queue.
 * 
 *****************************************************************************/
Queue* pop(Queue **queue)
{   
    Queue *aux;
    aux = *queue;
    if(isEmpty(aux)) return NULL;

    *queue = (*queue)->next;
    free(aux);
    return *queue;
}

/******************************************************************************
 * printPath()
 *
 * Arguments: fp_out, l, c, adjList, maze, parent, j, k
 * Returns: stack (stack pointer)
 *
 * Description: Print the path discovered by Dijkstras.
 * 
 *****************************************************************************/
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
