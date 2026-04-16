/************************************************ Combinações *************************************************/

#include "roap.h"
#include <stdbool.h>
#include <limits.h>

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