#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


int main(int argc, char *argv[]){

    FILE *fp_in = NULL;
    char *filename_in;
    int option;
    int l, c, a, b, a1, b1, d, e, walls, num_cells, cell, conversion, variant;

    if( argc!=3 || strcmp(argv[1],"-s")!= 0 || strstr(argv[2], ".in1") == NULL){
        exit(EXIT_FAILURE);
    }

    filename_in=argv[2];
    
    /* printf("%s\n",filename_in);*/
    if((fp_in = fopen(filename_in, "r")) == NULL) exit(EXIT_FAILURE);

    while(fscanf(fp_in,"%d %d", &l, &c)==2 && !feof(fp_in)){

    //fscanf(fp_in,"%d %d", &l, &c);
    num_cells = l*c;
    // 1 1 A1
    fscanf(fp_in,"%d %d A%d", &a, &b, &variant);
    if(variant==6){
        fscanf(fp_in,"%d %d", &a1, &b1);
    }
    fscanf(fp_in,"%d", &walls);

    
    /* printf("%d %d A%d\n", a, b, variant);
    printf("%d\n", walls); */
    //printf("l, c - %d, %d\n", l, c);
    printf("%d, %d\n", a, b);

    int *maze = calloc(num_cells, sizeof(int));

    for(int i = 0; i<walls; i++){
        fscanf(fp_in,"%d %d %d", &d, &e, &cell);
        /* printf("%d %d %d\n", d, e, cell); */
        conversion=((d*10)-10)+e;
        maze[conversion] = cell;
    }

        option = variant;
        conversion=((a*10)-10)+b;

    if (a<1 || a>l || b<1 || b>c){
                printf("O resultado é: -2\n");
            }
    else{
    switch(option){
        case 1:
            printf("O resultado é: %d\n", maze[conversion]);

        break;

        case 2:
            if(maze[conversion-1] == 0 || maze[conversion+1] == 0  || maze[conversion-10] == 0  || maze[conversion+10] == 0){
                 printf("O resultado é: 1\n");
            }
            else{
                 printf("O resultado é: 0\n");
            }
            //-2 fora do lab e 0 ou 1 para af ou neg

        break;

        case 3:
            if(maze[conversion-1] > 0 || maze[conversion+1] >0  || maze[conversion-10] > 0  || maze[conversion+10] > 0){
                 printf("O resultado é: 1\n");
            }
            else{
                 printf("O resultado é: 0\n");
            }

        break;

        case 4:
            if(maze[conversion-1] == -1 || maze[conversion+1] == -1 || maze[conversion-10] == -1 || maze[conversion+10] == -1){
                 printf("O resultado é: 1\n");
            }
            else{
                 printf("O resultado é: 0\n");
            }

        break;

        case 5:
            if (maze[conversion] == 0 || maze[conversion] == -1){
                printf("O resultado é: -1\n");
            }
            else{
                int operand[4];
                operand[0]=maze[conversion-1];
                operand[1]=maze[conversion+1];
                operand[2]=maze[conversion+10];
                operand[3]=maze[conversion-10];

                if (a==1){
                    operand[2]=2;
                }
                if (a==l){
                    operand[3]=2;
                }
                if (b==1){
                    operand[0]=2;
                }
                if (b==c){
                    operand[1]=2;
                }

                if(((operand[0]+ operand[1])*(operand[2] + operand[3])) == 0){
                    printf("O resultado é: 1\n");
                }
                else{
                    printf("O resultado é: 0\n");
                }
            }
        break;

        case 6:

            int i;
            int *sz = (int *) malloc(num_cells* sizeof(int));
            int *id = (int *) maalloc(num_cells* sizeof(int));
            for (i = 0; i < num_cells; i++) {
                id[i] = i;
                sz[i] = 1;
            }

            
            
        

        break;

    }}
    //print do labirinto
    int f,i;
    for (i=1; i<=l; i++){
        printf("\n");
        for(f=1; f<=c;f++){
            conversion=((i*10)-10)+f;
            printf(" %d ",maze[conversion]);
            if (maze[conversion]>=0){printf(" ");}
        }} 
 
    fclose (fp_in);
    
    
    }
    
    
    
    //./Roap -s enunciado501
}

