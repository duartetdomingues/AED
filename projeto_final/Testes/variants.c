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

int variants(int variant, int* maze, int l, int c, int cells_number, int a, int b, int a1, int b1){
    switch (variant){
        /* variant A1 */
        case 1:
            return maze[conversion(a, b, l, c)];

        /* variant A2 */
        case 2:
            //exploring the neighborhood of the cell
            if (maze[conversion(a, b - 1, l, c)] == 0 || maze[conversion(a, b + 1, l, c)] == 0 || maze[conversion(a - 1, b, l, c)] == 0 || maze[conversion(a + 1, l, b, c)] == 0){
                return 1;
            }
            else{
                return 0;
            }

        /* variant A3 */
        case 3:
            //exploring the neighborhood of the cell 
            if (maze[conversion(a, b - 1, l, c)] > 0 || maze[conversion(a, b + 1, l, c)] > 0 || maze[conversion(a - 1, b, l, c)] > 0 || maze[conversion(a + 1, b, l, c)] > 0){
                return 1;
            }
            else{
                return 0;
            }

        /* variant A4 */
        case 4:
            //exploring the neighborhood of the cell 
            if (maze[conversion(a, b - 1, l, c)] == -1 || maze[conversion(a, b + 1, l, c)] == -1 || maze[conversion(a - 1, b, l, c)] == -1 || maze[conversion(a + 1, b, l, c)] == -1){
                return 1;
            }
            else{
                return 0;
            }

        /* variant A5 */
        case 5:
            //checking if it isn't a grey cell
            if (maze[conversion(a, b, l, c)] <= 0){
                return -1;
            }
            else{
                //testing its breakability, vertically and horizontally
                if((maze[conversion(a,b-1,l,c)]==0 && maze[conversion(a,b+1,l,c)]==0) || (maze[conversion(a-1,b,l,c)]==0 && maze[conversion(a+1,b,l,c)]==0)){
                    return 1;
                }
                else{
                    return 0;
                }
            }

        /* variant A6 */
        case 6:
            //in case it isn't a white cell
            if (maze[conversion(a, b, l, c)] != 0 || maze[conversion(a1, b1, l, c)] != 0){
                return 0;
            }
            //if A6 function returns 1, then we've got two cells in the same room and the opposite for 0.
            if (a6(a, b, a1, b1, l, c, cells_number, maze)){
                return 1;
            }
            else{
                return 0;
            }
        

        /* variant A6 */
            
    }
    return 0;
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

    if (maze[conversion(a, b, l, c)] > 0 ){
                return -1;
            }
    
    struct Stack *white_stack = createStack(cells_number+1);
    int a2 = a, b2 = b;

    /* Creating the data structure (table) */
    unsigned int *id = (unsigned int *)malloc((cells_number + 1) * sizeof(unsigned int));
    char* check=(char*)malloc((cells_number + 1) * sizeof(char));

    /* Initializing the array */
    for (int i = 0; i <= cells_number; i++){
        id[i] = i;
        check[i] = 0;
    }

    push(white_stack,a,b);
    
    /* Doing a while loop testing all the paths from the starting cell to the finishing cell. 
    The loop ends when this two points are connected or, if not, when there isn't more paths available. */
    do{
        a2 = pop_a2(white_stack);
        b2 = pop_b2(white_stack);

        /* Testing the possible paths in the 4 directions that allow you to proceed a valid path */
        if (maze[conversion(a2, b2 - 1, l, c) == 0 && check[conversion(a2, b2 -1, l, c)]] == 0){
            id[conversion(a2, b2 - 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 - 1);
        }
        if (maze[conversion(a2, b2 + 1, l, c)] == 0 && check[conversion(a2, b2 + 1, l, c)] == 0){
            id[conversion(a2, b2 + 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 + 1);;
        }

        if (maze[conversion(a2 - 1, b2, l, c)] == 0 && check[conversion(a2 - 1, b2, l, c)] == 0){
            id[conversion(a2 - 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 - 1, b2);
        }
        if (maze[conversion(a2 + 1, b2, l, c)] == 0 && check[conversion(a2 + 1, b2, l, c)] == 0){
            id[conversion(a2 + 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 + 1, b2);
        }

        /* Avoiding that the path back off to the same cell by setting the cells already searched to -1 */
        check[conversion(a2, b2, l, c)] = 1;

    } while (id[conversion(a1, b1, l, c)] != conversion(a, b, l, c) && isEmpty(white_stack) != 1);

    freeStack(white_stack);
    free(check);

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

/******************************************************************************
 * a7()
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

int* _a7(int a, int b, int l, int c, int cells_number, int *maze,int *visited){
    
    struct Stack *white_stack = createStack(cells_number+1);
    int a2 = a, b2 = b;
    int *cell=(int*)calloc(2,sizeof(int));

    /* Creating the data structure (table) */
    unsigned int *id = (unsigned int *)malloc((cells_number + 1) * sizeof(unsigned int));
    char* check=(char*)malloc((cells_number + 1) * sizeof(char));

    /* Initializing the array */
    for (int i = 0; i <= cells_number; i++){
        id[i] = i;
        check[i] = 0;
    }

    push(white_stack,a,b);
    
    /* Doing a while loop testing all the paths from the starting cell to the finishing cell. 
    The loop ends when this two points are connected or, if not, when there isn't more paths available. */
    do{
        a2 = pop_a2(white_stack);
        b2 = pop_b2(white_stack);

        if (maze[conversion(a2, b2 - 1, l, c)] > 0  && visited[conversion(a2, b2 - 1, l, c)]==0){
            freeStack(white_stack);
            free(check);
            free(id);
            //visited[conversion(a2, b2, l,c)] = 1;
            visited[conversion(a2, b2-1, l,c)] = 1;
            cell[0]=a2;
            cell[1]=b2-1;
            return cell;
        }
        if (maze[conversion(a2, b2 + 1, l, c)] > 0 && visited[conversion(a2, b2 + 1, l, c)]==0){
            freeStack(white_stack);
            free(check);
            free(id);
            //visited[conversion(a2, b2, l,c)] = 1;
            visited[conversion(a2, b2 + 1, l,c)] = 1;
            cell[0]=a2;
            cell[1]=b2+1;
            return cell;
        }

        if (maze[conversion(a2 - 1, b2, l, c)] > 0 && visited[conversion(a2 -1 ,b2 , l, c)]==0){
            freeStack(white_stack);
            free(check);
            free(id);
            //visited[conversion(a2, b2, l,c)] = 1;
            visited[conversion(a2-1, b2, l,c)] = 1;
            cell[0]=a2-1;
            cell[1]=b2;
            return cell;
        }
        if (maze[conversion(a2 + 1, b2, l, c)] > 0 && visited[conversion(a2 + 1, b2 , l, c)]==0){
            freeStack(white_stack);
            free(check);
            free(id);
            //visited[conversion(a2, b2, l,c)] = 1;
            visited[conversion(a2+1, b2, l,c)] = 1;
            cell[0]=a2+1;
            cell[1]=b2;
            return cell;
        }
        

        /* Testing the possible paths in the 4 directions that allow you to proceed a valid path */
        if (maze[conversion(a2, b2 - 1, l, c) ]== 0 && check[conversion(a2, b2 -1, l, c)] == 0){
            id[conversion(a2, b2 - 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 - 1);
        }
        if (maze[conversion(a2, b2 + 1, l, c)] == 0 && check[conversion(a2, b2 + 1, l, c)] == 0){
            id[conversion(a2, b2 + 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 + 1);;
        }

        if (maze[conversion(a2 - 1, b2, l, c)] == 0 && check[conversion(a2 - 1, b2, l, c)] == 0){
            id[conversion(a2 - 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 - 1, b2);
        }
        if (maze[conversion(a2 + 1, b2, l, c)] == 0 && check[conversion(a2 + 1, b2, l, c)] == 0){
            id[conversion(a2 + 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 + 1, b2);
        }

        /* Avoiding that the path back off to the same cell by setting the cells already searched to -1 */
        check[conversion(a2, b2, l, c)] = 1;

    } while (isEmpty(white_stack) != 1);

    freeStack(white_stack);
    free(check);
    free(id);
    printf("nenhuma cinza\n");
    cell[0]=0;
    cell[1]=0;
    return cell;
    /* Freeing the data structure */
}



int a7(int a, int b, int l, int c, int cells_number, int *maze,int *visited,int *flag){
    
    struct Stack *white_stack = createStack(cells_number+1);
    int a2 = a, b2 = b;

    /* Creating the data structure (table) */
    unsigned int *id = (unsigned int *)malloc((cells_number + 1) * sizeof(unsigned int));
    int* check=(int*)malloc((cells_number + 1) * sizeof(int));

    /* Initializing the array */
    for (int i = 0; i <= cells_number; i++){
        id[i] = i;
        check[i] = 0;
    }

    push(white_stack,a,b);
    
    /* Doing a while loop testing all the paths from the starting cell to the finishing cell. 
    The loop ends when this two points are connected or, if not, when there isn't more paths available. */
    do{
        a2 = pop_a2(white_stack);
        b2 = pop_b2(white_stack);

        
        /* Testing the possible paths in the 4 directions that allow you to proceed a valid path */
        if (maze[conversion(a2, b2 - 1, l, c)] == 0 && check[conversion(a2, b2 - 1, l, c)] == 0){
            id[conversion(a2, b2 - 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 - 1);
        }
        if (maze[conversion(a2, b2 + 1, l, c)] == 0 && check[conversion(a2, b2 + 1, l, c)] == 0){
            id[conversion(a2, b2 + 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 + 1);;
        }

        if (maze[conversion(a2 - 1, b2, l, c)] == 0 && check[conversion(a2 - 1, b2, l, c)] == 0){
            id[conversion(a2 - 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 - 1, b2);
        }
        if (maze[conversion(a2 + 1, b2, l, c)] == 0 && check[conversion(a2 + 1, b2, l, c)] == 0){
            id[conversion(a2 + 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 + 1, b2);
        }

        if (maze[conversion(a2, b2 - 1, l, c)] > 0  && check[conversion(a2, b2 - 1, l, c)]==0 && visited[conversion(a2, b2-1 , l, c)]==0){
            check[conversion(a2, b2 - 1, l, c)]=1;
            freeStack(white_stack);
            free(check);
            free(id);
            flag[conversion(a2, b2, l,c)] = 1;
            //visited[conversion(a2, b2-1, l,c)] = 8;
            return conversion(a2, b2-1, l,c);
        }
        if (maze[conversion(a2, b2 + 1, l, c)] > 0 && check[conversion(a2, b2 + 1, l, c)]==0 && visited[conversion(a2, b2+1 , l, c)]==0){
            check[conversion(a2, b2 + 1, l, c)]=1;
            freeStack(white_stack);
            free(check);
            free(id);
            flag[conversion(a2, b2, l,c)] = 1;
            //visited[conversion(a2, b2 + 1, l,c)] = 8;
            return conversion(a2, b2 + 1, l,c);
        }

        if (maze[conversion(a2 - 1, b2, l, c)] > 0 && check[conversion(a2 -1 ,b2 , l, c)]==0 && visited[conversion(a2 - 1, b2 , l, c)]==0){
            check[conversion(a2-1, b2, l, c)]=1;
            freeStack(white_stack);
            free(check);
            free(id);
            flag[conversion(a2, b2, l,c)] = 1;
            //visited[conversion(a2-1, b2, l,c)] = 8;
            return conversion(a2-1, b2, l,c);
        }
        if (maze[conversion(a2 + 1, b2, l, c)] > 0 && check[conversion(a2 + 1, b2 , l, c)]==0 && visited[conversion(a2 + 1, b2 , l, c)]==0){
            
            check[conversion(a2 + 1, b2 , l, c)]=1;
            freeStack(white_stack);
            free(check);
            free(id);
            flag[conversion(a2, b2, l,c)] = 1;

            //visited[conversion(a2+1, b2, l,c)] = 8;

            return conversion(a2+1, b2, l,c);
        }

        /* Avoiding that the path back off to the same cell by setting the cells already searched to -1 */
        check[conversion(a2, b2, l, c)] = 1;


    } while (isEmpty(white_stack) != 1);
    freeStack(white_stack);
    for(int i=0;i<=cells_number;i++){
        if(visited[i]==1)
            check[i]=8;
    }
    //printf("\n");print_table(check,l,c);//print_table(maze,l,c);
    free(check);
    free(id);
    
    return 0;
    /* Freeing the data structure */
}

int a8(int cell,int a1, int b1, int l, int c, int cells_number, int *maze){
    
    //esta a checkar atras tambem == pouco eficiente

    int *p_cell=inverted_conversion(cell,l,c);
    int a=p_cell[0],b=p_cell[1];
    free(p_cell);
            

    struct Stack *white_stack = createStack(cells_number+1);
    int a2 = a, b2 = b;

    /* Creating the data structure (table) */
    unsigned int *id = (unsigned int *)malloc((cells_number + 1) * sizeof(unsigned int));
    int* check=(int*)malloc((cells_number + 1) * sizeof(int));

    /* Initializing the array */
    for (int i = 0; i <= cells_number; i++){
        id[i] = i;
        check[i] = 0;
    }

    push(white_stack,a,b);
    
    /* Doing a while loop testing all the paths from the starting cell to the finishing cell. 
    The loop ends when this two points are connected or, if not, when there isn't more paths available. */
    do{
        a2 = pop_a2(white_stack);
        b2 = pop_b2(white_stack);
        

        /* Testing the possible paths in the 4 directions that allow you to proceed a valid path */
        if (maze[conversion(a2, b2 - 1, l, c)] == 0 && check[conversion(a2, b2 - 1, l, c)] == 0){
            id[conversion(a2, b2 - 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 - 1);
        }
        if (maze[conversion(a2, b2 + 1, l, c)] == 0 && check[conversion(a2, b2 + 1, l, c)] == 0){
            id[conversion(a2, b2 + 1, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2, b2 + 1);;
        }

        if (maze[conversion(a2 - 1, b2, l, c)] == 0 && check[conversion(a2 - 1, b2, l, c)] == 0){
            id[conversion(a2 - 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 - 1, b2);
        }
        if (maze[conversion(a2 + 1, b2, l, c)] == 0 && check[conversion(a2 + 1, b2, l, c)] == 0){
            id[conversion(a2 + 1, b2, l, c)] = conversion(a, b, l, c);
            push(white_stack, a2 + 1, b2);
        }

        /* Avoiding that the path back off to the same cell by setting the cells already searched to -1 */
        check[conversion(a2, b2, l, c)] = 1;
        

    } while (isEmpty(white_stack) != 1 && id[conversion(b1, a1, l, c)] != conversion(a, b, l, c));
    freeStack(white_stack);
    
    free(check);

    if (id[conversion(a1, b1, l, c)] != conversion(a, b, l, c)){
        free(id);
        return 0;
    }
    else{
        free(id);
        return 1;
    }
    /* Freeing the data structure */
}