/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Nov. 2021-11-12
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 *      Function declarations for roap problems.
 *
 ******************************************************************************/

#ifndef LinkedListHeader
#define LinkedListHeader

/******************************************************************************
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *      1) Integer Vertex to store the Room.
 *      2) Integer Wall to store the nodes in the queue.
 *      3) Pointer to next node of the linked list.
 * 
 *****************************************************************************/

typedef struct LinkedList{
      int Vertex;
      int Wall;
      struct LinkedList *next;
}LinkedList;

LinkedList * initLinkedList(void);
LinkedList *insertLinkedList(int x_vertex,int x_wall);
LinkedList* get_vertex(LinkedList* head,int x_vertex,int x_wall);
void freeLinkedList(LinkedList * first);
void add_edge(LinkedList** adjList,int* maze,int room_a,int room_b,int grey);

LinkedList** fillAdjList(int *maze, int l, int c, int walls, int *walls_array, int a, int b, int rooms);


/* End of: Protect multiple inclusions                              */
#endif
