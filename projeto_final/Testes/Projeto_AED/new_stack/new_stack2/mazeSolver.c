#include "roap.h"
#include "LinkedList.h"

int maze_solver(FILE *fp_out, int *maze, int l, int c, int cells_number, int walls, int *walls_array, int a, int b)
{
    int i, rooms;

    /* for (i = 0; i < walls; i++)
        printf("%d,", walls_array[i]);

    printf("\n"); */

    // print_table(maze, l, c);

    //checkar se as casas de partida e chegada são válidas
    if (maze[conversion(a, b, l, c)] != 0 || maze[conversion(1, 1, l, c)] != 0)
    {
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }

    /*LinkedList **adjList=NULL;
    
    //tentar fazer alocação dinâmica do vetor de listas, adicionando linhas conforme necessário
     adjList = (LinkedList **)calloc(walls*1.25, sizeof(LinkedList*));

    for (i = 0; i <walls * 1.25; i++)
        adjList[i] = NULL;//initLinkedList(); */

    rooms = make_rooms(maze, l, c, cells_number, walls, walls_array);

    // se a casa de chegada ou de partida tiverem numa sala blindada a -1 (nesse caso não terão sido pintadas)
    if (maze[conversion(a, b, l, c)] == 0 || maze[conversion(1, 1, l, c)] == 0)
    {
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }

    if (maze[conversion(a, b, l, c)] == maze[conversion(1, 1, l, c)])
    {
        fprintf(fp_out, "%d\n", 0);
        return 0;
    }
    int final_vertix = abs(maze[conversion(a, b, l, c)]) - 2;
    int inicial_vertix = abs(maze[conversion(1, 1, l, c)]) - 2;
    

    LinkedList** adjList;
    adjList = fillAdjList(maze, l, c,  walls, walls_array, a, b, rooms);

    /* LinkedList *aux;
    for (i = 0; i < rooms; i++)
    {
        aux = adjList[i];
        while (aux != NULL)
        {
            printf("%d:%d(%d)  ", aux->Vertix, aux->Wall,aux->Weight);
            aux = aux->next;
        }
        printf("-1\n");
    } */
    printf("%d-%d-%d-%d\n",inicial_vertix,final_vertix,rooms,walls);

    free(maze);
    
    
    /* LinkedList **adjList;
    adjList = fillAdjList(maze, l, c, walls, walls_array, a, b, rooms); */

    // print_table(maze, l, c);

    /*int length;
    LinkedList *aux;

    for (i = 0; i < rooms; i++)
    {
        aux = adjList[i];
        while (aux != NULL)
        {
            printf("%d:%d(%d)  ", aux->Vertix, aux->Weight,maze[aux->Weight]);
            aux = aux->next;
        }
        printf("-1\n");
    } */

    int **result, *cost, *parent;
    result = dijkstra(adjList, inicial_vertix, rooms,final_vertix);
    // return 0;

    cost = result[0];
    parent = result[1];
    free(result);

    int final_cost = cost[final_vertix];

    if (final_cost == INT_MAX)
    {
        fprintf(fp_out, "%d\n", -1);
        return -1;
    }
    // printSolution(fp_out,maze,l,c,adjList,cost, rooms, parent,final_vertix);
    fprintf(fp_out, "%d\n", cost[final_vertix]);
    /* int k=0;
    for(int j=final_vertix;j!=-1;j=parent[j])
        k++;
    fprintf(fp_out,"%d\n",--k);  */
    printPath(fp_out, l, c, adjList, parent, final_vertix, 1);

    // printf("custo=%d || sala final =%d || Total salas=%d\n",final_cost,final_vertix,rooms);

    for (i = 0; i < rooms; i++)
        freeLinkedList(adjList[i]);

    free(adjList);
    free(cost);
    free(parent);

    return final_cost;
}

int make_rooms(int *maze, int l, int c, int cells_number, int walls, int *walls_array)
{
    int a1, b1, k = 0, *coord;
    Stack *white_stack=NULL, *final=NULL;
    //LinkedList *Node;

    for (a1 = 1; a1 <= l; a1++)
    {
        for(b1=1;b1 <= c;b1++){
            if (maze[conversion(a1, b1 - 1, l, c)] == 0)
            {
                push(&white_stack,&final, a1, b1 - 1);
                explore_room(maze,&white_stack,&final, k, l, c);
                k++;
            }
        }
        /*coord = inverted_conversion(walls_array[i], l, c);
        a1 = coord[0];
        b1 = coord[1];
        free(coord);

        
        if (maze[conversion(a1, b1 + 1, l, c)] == 0)
        {
            push(&white_stack,&final, a1, b1 + 1);
            explore_room(maze,&white_stack,&final, k, l, c);
            k++;
        } */
        
        /* if((maze[conversion(a1, b1 - 1, l, c)]< -1 && maze[conversion(a1, b1 + 1, l, c)]<-1) && (maze[conversion(a1, b1 - 1, l, c)] != maze[conversion(a1, b1 + 1, l, c)])){
            add_edge(adjList,maze,maze[conversion(a1, b1 - 1, l, c)],maze[conversion(a1, b1 + 1, l, c)], conversion(a1, b1 , l, c));
        } */

        /* if (maze[conversion(a1 - 1, b1, l, c)] == 0)
        {
            push(&white_stack,&final, a1 - 1, b1);
            explore_room(maze, &white_stack,&final, k, l, c);
            k++;
        }
        if (maze[conversion(a1 + 1, b1, l, c)] == 0)
        {
            push(&white_stack,&final, a1 + 1, b1);
            explore_room(maze, &white_stack,&final, k, l, c);
            k++;
        } */
       
        /* if((maze[conversion(a1 - 1, b1, l, c)]<-1 && maze[conversion(a1 + 1, b1, l, c)]<-1) && (maze[conversion(a1- 1, b1 , l, c)] != maze[conversion(a1 + 1, b1, l, c)])){
            add_edge(adjList,maze,maze[conversion(a1 - 1, b1, l, c)],maze[conversion(a1 + 1, b1, l, c)],conversion(a1, b1 , l, c));
        } */
    }
    
    return k;
}

void explore_room(int *maze, Stack **stack,Stack **final, int k, int l, int c)
{
    Stack *aux;
    int a, b;
    do
    {
        a = pop_a(*stack);
        b = pop_b(*stack);
        aux = *stack;
        *stack = (*stack)->next;
        free(aux);

        /* Testing the possible paths in the 4 directions that allow you to proceed a valid path */
        if (maze[conversion(a, b - 1, l, c)] == 0)
        {
            push(stack,final, a, b - 1);
        }
        if (maze[conversion(a - 1, b, l, c)] == 0)
        {
            push(stack,final, a - 1, b);
        }
        if (maze[conversion(a, b + 1, l, c)] == 0)
        {
            push(stack,final, a, b + 1);
        }
        if (maze[conversion(a + 1, b, l, c)] == 0)
        {
            push(stack,final, a + 1, b);
        }
        maze[conversion(a, b, l, c)] = 0 - (k + 2);

    } while (isEmpty(*stack) != 1);
    
}
int a5(int* maze, int l, int c, int a, int b)
{
    if (maze[conversion(a, b, l, c)] <= 0)
    {
        return -1;
    }
    else
    {
        // testing its breakability, vertically and horizontally
        if ((maze[conversion(a, b - 1, l, c)] == 0 && maze[conversion(a, b + 1, l, c)] == 0) || (maze[conversion(a - 1, b, l, c)] == 0 && maze[conversion(a + 1, b, l, c)] == 0))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void printPath(FILE *fp_out, int l, int c, LinkedList **adjList, int *parent, int j, int k)
{

    // Base Case : If j is source
    if (parent[j] == -1)
    {
        fprintf(fp_out, "%d\n", --k);
        return;
    }
    k++;
    printPath(fp_out, l, c, adjList, parent, parent[j], k);

    LinkedList *Node = get_vertix(adjList[j], parent[j],-1,INT_MAX);

    int *coord = inverted_conversion(Node->Weight, l, c);

    fprintf(fp_out, "%d %d %d\n", coord[0], coord[1],Node->Weight);
    free(coord);
}
/* int *init_visited(int *maze, int l, int c, int cells_number)
{
    int *visited = calloc((cells_number + 1), sizeof(bool));

    for (int i = 0; i <= l; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            if (maze[conversion(i, j, l, c)] == -1 || variants(5, maze, l, c, cells_number, i, j, 0, 0) == 0)
            {
                visited[conversion(i, j, l, c)] = -1;
                maze[conversion(i, j, l, c)] = -1;
            }
            else
            {
                visited[conversion(i, j, l, c)] = 0;
            }
        }
    }

    visited[0] = -2;

    return visited;
} */
// A utility function to print
// the constructed distance
// array
/* void printSolution(FILE *fp_out,int *maze,int l,int c,LinkedList** adjList ,int* dist, int V, int* parent, int final_vertix)
{
    fprintf(fp_out,"%d\n",dist[final_vertix]);
    printPath(fp_out,maze,l,c,adjList,parent,final_vertix,0);
} */

void print_table(int *table, int l, int c)
{
    int i, j;
    for (i = 1; i <= 10; i++)
    {
        for (j = 1; j <= 10; j++)
        {
            if (table[conversion(i, j, l, c)] >= 0)
            {
                printf(" ");
            }
            printf("%d ", table[conversion(i, j, l, c)]);
        }
        printf("\n");
    }
    printf("\n");
}

/* void print_matrix(int **matrix, int l, int c)
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            // f(matrix[conversion(i,j,l,c)]>=0){printf(" ");}
            printf("%d|", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(int **matrix, int l)
{
    int i;
    for (i = 0; i < l; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}*/