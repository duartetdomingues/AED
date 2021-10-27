/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   stack.c
 *
 * DESCRIPTION
 *      This algorithm is used to store the possible paths that can be 
 * followed to arrive to the finishing cell. A stack is used to suppress the 
 * need of using an algorithm that searches the whole array evrytime that is 
 * needed to check the next possible path.
 * 
 ******************************************************************************/

#include "roap.h"

/******************************************************************************
 * createStack()
 *
 * Arguments: capacity
 * Returns: stack (stack pointer)
 *
 * Description: Create a stack algorithm
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
 * Arguments: stack (stack pointer)
 * Returns: (void)
 *
 * Description: Free the memory allocated to the stack
 *****************************************************************************/
void freeStack(struct Stack *stack){
    free(stack->a2);
    free(stack->b2);
    free(stack);
}

/******************************************************************************
 * isEmpty()
 *
 * Arguments: stack (stack pointer)
 * Returns: 1 if the stack is empty and 0 if it isn't.
 *
 * Description: Check whether the stack is empty or not.
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
 * Arguments: stack (stack pointer), item1, item2
 *
 * Description: Push items a2 and b2 to the stack.
 *****************************************************************************/

void push(struct Stack *stack, int item1, int item2){
    stack->a2[++stack->top_a2] = item1;
    stack->b2[++stack->top_b2] = item2;
}

/******************************************************************************
 * pop_a2()
 *
 * Arguments: stack (stack pointer)
 * Returns: Item a2
 *
 * Description: Pop items a2 and b2 from the stack.
 *****************************************************************************/

int pop_a2(struct Stack *stack){
    if (isEmpty(stack)){
        printf("stack vazia\n");return 0;
    }
    return stack->a2[stack->top_a2--];
}

/******************************************************************************
 * pop_b2()
 *
 * Arguments: stack (stack pointer)
 * Returns: Item b2
 *
 * Description: Pop item b2 from the stack.
 *****************************************************************************/

int pop_b2(struct Stack *stack){
    if (isEmpty(stack)){
        printf("stack vazia\n");return 0;
    }
        
    return stack->b2[stack->top_b2--];
}

void push_a2(struct Stack *stack, int item){
    stack->a2[++stack->top_a2] = item;
}

void push_b2(struct Stack *stack, int item){
    stack->b2[++stack->top_b2] = item;
}



void print_stack(struct Stack *stack){
    for(int i=0;i<stack->top_a2;i++){
        printf("|%d-%d|",stack->a2[i],stack->b2[i]);
    }
}
