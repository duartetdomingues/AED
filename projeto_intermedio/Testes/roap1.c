#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int conversion(int a,int b,int l, int c){
    if(a<=l && b<=c && a>0 && b>0){ 
    int x=0;
    x=(a-1)*c+b;
    return x;
    }
    else{return 0;}
}

int main(int argc, char *argv[]){

    FILE *fp_in = NULL;
    FILE *fp_out = NULL;
    char *filename_in;
    int option;
    int l, c, a, b, a1, b1, d, e, walls, num_cells, /* conversion, */ variant, point=0;
    short cell;

    if( argc!=3 || strcmp(argv[1],"-s")!= 0 || strstr(argv[2], ".in1") == NULL){
        exit(EXIT_FAILURE);
    }

    filename_in=argv[2];

    for(int i=0;i<=strlen(filename_in);i++){
        if(filename_in[i]=='.'){
            point=i;
        }
    }
    char *filename_out=NULL;
    filename_out=(char*)calloc((point+strlen(".sol1")+1),sizeof(char));
    strncpy(filename_out,filename_in,point);
    strcat(filename_out,".sol1");

    /* printf("%s\n",filename_in);*/
    if((fp_in = fopen(filename_in, "r")) == NULL) exit(EXIT_FAILURE);
    if((fp_out = fopen(filename_out, "wb")) == NULL) exit(EXIT_FAILURE);

    while(fscanf(fp_in,"%d %d", &l, &c)==2 && !feof(fp_in)){


    //printf("Next file\n");
    //fscanf(fp_in,"%d %d", &l, &c);
    num_cells = l*c;
    // 1 1 A1
    if(fscanf(fp_in,"%d %d A%d", &a, &b, &variant)!=3){
        exit(EXIT_FAILURE);
    }
    if(variant==6){
        if(fscanf(fp_in,"%d %d", &a1, &b1)!=2){
            exit(EXIT_FAILURE);
        }
    }
    if(fscanf(fp_in,"%d", &walls)!=1){
        exit(EXIT_FAILURE);
    }

    
    /* printf("%d %d A%d\n", a, b, variant);
    printf("%d\n", walls); */
    //printf("l, c - %d, %d\n", l, c);
    //printf("%d, %d\n", a, b);

    short *maze = (short*) malloc((num_cells+1)* sizeof(short));
    for(int i=1;i<=num_cells;i++){
        maze[i]=0;
    }

    maze[0]=-2;

    for(int i = 0; i<walls; i++){
        if(fscanf(fp_in,"%d %d %hd", &d, &e, &cell)!=3){
            exit(EXIT_FAILURE);
        }
        /* printf("%d %d %d\n", d, e, cell); */
        maze[conversion(d,e,l,c)] = cell;
    }

        option = variant;
        

    if (a<1 || a>l || b<1 || b>c){
                fprintf(fp_out,"-2\n\n");
                break;
            }
    else{
    switch(option){
        case 1:
            fprintf(fp_out,"%d\n\n", maze[conversion(a,b,l,c)]);

        break;

        case 2:
            if(maze[conversion(a,b-1,l,c)] == 0 || maze[conversion(a,b+1,l,c)] == 0  || maze[conversion(a-1,b,l,c)] == 0  || maze[conversion(a+1,l,b,c)] == 0){
                 fprintf(fp_out,"1\n\n");
                 break;
            }
            else{
                 fprintf(fp_out,"0\n\n");
                 break;
            }
            //-2 fora do lab e 0 ou 1 para af ou neg

        break;

        case 3:
            if(maze[conversion(a,b-1,l,c)] > 0 || maze[conversion(a,b+1,l,c)] >0  || maze[conversion(a-1,b,l,c)] > 0  || maze[conversion(a+1,b,l,c)] > 0){
                 fprintf(fp_out,"1\n\n");
                 break;
            }
            else{
                 fprintf(fp_out,"0\n\n");
                 break;
            }

        break;

        case 4:
            if(maze[conversion(a,b-1,l,c)] == -1 || maze[conversion(a,b+1,l,c)] == -1 || maze[conversion(a-1,b,l,c)] == -1 || maze[conversion(a+1,b,l,c)] == -1){
                 fprintf(fp_out,"1\n\n");
                 break;
            }
            else{
                 fprintf(fp_out,"0\n\n");
                 break;
            }

        break;

        case 5:
            if (maze[conversion(a,b,l,c)] == 0 || maze[conversion(a,b,l,c)] == -1){
                fprintf(fp_out,"-1\n\n");
                break;
            }
            else{
                int operand[4];
                operand[0]=maze[conversion(a,b-1,l,c)];
                operand[1]=maze[conversion(a,b+1,l,c)];
                operand[2]=maze[conversion(a+1,b,l,c)];
                operand[3]=maze[conversion(a-1,b,l,c)];

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
                    fprintf(fp_out,"1\n\n");
                    break;
                }
                else{
                    fprintf(fp_out,"0\n\n");
                    break;
                }
            }
        break;

        case 6:
            if (maze[conversion(a,b,l,c)]==-2 || maze[conversion(a1,b1,l,c)]==-2){
                fprintf(fp_out,"-2\n\n");
                break;
            }
            else if (maze[conversion(a,b,l,c)]!=0 || maze[conversion(a1,b1,l,c)]!=0){
                fprintf(fp_out,"0\n\n");
                break;
            }

            short *sz = (short *) malloc((num_cells+1)* sizeof(short));
            short *id = (short *) malloc((num_cells+1)* sizeof(short));

            for (int i = 0; i <= num_cells; i++) {
                id[i] = i;
                if(maze[i]!=0){
                   sz[i] = 1; 
                }
                else{
                    sz[i]= 0;
                } 
            }

            int a2=a,b2=b;
            while(id[conversion(a1,b1,l,c)] != conversion(a,b,l,c)){
                
                
                if(maze[conversion(a2,b2-1,l,c)]==0){
                    id[conversion(a2,b2-1,l,c)]=conversion(a,b,l,c); 
                }
                if(maze[conversion(a2,b2+1,l,c)]==0){
                    id[conversion(a2,b2+1,l,c)]=conversion(a,b,l,c); 
                }

                if(maze[conversion(a2-1,b2,l,c)]==0){
                    id[conversion(a2-1,b2,l,c)]=conversion(a,b,l,c); 
                }
                if(maze[conversion(a2+1,b2,l,c)]==0){
                    id[conversion(a2+1,b2,l,c)]=conversion(a,b,l,c); 
                }
                sz[conversion(a2,b2,l,c)]=1;

                int i,f;
                for (i=1; i<=l;i++){
                for(f=1; f<=c;f++){
                    if(id[conversion(i,f,l,c)] == conversion(a,b,l,c) && sz[conversion(i,f,l,c)]==0){
                        a2=i;
                        b2=f;
                        break;
                    }
                }
                if(i==a2 && f==b2){
                    break;
                }}

                if(sz[conversion(a2,b2,l,c)]==1){
                    break;
                }
            }
            if(id[conversion(a1,b1,l,c)] == conversion(a,b,l,c)){
                fprintf(fp_out,"1\n\n");
                break;
            }
            else{
                fprintf(fp_out,"0\n\n");
                break;
            }
            free(id);
            free(sz);
    }
    }
    free(maze);
    }
    fclose (fp_in);
    fclose (fp_out);
    free(filename_out);
    
}

