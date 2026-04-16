/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   roap.h
 * DESCRIPTION
 *      Function declarations for roap problems.
 ******************************************************************************/
#ifndef __roap__
#define __roap__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>
#include "LinkedList.h"

/* struct Stack{
        int top_a2, top_b2;
        unsigned int capacity;
        int *a2;
        int *b2;
}; */

typedef struct stack
{
   int a;
   int b;
   struct stack *next;
}Stack;

/* struct stackB
{
   int a1;
   int b1;
   struct stackB *next;
}*topB = NULL; */

void push(Stack **head,Stack **final,int a1, int b1);
int pop_a(Stack * aux);
int pop_b(Stack * aux);
int isEmpty(Stack *aux);
void freeStack(Stack *head);
Stack *createStack(Stack* stack);



// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};
// Structure to represent a min heap
struct MinHeap
{
    // Number of heap nodes present currently
    int size;    
   
    // Capacity of min heap
    int capacity; 
   
    // This is needed for decreaseKey()
    int *pos;   
    struct MinHeapNode **array;
};


struct node* createNode(int);
struct Graph *createAGraph(int);
int make_rooms(int* maze,int l,int c,int cells_number, int walls,int* walls_array);
void explore_room(int *maze, Stack **stack,Stack **final, int k, int l, int c);
int** dijkstra(LinkedList** adjList,int src,int V,int final_vertix);
struct MinHeap* createMinHeap(int capacity);
struct MinHeapNode* newMinHeapNode(int v,int dist);
void decreaseKey(struct MinHeap* minHeap,int v, int dist);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
int is_Empty(struct MinHeap* minHeap);
bool isInMinHeap(struct MinHeap *minHeap, int v);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap,int idx);
void printPath(FILE* fp_out,int l,int c,LinkedList** adjList,int* parent, int j,int k);
//void printSolution(FILE *fp_out,int *maze,int l,int c,LinkedList** adjList,int* dist, int V, int* parent, int final_vertix);
int a5(int* maze, int l, int c, int a, int b);


int conversion(int a,int b,int l, int c);
int* inverted_conversion(int x, int l, int c);
int maze_solver(FILE* fp_out,int* maze, int l, int c, int cells_number, int walls, int* walls_array, int a, int b);
void print_table(int* table,int l,int c);
//void print_matrix(int** matrix,int l,int c);
//void free_matrix(int** matrix,int l);
//int* init_visited(int* maze,int l,int c,int cells_number);
//int variants(int variant, int* maze, int l, int c, int num_cells, int a, int b, int a1, int b1);
//int a6(int a,int b,int a1,int b1,int l, int c, int num_cells, int* maze);
/* int a7(int a, int b, int l, int c, int cells_number, int *maze,bool *visited);
int a8(int cell,int a1, int b1, int l, int c, int cells_number, int *maze);
int* _a7(int a, int b, int l, int c, int cells_number, int *maze,int *visited);
 */
//int** adj_matrix(int **adjMatrix,int*maze,int l,int c,int cells_number);
//bool** adj_matrix2(bool **adjMatrix,int*maze,int l,int c,int cells_number,int walls,int* walls_array);
///int indexof(int i,int array[],size_t size);

//int all_combination(int* maze, int** adjMatrix , int l, int c, int cells_number, int a, int b,FILE *fp_out);
//void depthFirstSearch(int* maze,int * visited, int** adjMatrix , int l, int c, int cells_number, int a, int b);
//int search_path(int vertexIndex,int ** visited, int** adjMatrix, int cells_number, struct stackA* A, struct stackB* B,int* maze,int a,int b,int l,int c,FILE *fp_out);
//void addEdge(bool**adjMatrix,int start,int end);
//struct Stack* createStack(unsigned capacity);
//void freeStack(struct Stack* stack);
//int isEmpty();
/* void push(struct Stack* stack, int item1, int item2);
void push_a(struct Stack *stack, int item);
void push_b(struct Stack *stack, int item);
int pop_a(struct Stack* stack);
int pop_b(struct Stack* stack); */


#endif    /* __roap__ */
