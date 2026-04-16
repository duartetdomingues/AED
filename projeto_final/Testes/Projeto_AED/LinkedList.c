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
#include "roap2.h"
#include"LinkedList.h"


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
LinkedList * initLinkedList(void)
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
    while (first!=NULL)
    {
        aux=first->next;
        free(first);
        first=aux;
    }
    
    return;
}


/*void freeItemFnt(Item node){
    free(node);
    return;
} */


/*
 *  Function:
 *    lengthLinkedList
 *
 *  Description:
 *    Determines the length of a linked list.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *        (LinkedList *) first
 *
 *  Return value:
 *    Returns the length of the linked list.
 */
int lengthLinkedList(LinkedList *first)
{
    LinkedList *aux;
    int counter;

    /* Length determination cycle                                   */
    for(aux = first, counter = 0;
        aux!=NULL;
        counter++, aux = aux->next);

    return counter;
}


/*
 *  Function:
 *    getNextNodeLinkedList
 *
 *  Description:
 *    Returns the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the next node of a linked list. NULL
 *   is returned in case the current node is empty or there is no
 *   node following the current node.
 */
LinkedList * getNextNodeLinkedList(LinkedList * node)
{
  return ((node == NULL) ? NULL : node->next);
}

LinkedList * getItemLinkedList(LinkedList *node)
{
    if(node == NULL)  /* Check that node is not empty */
        return NULL;

    return node;
}
/*
 *  Function:
 *    insertUnsortedLinkedList
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
LinkedList *insertLinkedList(int x_vertix,int x_weight)
{
    LinkedList *new;

    /* Memory allocation */
    new = (LinkedList *) malloc(sizeof(LinkedList));

    /* Check memory allocation errors */
    if(new == NULL)
        return NULL;

    /* Initialize new node */
    new->Weight=x_weight;
    new->Vertix=x_vertix;
    new->next = NULL;

    return new;
}

LinkedList** fillAdjList(int *maze, int l, int c, int walls, int *walls_array, int a, int b, int rooms){

    LinkedList **adjList = NULL, *Node;
    adjList = (LinkedList **)calloc(rooms, sizeof(adjList));
    int a1, b1, i, *coord;

    for (i = 0; i < rooms; i++)
        adjList[i] = initLinkedList();

    for (i = 0; i < walls; i++)
    {
        if(maze[walls_array[i]]==-1){
            continue;
        }
        coord = inverted_conversion(walls_array[i], l, c);
        a1 = coord[0];
        b1 = coord[1];

        free(coord);
        if ((maze[conversion(a1, b1 - 1, l, c)] < -1) && (maze[conversion(a1, b1 + 1, l, c)] < -1) && (maze[conversion(a1, b1 - 1, l, c)] != maze[conversion(a1, b1 + 1, l, c)]))
        {
            if (adjList[abs(maze[conversion(a1, b1 - 1, l, c)]) - 2] != NULL)
            { 
                Node = get_vertix(adjList[abs(maze[conversion(a1, b1 - 1, l, c)]) - 2], abs(maze[conversion(a1, b1 + 1, l, c)]) - 2, conversion(a1, b1, l, c));

                if (maze[Node->Weight] > maze[conversion(a1, b1, l, c)])
                {
                    Node->Weight = conversion(a1, b1, l, c);
                }
            }
            else
            {
                Node = insertLinkedList(abs(maze[conversion(a1, b1 + 1, l, c)]) - 2, conversion(a1, b1, l, c));
                // Node->Weight = maze[conversion(a1, b1, l, c)];
                adjList[abs(maze[conversion(a1, b1 - 1, l, c)]) - 2] = Node;
            }

            if (adjList[abs(maze[conversion(a1, b1 + 1, l, c)]) - 2] != NULL)
            {
                Node = get_vertix(adjList[abs(maze[conversion(a1, b1 + 1, l, c)]) - 2], abs(maze[conversion(a1, b1 - 1, l, c)]) - 2, conversion(a1, b1, l, c));

                if (maze[Node->Weight] > maze[conversion(a1, b1, l, c)])
                {
                    Node->Weight = conversion(a1, b1, l, c);
                }
            }
            else
            {
                Node = insertLinkedList(abs(maze[conversion(a1, b1 - 1, l, c)])-2, conversion(a1, b1, l, c));
                // Node->Weight = maze[conversion(a1, b1, l, c)];
                adjList[abs(maze[conversion(a1, b1 + 1, l, c)]) - 2] = Node;
            }
        }

        if ((maze[conversion(a1 - 1, b1, l, c)] < -1) && (maze[conversion(a1 + 1, b1, l, c)] < -1) && (maze[conversion(a1 - 1, b1, l, c)] != maze[conversion(a1 + 1, b1, l, c)]))
        {
            if (adjList[abs(maze[conversion(a1 - 1, b1, l, c)]) - 2] != NULL)
            {
                Node = get_vertix(adjList[abs(maze[conversion(a1 - 1, b1, l, c)]) - 2], abs(maze[conversion(a1 + 1, b1, l, c)]) - 2, conversion(a1, b1, l, c));

                if (maze[Node->Weight] > maze[conversion(a1, b1, l, c)])
                {
                    Node->Weight = conversion(a1, b1, l, c);
                }
            }
            else
            {
                Node = insertLinkedList(abs(maze[conversion(a1 + 1, b1, l, c)]) -2, conversion(a1, b1, l, c));
                // Node->Weight = maze[conversion(a1, b1, l, c)];
                adjList[abs(maze[conversion(a1 - 1, b1, l, c)]) - 2] = Node;
            }

            if (adjList[abs(maze[conversion(a1 + 1, b1, l, c)]) - 2] != NULL)
            {
                Node = get_vertix(adjList[abs(maze[conversion(a1 + 1, b1, l, c)]) - 2], abs(maze[conversion(a1 - 1, b1, l, c)]) - 2, conversion(a1, b1, l, c));

                if (maze[Node->Weight] > maze[conversion(a1, b1, l, c)])
                {
                    Node->Weight = conversion(a1, b1, l, c);
                }
            }
            else
            {

                Node = insertLinkedList(abs(maze[conversion(a1 - 1, b1, l, c)])- 2, conversion(a1, b1, l, c));
                // Node->Weight = maze[conversion(a1, b1, l, c)];
                adjList[abs(maze[conversion(a1 + 1, b1, l, c)]) - 2] = Node;
            }
        }
    }
    return adjList;
}

LinkedList* get_vertix(LinkedList* head,int x_vertix ,int x_weight)
{
    LinkedList * aux;
    aux=head;
    while (aux != NULL)
    {
        if(aux->Vertix==x_vertix){
            return aux;
        }
        head=aux;
        aux = aux->next;
    }
    head->next=insertLinkedList(x_vertix, x_weight);
    return head->next;
}
