#include "roap.h"

int maze_solver(FILE *fp_out, int *maze, int l, int c, int cells_number, int walls, int* walls_array, int a, int b)
{
    printf("dimensão=%dx%d\n",l,c);
    print_table(maze, l, c);

    if (a6(1, 1, a, b, l, c, cells_number, maze))
    {
        return 0;
    }

    if(maze[conversion(a,b,l,c)]!=0)
    {
        return -1;
    }

    bool **adjMatrix = NULL;

    adjMatrix=adj_matrix2(adjMatrix,maze,l,c,cells_number,walls,walls_array);

    int *cost;
    cost = dijkstra(adjMatrix, 0, cells_number, maze,walls,walls_array);
    bool *visited = (bool *)calloc(cells_number+1, sizeof(bool));
    //int *visited = init_visited(maze, l, c, cells_number);
    
    int final_vertex;
    
    for (int i = 1; i < walls + 1; i++)
    {
        printf("custo(%d)=%d\n",i,cost[i]); 
        cost[i]+=maze[walls_array[i]];
    } 

    int final[2]={INT_MAX,INT_MAX};
        
    while ((final_vertex = a7(a, b, l, c, cells_number, maze, visited)) != 0)
    {   
        visited[final_vertex]=1;
        if(final[1]>cost[indexof(final_vertex,walls_array,walls+1)]){
            final[0]=final_vertex;
            final[1]=cost[indexof(final_vertex,walls_array,walls+1)];
        }  
    }
    
    if(final[0]!=INT_MAX && final[1]!=INT_MAX){
        printf("fim:%d,custo:%d\n",final[0],final[1]);
    }
    else printf("Impossible Maze\n");
    free(visited);

    free(cost);
    free_matrix(adjMatrix, walls+1);

    return final[1];
}

bool** adj_matrix2(bool **adjMatrix,int*maze,int l,int c,int cells_number,int walls,int* walls_array){
    int a1, b1, cell, a2, b2;
    int *p_cell = NULL;

    struct Stack *adjMatrix_stack = createStack(walls);
    adjMatrix = (bool **)calloc(walls+1, sizeof(bool *));
    for (int i = 0; i <walls+1; i++)
    {
        adjMatrix[i] = (bool *)calloc(walls+1, sizeof(bool));
    }

    for(int i=0;i<walls+1;i++)
    {
        bool *visited = (bool *)calloc(cells_number+1, sizeof(bool));
        int* k = inverted_conversion(walls_array[i],l,c);
        a1= k[0];
        b1= k[1];
        free(k);

        while ((cell = a7(a1, b1, l, c, cells_number, maze, visited)) != 0 )
        {
            visited[cell] = 1;
            addEdge(adjMatrix, indexof(conversion(a1, b1, l, c),walls_array,walls+1), indexof(cell,walls_array,walls+1));
        }

        free(visited);
        
    }
    freeStack(adjMatrix_stack);
    return adjMatrix;
}



int indexof(int i,int array[],size_t size){
    for(size_t j=0;j<size;j++)
        if(array[j]==i)
            return j;

    return -1;    
}

/************************************************ Dijkstra *************************************************/

int minDistance(int dist[], bool sptSet[], int walls)
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < walls +1; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

int *dijkstra(bool **graph, int src, int cells_number, int *maze,int walls,int* walls_array)
{
    int *dist;
    dist = (int *)calloc(walls+1, sizeof(int)); // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[walls+1]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < walls + 1; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 1; count < walls+1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, walls);

        // Mark the picked vertex as processed
        sptSet[u] = true;


        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 1; v < walls+1; v++)
            
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + maze[walls_array[u]] < dist[v])
                dist[v] = dist[u] + maze[walls_array[u]];
    }

    // print the constructed distance array
    return dist;
}



void print_table(int *table, int l, int c)
{
    if(l>40){return;}
    int i, j;
    for (i = 1; i <= l; i++)
    {
        for (j = 1; j <= c; j++)
        {
            if (table[conversion(i, j, l, c)] >= 0)
            {
                printf(" ");
            }
            if(table[conversion(i, j, l, c)] == 0)printf(" |");
            else printf("%d|", table[conversion(i, j, l, c)]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_matrix(int **matrix, int l, int c)
{
    if(l>90){return;}
    int i, j;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%d|", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(bool **matrix, int l)
{
    int i;
    for (i = 0; i < l; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

bool *init_visited(int *maze, int l, int c, int cells_number)
{
    bool *visited = calloc((cells_number + 1), sizeof(bool));

    for (int i = 0; i <= l; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            if (maze[conversion(i, j, l, c)] == -1)
            {
                visited[conversion(i, j, l, c)] = -1;
            }
            else
            {
                visited[conversion(i, j, l, c)] = 0;
            }
        }
    }

    visited[0] = -2;

    return visited;
}

void addEdge(bool **adjMatrix, int start, int end)
{
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1;
}


/* int** adj_matrix(int **adjMatrix,int*maze,int l,int c,int cells_number){
    int a1, b1, cell, a2, b2;
    int *p_cell = NULL;

    struct Stack *adjMatrix_stack = createStack((cells_number + 1) * (cells_number + 1));
    int *check = (int *)calloc(cells_number + 1, sizeof(int));
    int *flag = (int *)calloc(cells_number + 1, sizeof(int));
    adjMatrix = (int **)calloc(cells_number + 1, sizeof(int *));
    for (int i = 0; i <= cells_number; i++)
    {
        adjMatrix[i] = (int *)calloc(cells_number+1, sizeof(int));
    }

    push(adjMatrix_stack, 0, 1);
    do
    {

        int *visited = init_visited(maze, l, c, cells_number);

        a1 = pop_a2(adjMatrix_stack);
        b1 = pop_b2(adjMatrix_stack);

        if (check[conversion(a1, b1, l, c)] == 1)
            continue;

        check[0] = 1;
        flag[0] = 1;
        a2 = a1;
        b2 = b1;

        // printf("%d-%d\n",conversion(a1-1,b1,l,c),visited[conversion(a1-1,b1,l,c)]);

        if (flag[conversion(a1 - 1, b1, l, c)] == 1)
        {
            a2 = a1 + 1;
        }
        else if (flag[conversion(a1 + 1, b1, l, c)] == 1)
        {
            a2 = a1 - 1;
        }
        else if (flag[conversion(a1, b1 + 1, l, c)] == 1)
        {
            b2 = b1 - 1;
        }
        else if (flag[conversion(a1, b1 - 1, l, c)] == 1)
        {
            b2 = b1 + 1;
        }
        else
        {
            printf("deu merda\n\n");
        }
        if (conversion(a1, b1, l, c) == 0)
        {
            a1 = 1;
            b1 = 1;
        }

        // printf("%d--",conversion(a1,b1,l,c));

        visited[conversion(a1, b1, l, c)] = 1;
        while ((cell = a7(a2, b2, l, c, cells_number, maze, visited, flag)) != 0 && check[conversion(a1, b1, l, c)] == 0)
        {

            p_cell = inverted_conversion(cell, l, c);
            push(adjMatrix_stack, p_cell[0], p_cell[1]);
            free(p_cell);
            visited[cell] = 1;

            addEdge(adjMatrix, conversion(a1, b1, l, c), cell);
        }

        free(visited);
        check[conversion(a1, b1, l, c)] = 1;

        // print_table(adjMatrix,l*c,l*c);
        // print_table(check,l,c);

    } while (!isEmpty(adjMatrix_stack));
    freeStack(adjMatrix_stack);
    free(check);
    free(flag);
    return adjMatrix;
} */

/* void displayVertex(int vertexIndex) {
   printf("%c ",lstVertices[vertexIndex]->label);
} */

/*void depthFirstSearch(int* maze,int * visited, int l, int c, int cells_number, int a, int b) {
   //int i;

   //mark first node as visited

   //int* vertex=inverted_conversion(a7(1,1,l,c,cells_number,maze,visited));

   //int a1=vertex[0],a2=vertex[1];
   int a1,b1;
   //free(vertex);
   visited[conversion(1,1,l,c)]=1;

   //display the vertex
   //displayVertex(0);

   //push vertex index in stack
   struct Stack* grey_stack = createStack(cells_number+1);
   push(grey_stack,1,1);

   while(!isEmpty(grey_stack)) {
      //get the unvisited vertex of vertex which is at top of the stack
      //int unvisitedVertex = search_path(peek());
      int* cell=  _a7(grey_stack->a2[grey_stack->top_a2],grey_stack->b2[grey_stack->top_b2],l,c,cells_number,maze,visited);
      a1=cell[0];
      b1=cell[1];
      free(cell);
      //no adjacent vertex found
      if(a1==0 && b1==0) {
         a1=pop_a2(grey_stack);
         b1=pop_b2(grey_stack);
         printf("%d,%d\n",a1,b1);
         visited[conversion(a1,b1,l,c)]=0;
         return;
      } else {
        printf("%d,%d\n",a1,b1);
        maze[conversion(a1,b1,l,c)]=8;
        //visited[conversion(a1,b1,l,c)] = 1;
         //displayVertex(unvisitedVertex);
        push(grey_stack,a1,b1);
      }
   }

   //stack is empty, search is complete, reset the visited flag
   //for(i = 0;i < vertexCount;i++) {
   //   lstVertices[i]->visited = false;
   //}
}
*/
/*
void depthFirstSearch(int* maze,int * visited, int** adjMatrix , int l, int c, int cells_number, int a, int b) {
   int i,a1,b1;
   int* p_cell;

   //mark first node as visited
   visited[conversion(1,1,l,c)]=1;

   //display the vertex
   //displayVertex(0);
   printf("%d, ",1);

   //push vertex index in stack
   struct Stack* grey_stack = createStack(cells_number+1);
   push(grey_stack,1,1);

   int unvisitedVertex=1,last_cell;

   while(!isEmpty(grey_stack)) {
      //get the unvisited vertex of vertex which is at top of the stack
      //last_cell=unvisitedVertex;
      unvisitedVertex = search_path(conversion(grey_stack->a2[grey_stack->top_a2],grey_stack->b2[grey_stack->top_b2],l,c),visited,adjMatrix,cells_number);


      //no adjacent vertex found
      if(unvisitedVertex == -1 ) {
         pop_a2(grey_stack);
         pop_b2(grey_stack);
         printf("\n");
      } else {

        //if(adjMatrix[unvisitedVertex][last_cell]==0){
        printf("%d, ",unvisitedVertex);
         //displayVertex(unvisitedVertex);
         p_cell=inverted_conversion(unvisitedVertex,l,c);
         push(grey_stack,p_cell[0],p_cell[1]);
         free(p_cell);
         visited[unvisitedVertex] = true;
         //push(grey_stack,a1,b1);
         //push(unvisitedVertex);
        // }
        //else{
        //    adjMatrix[conversion(grey_stack->a2[grey_stack->top_a2],grey_stack->b2[grey_stack->top_b2],l,c)][unvisitedVertex]==0;
        //}

      }
   }

   //stack is empty, search is complete, reset the visited flag
   print_table(visited,l,c);
   for(i = 0; i <= cells_number; i++) {
      visited[i] = false;
   }
}*/