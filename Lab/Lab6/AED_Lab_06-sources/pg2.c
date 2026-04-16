
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

FILE *OpenFile(char *name, char *mode);

int main(int argc, char **argv){

    FILE *fp_in = NULL, *fp_out = NULL;
    char *filename_in = NULL,*filename_out = NULL;
    int point, N, E, i, j, node_1, node_2, weight,length;
    LinkedList *aux = initLinkedList(),*aux1 = initLinkedList();
    LinkedList **adj_list=NULL;
    Node_Type *Node_1=NULL,*Node_2=NULL;
    int err=0;


    if (argc != 2 || strstr(argv[1], ".edge") == NULL){
        exit(EXIT_FAILURE);
    }

    filename_in = argv[1];

    for (i = 0; i <= strlen(filename_in); i++){
        if (filename_in[i] == '.'){
            point = i;
        }
    }

    filename_out = (char *)calloc((point + strlen(".ladj") + 1), sizeof(char));
    strncpy(filename_out, filename_in, point);
    strcat(filename_out, ".ladj");

    fp_in=OpenFile(filename_in,"r");

    fscanf(fp_in,"%d %d", &N, &E);

    adj_list=(LinkedList **)calloc( N, sizeof(*adj_list));
    for (i = 0; i < N; i++)
                  adj_list[i] = initLinkedList();

    for(i=0;i<E;i++){
        Node_1=(Node_Type*)malloc(sizeof(Node_Type));
        Node_2=(Node_Type*)malloc(sizeof(Node_Type));
        fscanf(fp_in,"%d %d %d", &node_1, &node_2, &weight);
        Node_1->Vertix=node_1;
        Node_2->Vertix=node_2;
        Node_1->Weight=Node_2->Weight=weight;
        adj_list[node_1] = insertSortedLinkedList(adj_list[node_1], (Item) Node_2, comparisonItemFnt, &err);
        adj_list[node_2] = insertSortedLinkedList(adj_list[node_2], (Item) Node_1, comparisonItemFnt, &err); 
    }
    fclose(fp_in);

    fp_out=OpenFile(filename_out,"w");

    
    fprintf(fp_out,"%d\n",N);

    for(i=0;i<N;i++){
        aux=adj_list[i];
        length = lengthLinkedList(adj_list[i]);
        for(j=0;j<length;aux = getNextNodeLinkedList(aux),j++){
            aux1 = getItemLinkedList(aux);
            fprintf(fp_out,"%d:%d ",aux1->Vertix,aux1->Weight);
        }  
        fprintf(fp_out,"-1\n");
    }
    fclose(fp_out);
    free(filename_out);
    for (i = 0; i < N; i++)
        freeLinkedList(adj_list[i],freeItemFnt);
    free(adj_list);
    return EXIT_SUCCESS;
}


FILE *OpenFile(char *name, char *mode)
{
   FILE *fp;

   fp = fopen(name, mode);
   if (fp == NULL) {
      fprintf(stderr, "Error: Unable to open file '%s'\n.", name);
      exit(EXIT_FAILURE);
   }
   return fp;
}
