/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   variants.c
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


void variants(int variant, FILE* fp_out, int* maze, int l, int c, int num_cells, int a, int b, int a1, int b1){
    switch (variant){
        case 1:
            fprintf(fp_out, "%d\n\n", maze[conversion(a, b, l, c)]);
            break;

        case 2:
            if (maze[conversion(a, b - 1, l, c)] == 0 || maze[conversion(a, b + 1, l, c)] == 0 || maze[conversion(a - 1, b, l, c)] == 0 || maze[conversion(a + 1, l, b, c)] == 0){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }
            //-2 fora do lab e 0 ou 1 para af ou neg

        case 3:
            if (maze[conversion(a, b - 1, l, c)] > 0 || maze[conversion(a, b + 1, l, c)] > 0 || maze[conversion(a - 1, b, l, c)] > 0 || maze[conversion(a + 1, b, l, c)] > 0){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }

        case 4:
            if (maze[conversion(a, b - 1, l, c)] == -1 || maze[conversion(a, b + 1, l, c)] == -1 || maze[conversion(a - 1, b, l, c)] == -1 || maze[conversion(a + 1, b, l, c)] == -1){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }


        case 5:
            if (maze[conversion(a, b, l, c)] <= 0){
                fprintf(fp_out, "-1\n\n");
                break;
            }
            else{
                if((maze[conversion(a,b-1,l,c)]==0 && maze[conversion(a,b+1,l,c)]==0) || (maze[conversion(a-1,b,l,c)]==0 && maze[conversion(a+1,b,l,c)]==0)){
                    fprintf(fp_out, "1\n\n");
                    break;
                }
                else{
                    fprintf(fp_out, "0\n\n");
                    break;
                }
            }

        case 6:
            if (maze[conversion(a, b, l, c)] == -2 || maze[conversion(a1, b1, l, c)] == -2){
                fprintf(fp_out, "-2\n\n");
                break;
            }
            else if (maze[conversion(a, b, l, c)] != 0 || maze[conversion(a1, b1, l, c)] != 0){
                fprintf(fp_out, "0\n\n");
                break;
            }

            if (a6(a, b, a1, b1, l, c, num_cells, maze)){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }
    }
}


/******************************************************************************
 * a6()
 *
 * Arguments: (...)
 * Returns: 1 if (...) or 0 if (...)
 * Side-Effects: (exemple)pairs of elements are read and the connectivity array is modified
 *
 *
 * Description: (...)
 *****************************************************************************/
int a6(int a, int b, int a1, int b1, int l, int c, int num_cells, int *maze){
    
    struct Stack *stack = createStack(num_cells);
    int a2 = a, b2 = b;
    unsigned int *id = (unsigned int *)malloc((num_cells + 1) * sizeof(unsigned int));

    for (int i = 0; i <= num_cells; i++){
        id[i] = i;
    }

    push(stack,a,b);
    do{
        a2 = pop_a2(stack);
        b2 = pop_b2(stack);

        if (maze[conversion(a2, b2 - 1, l, c)] == 0){
            id[conversion(a2, b2 - 1, l, c)] = conversion(a, b, l, c);
            push(stack, a2, b2 - 1);
        }
        if (maze[conversion(a2, b2 + 1, l, c)] == 0){
            id[conversion(a2, b2 + 1, l, c)] = conversion(a, b, l, c);
            push(stack, a2, b2 + 1);;
        }

        if (maze[conversion(a2 - 1, b2, l, c)] == 0){
            id[conversion(a2 - 1, b2, l, c)] = conversion(a, b, l, c);
            push(stack, a2 - 1, b2);
        }
        if (maze[conversion(a2 + 1, b2, l, c)] == 0){
            id[conversion(a2 + 1, b2, l, c)] = conversion(a, b, l, c);
            push(stack, a2 + 1, b2);
        }

        maze[conversion(a2, b2, l, c)] = -1;

    } while (id[conversion(a1, b1, l, c)] != conversion(a, b, l, c) && isEmpty(stack) != 1);

    freeStack(stack);

    if (id[conversion(a1, b1, l, c)] != conversion(a, b, l, c)){
        free(id);
        return 0;
    }
    else{
        free(id);
        return 1;
    }
}