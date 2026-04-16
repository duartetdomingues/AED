/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Nov. 2021-11-12
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 *      Main program to read the given file and call the variants function
 *      which will output the desired information about one specific cell.
 *      Requires argc and argv as argument.
 *      Option "-s" to select the input's filename.
 *
 ******************************************************************************/

#include "roap.h"

/******************************************************************************
 * initLinkedList()
 *
 * Arguments: void
 * Returns: NULL
 *
 * Description: Initilizes the list with NULL
 * 
 *****************************************************************************/
LinkedList *initLinkedList(void)
{
    return NULL;
}

/******************************************************************************
 * freeLinkedList()
 *
 * Arguments: first (pointer to the beggining of the list)
 * Returns: -
 *
 * Description: Free the adjacency list.
 *****************************************************************************/
void freeLinkedList(LinkedList *first)
{
    LinkedList *aux;

    // Cycle from the first to the last element
    while (first != NULL)
    {
        aux = first->next;
        free(first);
        first = aux;
    }

    return;
}

/******************************************************************************
 * insertLinkedList()
 *
 * Arguments: x_vertex, x_wall
 * Returns: new
 *
 * Description: Create and insert a new node on the adjacency list.
 *****************************************************************************/
LinkedList *insertLinkedList(int x_vertex, int x_wall)
{
    LinkedList *new;

    /* Memory allocation */
    new = (LinkedList *)malloc(sizeof(LinkedList));

    if (new == NULL)
        return NULL;

    /* Initialize new node */
    new->Vertex = x_vertex;
    new->Wall = x_wall;
    new->next = NULL;

    return new;
}

/******************************************************************************
 * fillAdjList()
 *
 * Arguments: maze, l, c, walls, walls_array, a, b, rooms
 * Returns: adjList
 *
 * Description: Create and fills the adjacent list that represents the graph.
 *****************************************************************************/
LinkedList** fillAdjList(int *maze, int l, int c, int walls, int *walls_array, int a, int b, int rooms){

    LinkedList **adjList = NULL;
    adjList = (LinkedList **)calloc(rooms, sizeof(adjList));
    int a1, b1, i, *coord;

    for (i = 0; i < rooms; i++)
        adjList[i] = initLinkedList();

    /* Transversing the walls' array to fill the adjacency list */
    for (i = 0; i < walls; i++)
    {
        coord = inverted_conversion(walls_array[i], l, c);
        a1 = coord[0];
        b1 = coord[1];
        free(coord);

        //add to adjacency list if both cells belong to different rooms.
        if((maze[conversion(a1, b1 - 1, l, c)]< -1 && maze[conversion(a1, b1 + 1, l, c)]<-1) && (maze[conversion(a1, b1 - 1, l, c)] != maze[conversion(a1, b1 + 1, l, c)])){
            add_edge(adjList,maze,maze[conversion(a1, b1 - 1, l, c)],maze[conversion(a1, b1 + 1, l, c)], conversion(a1, b1 , l, c));
        }
        if((maze[conversion(a1 - 1, b1, l, c)]<-1 && maze[conversion(a1 + 1, b1, l, c)]<-1) && (maze[conversion(a1- 1, b1 , l, c)] != maze[conversion(a1 + 1, b1, l, c)])){
            add_edge(adjList,maze,maze[conversion(a1 - 1, b1, l, c)],maze[conversion(a1 + 1, b1, l, c)],conversion(a1, b1 , l, c));
        }
    }
    return adjList;
}

/******************************************************************************
 * get_vertex()
 *
 * Arguments: head, x_vertex, x_wall
 * Returns: head->next
 *
 * Description: It searches a specified vertex on the adjacency list. If
 * not found, this vertex is inserted and if it was found, the position
 * of that vertex on the list is returned.
 * 
 *****************************************************************************/
LinkedList *get_vertex(LinkedList *head, int x_vertex, int x_wall)
{
    LinkedList *aux;
    aux = head;
    while (aux != NULL)
    {
        if (aux->Vertex == x_vertex)
        {
            return aux;
        }
        head = aux;
        aux = aux->next;
    }
    head->next = insertLinkedList(x_vertex, x_wall);
    return head->next;
}

/******************************************************************************
 * add_edge()
 *
 * Arguments: adjList, maze, room_a, room_b, grey
 * Returns: -
 *
 * Description: Insertion on the adjacency list, it connects two rooms
 * and associate a specific weight to this connection, being this express
 * in form of a list.
 * 
 *****************************************************************************/
void add_edge(LinkedList **adjList, int *maze, int room_a, int room_b, int grey)
{

    LinkedList *Node=NULL;

    if (adjList[abs(room_a) - 2] != NULL)
    {
        Node = get_vertex(adjList[abs(room_a) - 2], abs(room_b) - 2, grey);

        if (maze[Node->Wall] > maze[grey])
        {
            Node->Wall = grey;
        }
    }
    else
    {
        Node = insertLinkedList(abs(room_b) - 2, grey);
        adjList[abs(room_a) - 2] = Node;
    }

    if (adjList[abs(room_b) - 2] != NULL)
    {
        Node = get_vertex(adjList[abs(room_b) - 2], abs(room_a) - 2, grey);

        if (maze[Node->Wall] > maze[grey])
        {
            Node->Wall = grey;
        }
    }
    else
    {
        Node = insertLinkedList(abs(room_a) - 2, grey);
        adjList[abs(room_b) - 2] = Node;
    }
}
