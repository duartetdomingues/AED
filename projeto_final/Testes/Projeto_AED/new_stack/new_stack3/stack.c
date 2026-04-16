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
void push(Stack **head,Stack **final,int a1, int b1)
{
    Stack *new= NULL;
    new = (Stack*)malloc(sizeof(Stack));
    if(new==NULL){
        printf("erro memoria\n\n\n");
    }
    new->next=NULL;
    new->a=a1;
    new->b=b1;
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
 * pop_a()
 *
 * Arguments: stack (stack pointer)
 * Returns: Item a2
 *
 * Description: Pop items a2 and b2 from the stack.
 *****************************************************************************/
int pop_a(Stack * aux)
{
    if(isEmpty(aux)) return 0;
    return aux->a;
}

/******************************************************************************
 * pop_b()
 *
 * Arguments: stack (stack pointer)
 * Returns: Item b2
 *
 * Description: Pop item b2 from the stack.
 *****************************************************************************/
int pop_b(Stack * aux)
{
   if(isEmpty(aux)) return 0;
    return aux->b;
}

/* void print_stack(struct Stack *stack){
    for(int i=0;i<stack->top_a2;i++){
        printf("|%d-%d|",stack->a2[i],stack->b2[i]);
    }
} */






