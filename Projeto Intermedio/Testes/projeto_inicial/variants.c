/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *      variants.c
 *
 * DESCRIPTION
 *      This function writes the requested answer in the output file
 *      according to the selected variant.
 *
 ******************************************************************************/

#include "roap.h"

void variants(int variant, FILE* fp_out, int* maze, int l, int c, int cells_number, int a, int b, int a1, int b1){
    switch (variant){
        /* variant A1 */
        case 1:
            fprintf(fp_out, "%d\n\n", maze[conversion(a, b, l, c)]);
            break;

        /* variant A2 */
        case 2:
            //exploring the neighborhood of the cell
            if (maze[conversion(a, b - 1, l, c)] == 0 || maze[conversion(a, b + 1, l, c)] == 0 || maze[conversion(a - 1, b, l, c)] == 0 || maze[conversion(a + 1, l, b, c)] == 0){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }

        /* variant A3 */
        case 3:
            //exploring the neighborhood of the cell 
            if (maze[conversion(a, b - 1, l, c)] > 0 || maze[conversion(a, b + 1, l, c)] > 0 || maze[conversion(a - 1, b, l, c)] > 0 || maze[conversion(a + 1, b, l, c)] > 0){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }

        /* variant A4 */
        case 4:
            //exploring the neighborhood of the cell 
            if (maze[conversion(a, b - 1, l, c)] == -1 || maze[conversion(a, b + 1, l, c)] == -1 || maze[conversion(a - 1, b, l, c)] == -1 || maze[conversion(a + 1, b, l, c)] == -1){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }

        /* variant A5 */
        case 5:
            //checking if it isn't a grey cell
            if (maze[conversion(a, b, l, c)] <= 0){
                fprintf(fp_out, "-1\n\n");
                break;
            }
            else{
                //testing its breakability, vertically and horizontally
                if((maze[conversion(a,b-1,l,c)]==0 && maze[conversion(a,b+1,l,c)]==0) || (maze[conversion(a-1,b,l,c)]==0 && maze[conversion(a+1,b,l,c)]==0)){
                    fprintf(fp_out, "1\n\n");
                    break;
                }
                else{
                    fprintf(fp_out, "0\n\n");
                    break;
                }
            }

        /* variant A6 */
        case 6:
            //in case it isn't a white cell
            if (maze[conversion(a, b, l, c)] != 0 || maze[conversion(a1, b1, l, c)] != 0){
                fprintf(fp_out, "0\n\n");
                break;
            }
            //if A6 function returns 1, then we've got two cells in the same room and the opposite for 0.
            if (a6(a, b, a1, b1, l, c, cells_number, maze)){
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
 * Arguments: a, b, a1, b1, l, c, cells_number, maze
 * Returns: 1 if the given cells are in the same room or 0 if they aren't.
 * Side-Effects: the stack is modified.
 *
 * Description: this function implements the A6 variation using the stack 
 * as support. This variant has an additional function due to his increased
 * complexity and extension.
 * 
 *****************************************************************************/

int a6(int a, int b, int a1, int b1, int l, int c, int cells_number, int *maze){
    
    struct Stack *stack = createStack(cells_number);
    int a2 = a, b2 = b;

    /* Creating the data structure (table) */
    unsigned int *id = (unsigned int *)malloc((cells_number + 1) * sizeof(unsigned int));

    /* Initializing the array */
    for (int i = 0; i <= cells_number; i++){
        id[i] = i;
    }

    push(stack,a,b);
    
    /* Doing a while loop testing all the paths from the starting cell to the finishing cell. 
    The loop ends when this two points are connected or, if not, when there isn't more paths available. */
    do{
        a2 = pop_a2(stack);
        b2 = pop_b2(stack);

        /* Testing the possible paths in the 4 directions that allow you to proceed a valid path */
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

        /* Avoiding that the path back off to the same cell by setting the cells already searched to -1 */
        maze[conversion(a2, b2, l, c)] = -1;

    } while (id[conversion(a1, b1, l, c)] != conversion(a, b, l, c) && isEmpty(stack) != 1);

    freeStack(stack);

    /* Freeing the data structure */
    if (id[conversion(a1, b1, l, c)] != conversion(a, b, l, c)){
        free(id);
        return 0;
    }
    else{
        free(id);
        return 1;
    }
}