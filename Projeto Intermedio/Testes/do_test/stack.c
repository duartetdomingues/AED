/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   stack.c
 *
 * DESCRIPTION
 * 
 * 
 * exemple:
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 * 
 * 
 * exemple:
 *   Code for public distribution
 ******************************************************************************/

#include "roap.h"

/******************************************************************************
 * createStack()
 *
 * Arguments: capacity - (...)
 * Returns: stack pointer
 * Side-Effects: (exemple)pairs of elements are read and the connectivity array is modified
 *
 *
 * Description: (ver ingles)Create a Stack algorithm
 *****************************************************************************/
struct Stack *createStack(unsigned capacity){
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top_a2 = -1;
    stack->top_b2 = -1;
    stack->a2 = (int *)malloc(stack->capacity * sizeof(int));
    stack->b2 = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}


/******************************************************************************
 * freeStack()
 *
 * Arguments: stack - stack pointer
 * Returns: (void)
 * Side-Effects: (exemple)pairs of elements are read and the connectivity array is modified
 *
 *
 * Description: (ver ingles) Free the memory allocated to the stack
 *****************************************************************************/
void freeStack(struct Stack *stack){
    free(stack->a2);
    free(stack->b2);
    free(stack);
}

/******************************************************************************
 * isEmply()
 *
 * Arguments: stack - stack pointer
 * Returns: (ver ingles) 1 if stack is Emply or 0 if stack isn't Emply
 * Side-Effects: (exemple)pairs of elements are read and the connectivity array is modified
 *
 *
 * Description: (ver ingles) See if the stack is empty
 *****************************************************************************/
int isEmpty(struct Stack *stack){
    if (stack->top_a2 == -1 && stack->top_b2 == -1){
        return 1;
    }
    else{
        return 0;
    }
}

/******************************************************************************
 * push()
 *
 * Arguments: stack - stack pointer
 *                  - item1
 *                  - item2
 * Returns: (void)
 * Side-Effects: (exemple)pairs of elements are read and the connectivity array is modified
 *
 *
 * Description: (ver ingles) Push a (a2) and (b2) items to stack
 *****************************************************************************/
void push(struct Stack *stack, int item1, int item2){
    stack->a2[++stack->top_a2] = item1;
    stack->b2[++stack->top_b2] = item2;
}

/******************************************************************************
 * pop_a2()
 *
 * Arguments: stack - stack pointer
 * Returns: (ver ingles)a2 item
 * Side-Effects: (exemple)pairs of elements are read and the connectivity array is modified
 *
 *
 * Description: (ver ingles) Pop a (a2) item to stack
 *****************************************************************************/
int pop_a2(struct Stack *stack){
    if (isEmpty(stack))
        return 0;
    return stack->a2[stack->top_a2--];
}


/******************************************************************************
 * pop_b2()
 *
 * Arguments: stack - stack pointer
 * Returns: (ver ingles)b2 item
 * Side-Effects: (exemple)pairs of elements are read and the connectivity array is modified
 *
 *
 * Description: (ver ingles) Pop a (b2) item to stack
 *****************************************************************************/
int pop_b2(struct Stack *stack){
    if (isEmpty(stack))
        return 0;
    return stack->b2[stack->top_b2--];
}
