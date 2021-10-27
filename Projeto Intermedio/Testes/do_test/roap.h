/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   roap.h
 *
 * DESCRIPTION
 * 
 *
 *  exemple:
 *   Function declarations for connectivity problem solvers
 *
 * COMMENTS
 *
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
void variants(int variant, FILE* fp_out, int* maze, int l, int c, int num_cells, int a, int b, int a1, int b1);
int a6(int a,int b,int a1,int b1,int l, int c, int num_cells,int* maze);
struct Stack* createStack(unsigned capacity);
void freeStack(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int item1, int item2);
int pop_a2(struct Stack* stack);
int pop_b2(struct Stack* stack);



#endif    /* __roap__ */