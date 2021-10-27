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

struct Stack{
        int top_a2, top_b2;
        unsigned int capacity;
        int *a2;
        int *b2;
};
int conversion(int a,int b,int l, int c);
int* inverted_conversion(int x, int l, int c);
int maze_solver(FILE* fp_out,int* maze, int l, int c, int cells_number, int a, int b);
void print_table(int* table,int l,int c);
void print_matrix(int** matrix,int l,int c);
void free_matrix(int** matrix,int l);
int* init_visited(int* maze,int l,int c,int cells_number);
int variants(int variant, int* maze, int l, int c, int num_cells, int a, int b, int a1, int b1);
int a6(int a,int b,int a1,int b1,int l, int c, int num_cells, int* maze);
int a7(int a, int b, int l, int c, int cells_number, int *maze,int *visited,int *flag);
int a8(int cell,int a1, int b1, int l, int c, int cells_number, int *maze);
int* _a7(int a, int b, int l, int c, int cells_number, int *maze,int *visited);
int all_combination(int* maze, int** adjMatrix , int l, int c, int cells_number, int a, int b,FILE *fp_out);
void depthFirstSearch(int* maze,int * visited, int** adjMatrix , int l, int c, int cells_number, int a, int b);
int search_path(int vertexIndex,int ** visited, int** adjMatrix, int cells_number, struct Stack* path_stack,int* maze,int a,int b,int l,int c,FILE *fp_out);
void addEdge(int**adjMatrix,int start,int end);
struct Stack* createStack(unsigned capacity);
void freeStack(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item1, int item2);
void push_a2(struct Stack *stack, int item);
void push_b2(struct Stack *stack, int item);
int pop_a2(struct Stack* stack);
int pop_b2(struct Stack* stack);
#endif    /* __roap__ */
