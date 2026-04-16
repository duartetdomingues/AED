/******************************************************************************
 * (c) 2018-2019 AED Team
 * Last modified: abl 2019-03-17
 *
 * NAME
 *      LinkedList.c
 *
 * DESCRIPTION
 *      Implementation of an abstract Linked List
 *
 * COMMENTS
 *      (Derived from 2018/10/24 lab4 code)
 *
 *  Implementation details:
 *      Linked list node: Each node of the list contains an item and a
 *      pointer to the next node.
 *      The item is specified in the file defs.h, expectably also a pointer.
 *
 *      Item deletion/freeing and comparison functions must be supplied
 *
 *****************************************************************************/
#include "roap.h"
#include "LinkedList.h"

/*
 *  Function:
 *    initLinkedList
 *
 *  Description:
 *    Initializes a new linked list.
 *
 *  Arguments:
 *    None
 *
 *  Return value:
 *    Returns the pointer to a new linked list.
 */

LinkedList *initLinkedList(void)
{
    return NULL;
}

/*
 *  Function:
 *    freeLinkedList
 *
 *  Description:
 *    Frees the memory allocated to a linked list.
 *
 *  Arguments:
 *    Pointer to the first element of a linked list:
 *      (LinkedList *) first
 *    Function to free the memory allocated to the items:
 *      void freeItem(Item)
 *
 *  Return value:
 *    None
 */

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

/*
 *  Function:
 *    insertLinkedList
 *
 *  Description:
 *    Creates a new node at the head of the linked list.
 *
 *  Arguments:
 *    Item to associate to the new node:
 *      Item this
 *    Pointer to the next node:
 *      (LinkedList *) next
 *
 *  Return value:
 *    Returns the pointer to the new head of the list.
 */

LinkedList *insertLinkedList(int x_vertex, int x_wall)
{
    LinkedList *new;

    /* Memory allocation */
    new = (LinkedList *)malloc(sizeof(LinkedList));

    /* Check memory allocation errors */
    if (new == NULL)
        return NULL;

    /* Initialize new node */
    new->Vertex = x_vertex;
    new->Wall = x_wall;
    new->next = NULL;

    return new;
}

LinkedList** fillAdjList(int *maze, int l, int c, int walls, int *walls_array, int a, int b, int rooms){

    LinkedList **adjList = NULL;
    adjList = (LinkedList **)calloc(rooms, sizeof(adjList));
    int a1, b1, i, *coord;

    for (i = 0; i < rooms; i++)
        adjList[i] = initLinkedList();

    for (i = 0; i < walls; i++)
    {
        coord = inverted_conversion(walls_array[i], l, c);
        a1 = coord[0];
        b1 = coord[1];

        free(coord);
        if((maze[conversion(a1, b1 - 1, l, c)]< -1 && maze[conversion(a1, b1 + 1, l, c)]<-1) && (maze[conversion(a1, b1 - 1, l, c)] != maze[conversion(a1, b1 + 1, l, c)])){
            add_edge(adjList,maze,maze[conversion(a1, b1 - 1, l, c)],maze[conversion(a1, b1 + 1, l, c)], conversion(a1, b1 , l, c));
        }
        if((maze[conversion(a1 - 1, b1, l, c)]<-1 && maze[conversion(a1 + 1, b1, l, c)]<-1) && (maze[conversion(a1- 1, b1 , l, c)] != maze[conversion(a1 + 1, b1, l, c)])){
            add_edge(adjList,maze,maze[conversion(a1 - 1, b1, l, c)],maze[conversion(a1 + 1, b1, l, c)],conversion(a1, b1 , l, c));
        }
    }
    return adjList;
}

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

/* QUEUE: */

/******************************************************************************
 * freeStack()
 *
 * Arguments: stack (stack pointer)
 * Returns: (void)
 *
 * Description: Free the memory allocated to the stack
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
 * Arguments: stack (stack pointer)
 * Returns: 1 if the stack is empty and 0 if it isn't.
 *
 * Description: Check whether the stack is empty or not.
 *****************************************************************************/
int isEmpty(Queue *aux){
    if(aux==NULL)
        return 1;

    return 0;
}

/******************************************************************************
 * push()
 *
 * Arguments: stack (stack pointer), item1, item2
 *
 * Description: Push items a2 and b2 to the stack.
 *****************************************************************************/
void push(Queue **head,Queue **final,int new_vertex)
{
    Queue *new= NULL;
    new = (Queue*)malloc(sizeof(Queue));
    if(new==NULL){
        printf("erro memoria\n\n\n");
    }

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
 * Arguments: stack (stack pointer)
 * Returns: Item a2
 *
 * Description: Pop items a2 and b2 from the stack.
 *****************************************************************************/
Queue* pop(Queue **queue)
{   
    Queue *aux;
    aux = *queue;
    if(isEmpty(aux)) return 0;

    *queue = (*queue)->next;
    free(aux);
    return *queue;
}
