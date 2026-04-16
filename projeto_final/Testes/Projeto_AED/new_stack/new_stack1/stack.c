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

#include "roap2.h"

/******************************************************************************
 * createStack()
 *
 * Arguments: capacity
 * Returns: stack (stack pointer)
 *
 * Description: Create a stack algorithm
 *****************************************************************************/

Stack *createStack(Stack* stack){
    stack->next = NULL;
    stack->a = -1;
    stack->b = -1;
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
void freeStack(Stack *head){
    Stack *aux;
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

int isEmpty(Stack *aux){
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

/* void push(struct Stack *stack, int item1, int item2){
    stack->a2[++stack->top_a2] = item1;
    stack->b2[++stack->top_b2] = item2;
} */

/******************************************************************************
 * pop_a2()
 *
 * Arguments: stack (stack pointer)
 * Returns: Item a2
 *
 * Description: Pop items a2 and b2 from the stack.
 *****************************************************************************/

/* int pop_a(struct Stack *stack){
    if (isEmpty(stack)){
        printf("stack vazia\n");return 0;
    }
    return stack->a2[stack->top_a2--];
} */

/******************************************************************************
 * pop_b2()
 *
 * Arguments: stack (stack pointer)
 * Returns: Item b2
 *
 * Description: Pop item b2 from the stack.
 *****************************************************************************/

/* int pop_b(struct Stack *stack){
    if (isEmpty(stack)){
        printf("stack vazia\n");
        return 0;
    }
        
    return stack->b2[stack->top_b2--];
} */

/* void push_a(struct Stack *stack, int item){
    stack->a2[++stack->top_a2] = item;
}

void push_b(struct Stack *stack, int item){
    stack->b2[++stack->top_b2] = item;
}
 */


/* void print_stack(struct Stack *stack){
    for(int i=0;i<stack->top_a2;i++){
        printf("|%d-%d|",stack->a2[i],stack->b2[i]);
    }
} */

Stack* push(Stack *aux,int a1, int b1)
{
   Stack *new= NULL;
   new = (struct stack*)malloc(sizeof(struct stack));
   new->a = a1;
   new->b = b1;
   new->next=aux;
   return new;
   
}
/* void push(int a1, int b1)
{
   struct stackB *newNode;
   newNode = (struct stackB*)malloc(sizeof(struct stackB));
   newNode->a1 = a1;
   newNode->b1 = b1;
   if(topB == NULL)
      newNode->next = NULL;
   else
      newNode->next = topB;
   topB = newNode;
   //printf("\nInsertion is Success!!!\n");
} */

int pop_a(Stack * aux)
{
    if(isEmpty(aux)) return 0;
    return aux->a;
}


int pop_b(Stack * aux)
{
   if(isEmpty(aux)) return 0;
    return aux->b;
}
