/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 * 
 * 
 * exemple:
 *   Main program to call the different connectivity algorithms.
 *   Requires test data file name as argument.
 *   Option "-q" for reduced output in interactive mode.
 *   Option "-1/2/3/4" for for single run in batch, quiet mode.
 *
 * COMMENTS
 * 
 * 
 * exemple:
 *  Batch mode added experimentally. Todo: rework logic, fix repeated code
 ******************************************************************************/
#include "roap.h"
#include <getopt.h>
#include <string.h>

int conversion(int a, int b, int l, int c){
    if (a <= l && b <= c && a > 0 && b > 0){
        int x = 0;
        x = (a - 1) * c + b;
        return x;
    }
    else{
        return 0;
    }
}

int main(int argc, char *argv[]){

    FILE *fp_in = NULL,*fp_out = NULL;
    char *filename_in = NULL,*filename_out = NULL;
    int l = 0, c = 0, a = 0, b = 0, a1 = 0, b1 = 0, d = 0, e = 0, walls = 0, num_cells = 0, variant = 0, point = 0, i, cell;

    if (argc != 3 || strcmp(argv[1], "-s") != 0 || strstr(argv[2], ".in1") == NULL){
        exit(EXIT_FAILURE);
    }

    filename_in = argv[2];

    for (int i = 0; i <= strlen(filename_in); i++){// encontar o ultimo ponto 
        if (filename_in[i] == '.'){
            point = i;
        }
    }
    
    filename_out = (char *)calloc((point + strlen(".sol1") + 1), sizeof(char));
    strncpy(filename_out, filename_in, point); // copiar ate ao '.'
    strcat(filename_out, ".sol1");

    if ((fp_in = fopen(filename_in, "r")) == NULL){
        free(filename_out);
        exit(EXIT_FAILURE);
        
    }
        
    if ((fp_out = fopen(filename_out, "w")) == NULL){
        free(filename_out);
        exit(EXIT_FAILURE);
    }   

    while (!feof(fp_in)){

        if (fscanf(fp_in, "%d %d", &l, &c) != 2){
            free(filename_out);
            exit(EXIT_FAILURE);
        }
        
        num_cells = l * c;

        if (fscanf(fp_in, "%d %d A%d", &a, &b, &variant) != 3){
            free(filename_out);
            exit(EXIT_FAILURE);
        }

        if (variant == 6){
            if (fscanf(fp_in, "%d %d", &a1, &b1) != 2){
                free(filename_out);
                exit(EXIT_FAILURE);
            }
        }

        if (fscanf(fp_in, "%d", &walls) != 1){
            free(filename_out);
            exit(EXIT_FAILURE);
        }

        if (a < 1 || a > l || b < 1 || b > c){
            for (i = 0; i < walls; i++){
                if (fscanf(fp_in, "%d %d %d", &d, &e, &cell) != 3){
                    free(filename_out);
                    exit(EXIT_FAILURE);
                }
            }
            fprintf(fp_out, "-2\n\n");
            continue;
        }
        
        int *maze = (int *)malloc((num_cells + 1) * sizeof(int));
        for (i = 1; i <= num_cells; i++){
            maze[i] = 0;
        }

        maze[0] = -2;

        for (i = 0; i < walls; i++){
            if (fscanf(fp_in, "%d %d %d", &d, &e, &cell) != 3){
                free(filename_out);
                free(maze);
                exit(EXIT_FAILURE);
            }
            maze[conversion(d, e, l, c)] = cell;
        }

        variants(variant, fp_out, maze, l, c, num_cells, a, b, a1, b1);
        free(maze);
    }

    fclose(fp_in);
    fclose(fp_out);
    free(filename_out);
    
}
