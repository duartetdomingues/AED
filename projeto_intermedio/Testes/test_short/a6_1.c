#include <stdlib.h>
#include <stdio.h>
#include "test.h"

struct Stack {
    int top_a2,top_b2;
    unsigned int capacity;
    int* a2;
    int* b2;
};

int a6(int a,int b,int a1,int b1,int l, int c, int num_cells, int* maze){

            unsigned short *id = (unsigned short *) malloc((num_cells+1)* sizeof(unsigned short));

            for (int i = 0; i <= num_cells; i++){
                id[i] = i;
            }

            struct Stack* stack =createStack(num_cells);

            int a2=a, b2=b;
            
            do{
                
                if(maze[conversion(a2,b2-1,l,c)]==0){
                    id[conversion(a2,b2-1,l,c)]=conversion(a,b,l,c); 
                    push_a2(stack,a2);
                    push_b2(stack,b2-1); 
                }
                if(maze[conversion(a2,b2+1,l,c)]==0){
                    id[conversion(a2,b2+1,l,c)]=conversion(a,b,l,c);
                    push_a2(stack,a2);
                    push_b2(stack,b2+1); 
                }

                if(maze[conversion(a2-1,b2,l,c)]==0){
                    id[conversion(a2-1,b2,l,c)]=conversion(a,b,l,c); 
                    push_a2(stack,a2-1);
                    push_b2(stack,b2);
                }
                if(maze[conversion(a2+1,b2,l,c)]==0){
                    id[conversion(a2+1,b2,l,c)]=conversion(a,b,l,c);
                    push_a2(stack,a2+1);
                    push_b2(stack,b2);
                }

                maze[conversion(a2,b2,l,c)]=-1;
                a2=pop_a2(stack);
                b2=pop_b2(stack);

            }while(id[conversion(a1,b1,l,c)] != conversion(a,b,l,c) && isEmpty(stack)!=1 );
            
            freeStack(stack); 

            if(id[conversion(a1,b1,l,c)] != conversion(a,b,l,c)){
                free(id);  
                return 0;
            }
            else {
                free(id);
                return 1;
            }
            
}

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top_a2 = -1;
    stack->top_b2 = -1;
    stack->a2 = (int*)malloc(stack->capacity * sizeof(int));
    stack->b2 = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

void freeStack(struct Stack* stack)
{
    free(stack->a2);
    free(stack->b2);
    free(stack);
}

int isEmpty(struct Stack* stack)
{
    if(stack->top_a2==-1 && stack->top_b2==-1){
        return 1;
    }
    else{
        return 0;
    }
}

void push_a2(struct Stack* stack, int item)
{
    stack->a2[++stack->top_a2] = item;
}

void push_b2(struct Stack* stack, int item)
{
    stack->b2[++stack->top_b2] = item;
}
 
int pop_a2(struct Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->a2[stack->top_a2--];
}

int pop_b2(struct Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->b2[stack->top_b2--];
}
 