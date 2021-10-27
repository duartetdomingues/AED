#ifndef __roap__
#define __roap__


int a6(int a,int b,int a1,int b1,int l, int c, int num_cells,int* maze);

struct Stack* createStack(unsigned capacity);
void freeStack(struct Stack* stack);
int isEmpty(struct Stack* stack);
void push_a2(struct Stack* stack, int item);
void push_b2(struct Stack* stack, int item);
int pop_a2(struct Stack* stack);
int pop_b2(struct Stack* stack);


int conversion(int a,int b,int l, int c);

#endif    /* __roap__ */