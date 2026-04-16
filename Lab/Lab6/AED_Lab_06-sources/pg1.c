
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *OpenFile(char *name, char *mode);

int main(int argc, char **argv){

    FILE *fp_in = NULL, *fp_out = NULL;
    char *filename_in = NULL,*filename_out = NULL;
    int point, N=0, E=0, G_N=0, G=0, **adj_matrix, **edge_array, i,j,k;

    if (argc != 2 || strstr(argv[1], ".adj") == NULL){
        exit(EXIT_FAILURE);
    }

    filename_in = argv[1];

    for (i = 0; i <= strlen(filename_in); i++){
        if (filename_in[i] == '.'){
            point = i;
        }
    }

    filename_out = (char *)calloc((point + strlen(".edge") + 1), sizeof(char));
    strncpy(filename_out, filename_in, point);
    strcat(filename_out, ".edge");

    fp_in=OpenFile(filename_in,"r");

    fscanf(fp_in,"%d",&N);

    adj_matrix=(int**)malloc(N*sizeof(int*));

    for(i=0;i<N;i++){
        adj_matrix[i]=(int*)calloc(N,sizeof(int));
        for (j = 0; j < N; j++){
            fscanf(fp_in,"%d", &adj_matrix[i][j]);
             if(adj_matrix[i][j] != 0)E++;
        }  
    }
    fclose(fp_in);
    E=E/2;

    edge_array=(int**)malloc(E*sizeof(int*));
    for(i=0,k=0; i<N && k<E; i++){ 
        G_N=0;
        for (j = i+1; j < N && k<E; j++){
            if(adj_matrix[i][j] != 0){
                edge_array[k]=(int*)calloc(3,sizeof(int));
                edge_array[k][0]=i;
                edge_array[k][1]=j;
                edge_array[k][2]=adj_matrix[i][j];
                G_N++;
                k++; 
            }
        }
        if(G_N>G){
            G=G_N;
        } 
    }

    printf("Densidade=%.2f\nGrau Máximo=%d\n",(float)2*E/N,G);


    fp_out=OpenFile(filename_out,"w");

    fprintf(fp_out,"%d %d\n",N,E);

    for(i=0; i<E ; i++){
        fprintf(fp_out,"%d %d %d\n", edge_array[i][0], edge_array[i][1], edge_array[i][2]);
    }
    fclose(fp_out);
    free(filename_out);
    for(i=0;i<N;i++){
        free(adj_matrix[i]);
    }
    free(adj_matrix);
    for(i=0;i<E;i++){
        free(edge_array[i]);
    }
    free(edge_array);
    return EXIT_SUCCESS;
}

FILE *OpenFile(char *name, char *mode)
{
   FILE *fp=NULL;

   fp = fopen(name, mode);
   if (fp == NULL) {
      fprintf(stderr, "Error: Unable to open file '%s'\n.", name);
      exit(EXIT_FAILURE);
   }
   return fp;
}