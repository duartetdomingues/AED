/******************************************************************************
 * (c) 2018-2019 AED Team
 * Last modified: abl 2019-03-17
 *
 * NAME
 *   LinkedList.h
 *
 * DESCRIPTION
 *  Header file for an abstract implementation of a Linked List
 *
 * COMMENTS
 *  (Derived from 2018/10/24 lab4 code)
 *
 *  Data type list:
 *    Linked list node: LinkedList
 *
 *  Function list:
 *    A) Initialization & Termination
 *        initLinkedList
 *        freeLinkedList
 *
 *    B) Properties
 *        lengthLinkedList
 *
 *    C) Navigation
 *        getNextNodeLinkedList
 *
 *    D) Lookup
 *        getItemLinkedList
 *
 *    E) Insertion - simple at head, sorted
 *       insertUnsortedLinkedList
 *       insertSortedLinkedList
 *
 *  Dependencies:
 *    stdio.h
 *    stdlib.h
 *    defs.h
 *
 *****************************************************************************/


/* Prevent multiple inclusions */
#ifndef LinkedListHeader
#define LinkedListHeader

/* Header file for the definition of the Item type */

/*
 *  Data type: LinkedList
 *
 *  Description: Node of a linked list
 */

/*
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *      1) Item of the linked list node (possibly pointer to data)
 *      2) Item of the linked list node (possibly pointer to data)
 *      3) Item of the linked list node (possibly pointer to data)
 *      4) Pointer to next node of the linked list.
 */

typedef struct LinkedList{
      int Vertix;
      int Wall;
      int Weight;
      struct LinkedList *next;
}LinkedList;


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
LinkedList * initLinkedList(void);

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
void freeLinkedList(LinkedList * first);

/*
 *  Function:
 *    insertLinkedList
 *
 *  Description:
 *    Creates a new linked list node.
 *
 *  Arguments:
 *    Vertix to associate to the new node:
 *      int x_vertix
 *    Pointer to the head node:
 *      (LinkedList *) head
 *
 *  Return value:
 *    Returns the pointer to the new node.
 */
LinkedList *insertLinkedList(int x_vertix,int x_wall,int x_weight);

LinkedList* get_vertix(LinkedList* head,int x_vertix,int x_wall,int x_weight);

void add_edge(LinkedList** adjList,int* maze,int room_a,int room_b,int grey);

LinkedList** fillAdjList(int *maze, int l, int c, int walls, int *walls_array, int a, int b, int rooms);


/* End of: Protect multiple inclusions                              */
#endif
