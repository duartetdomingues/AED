#include "roap.h"
#include <stdbool.h>

int maze_solver(FILE* fp_out,int* maze, int l, int c, int cells_number, int a, int b){
    print_table(maze,l,c);
        
    if(a6(1,1,a,b,l,c,cells_number,maze)){
        printf("Lab,feito\n");
        return 0;
    }

    
    int** adjMatrix=(int**)calloc(cells_number*2,sizeof(int*));
    for(int i=0;i<cells_number*2;i++){
        adjMatrix[i]=(int*)calloc(cells_number*2,sizeof(int));
    }

    //int* visited=init_visited(maze,l,c,cells_number);

    int a1,b1,cell,a2,b2;
    int*p_cell=NULL;
    
    struct Stack* adjMatrix_stack=createStack((cells_number+1)*(cells_number+1));
    int* check=(int*)calloc(cells_number+1,sizeof(int));
    int* flag=(int*)calloc(cells_number+1,sizeof(int));
    
    push(adjMatrix_stack,0,1);
    do{
        
        int *visited=init_visited(maze,l,c,cells_number);
        
        
        a1=pop_a2(adjMatrix_stack);
        b1=pop_b2(adjMatrix_stack);
        
        
        if(check[conversion(a1,b1,l,c)]==1)continue;


        check[0]=1;
        flag[0]=1;
        a2=a1;
        b2=b1;
        
        //printf("%d-%d\n",conversion(a1-1,b1,l,c),visited[conversion(a1-1,b1,l,c)]);

    
        if(flag[conversion(a1-1,b1,l,c)]==1){a2=a1+1;}
        else if(flag[conversion(a1+1,b1,l,c)]==1){a2=a1-1;}
        else if(flag[conversion(a1,b1+1,l,c)]==1){b2=b1-1;}
        else if(flag[conversion(a1,b1-1,l,c)]==1){b2=b1+1;}
        else {printf("deu merda\n\n");}
        if(conversion(a1,b1,l,c)==0){  
            a1=1;
            b1=1;
        }

        
        

        //printf("%d--",conversion(a1,b1,l,c));
        
        visited[conversion(a1,b1,l,c)]=1;
        while((cell=a7(a2,b2,l,c,cells_number,maze,visited,flag))!=0 && check[conversion(a1,b1,l,c)]==0){
            
           
            p_cell=inverted_conversion(cell,l,c);
            push(adjMatrix_stack,p_cell[0],p_cell[1]);
            free(p_cell);
            visited[cell]=1;

            addEdge(adjMatrix,conversion(a1,b1,l,c),cell);
            
            
        }
       
        
        free(visited);
        check[conversion(a1,b1,l,c)]=1;
        
        
        //print_table(adjMatrix,l*c,l*c);
        //print_table(check,l,c);

    }while (!isEmpty(adjMatrix_stack));
    freeStack(adjMatrix_stack);
    free(check);

    //print_matrix(adjMatrix,cells_number,cells_number);
    //free(visited);
    int* visited=init_visited(maze,l,c,cells_number);
    
    
        for(int i=1;i<=(l*c);i++){
            printf("\n%d-",i);
            for(int f=1;f<=(l*c);f++){
                if(adjMatrix[i][f]==1) {printf("%d,",f);}
            }
            printf("\n");
        }

    

    //depthFirstSearch(maze,visited,adjMatrix,l,c,cells_number,a,b);

    //while(all_combination(maze, adjMatrix , l, c, cells_number, a, b)==0){;}
    
    all_combination(maze, adjMatrix , l, c, cells_number, a, b,fp_out);
    
    
    
    free_matrix(adjMatrix,cells_number);

    //print_table(visited,l,c);
 
    
    
    //printf("%d\n",a7(1,1,l,c,cells_number,maze,visited));

    return -2;


}

void print_table(int* table,int l,int c)
{
	int i, j;
	for (i = 1; i <=l; i++) {
		for (j = 1; j <=c; j++) {
            if(table[conversion(i,j,l,c)]>=0){printf(" ");}
			printf("%d|", table[conversion(i,j,l,c)]);
		}
		printf("\n");
	}	
	printf("\n");
}

void print_matrix(int** matrix,int l,int c)
{
	int i, j;
	for (i = 0; i <l; i++) {
		for (j = 0; j <c; j++) {
            //f(matrix[conversion(i,j,l,c)]>=0){printf(" ");}
			printf("%d|", matrix[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
}



void free_matrix(int** matrix,int l)
{
	int i;
	for (i = 0; i <l; i++) {
		free(matrix[i]);
	}
    free(matrix);	
}



int* init_visited(int* maze,int l,int c,int cells_number)
{
	int *visited = calloc((cells_number+1) , sizeof(int));

	int i, j;
	for (i = 0; i <= l; i++) {
		for (j = 0; j <= c; j++) {
			if (maze[conversion(i,j,l,c)] == -1  || variants(5, maze, l, c, cells_number, i, j, 0, 0) == 0) {
				visited[conversion(i,j,l,c)] = -1;
                maze[conversion(i,j,l,c)] = -1;
			} 
            else {
				visited[conversion(i,j,l,c)] = 0;
			}
		}
	}  


    visited[0]=-2;

    /* for (i = 1; i <= l; i++) {
		for (j = 1; j <= c; j++) {
			printf("%d", visited[conversion(i,j,l,c)]);
		}
		printf("\n");
	} 
    printf("\n");*/

    return visited;
}




int all_combination(int* maze, int** adjMatrix , int l, int c, int cells_number, int a, int b,FILE *fp_out){
   
    int** visited=(int**)calloc(cells_number+1,sizeof(int*));
    for(int i=0;i<=cells_number;i++){
        visited[i]=(int*)calloc(cells_number+1,sizeof(int));
    }
    int last_cell=1,cell=1,cell_=0;

    
    
    struct Stack* path_stack=createStack(cells_number); //celulas cinza
    push_a2(path_stack,1);

    search_path(cell,visited,adjMatrix,cells_number,path_stack,maze, a, b, l, c,fp_out);

    
    /* while((cell_=search_path(cell,visited,adjMatrix,cells_number))!=-1){
        
        cell=cell_;
        if(a8(cell,a,b,l,c,cells_number,maze)==1){printf("\nfim");free(visited);return 1;}
        last_cell=cell;
        printf("%d,",cell);
        visited[cell]=1;
    }
    printf("cell=%d,last_cell=%d");
    adjMatrix[last_cell][cell]=0;
    free(visited) */;
    return 0;


}


int search_path(int vertexIndex,int ** visited, int** adjMatrix, int cells_number, struct Stack* path_stack,int* maze,int a,int b,int l,int c,FILE *fp_out) {
   int i=0,flag=0,j=0;

    for(i=0; i <= cells_number; i++) {
       flag=0;

       for(j=0;j<=path_stack->top_a2;j++){
           if(i==path_stack->a2[j]){
               flag=1;
           }
       }
       //printf("%d\n",i);
      if(adjMatrix[vertexIndex][i] == 1  /* && visited[vertexIndex][i] == false */  && flag==0) {
        push_a2(path_stack,i);
        if(a8(i,a,b,l,c,cells_number,maze)==1){
            //printf("");
            fprintf(fp_out,"\nfim:");
            for(j=path_stack->top_a2;j>=0;j--){
                fprintf(fp_out,"%d,",path_stack->a2[j]);
            }
            pop_a2(path_stack);
            //search_path(i,visited,adjMatrix,cells_number,path_stack, maze, a, b, l, c);
            //return 1;
        }else{
            search_path(i,visited,adjMatrix,cells_number,path_stack, maze, a, b, l, c,fp_out);
        }
        
        //visited[vertexIndex][i] = true;
        //search_path(i,visited,adjMatrix,cells_number,path_stack, maze, a, b, l, c);
      }
      
   }
    
    fprintf(fp_out,"\ncaminho:");
    for(j=path_stack->top_a2;j>=0;j--){
           fprintf(fp_out,"%d,",path_stack->a2[j]);
    }
    /* while (!isEmpty(path_stack))
    {   
        printf("%d,",);
    } */
    pop_a2(path_stack);
    
   /* 
    for(int f=0;f<=cells_number+1;f++){
        for(int g=0;g<=cells_number+1;g++){
            visited[f][g]=false;
        }
    }  */
    return -1;
}


void addEdge(int**adjMatrix,int start,int end) {
   adjMatrix[start][end] = 1;
   adjMatrix[end][start] = 1;
}

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
}