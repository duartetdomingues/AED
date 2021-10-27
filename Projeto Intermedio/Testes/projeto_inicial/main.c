/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   main.c
 *
 * DESCRIPTION
 *      Main program to read the given file and call the variants function 
 *      which will output the desired information about one specific cell.
 *      Requires argc and argv as argument.
 *      Option "-s" to select the input's filename.
 *
 ******************************************************************************/

#include "roap.h"
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]){

    FILE *fp_in = NULL, *fp_out = NULL;
    char *filename_in = NULL,*filename_out = NULL;
    int l = 0, c = 0, a = 0, b = 0, a1 = 0, b1 = 0, x = 0, y = 0, walls = 0, cells_number = 0, variant = 0, point = 0, i=0, cell = 0;

    /* Checking terminal commands' validality */
    if (argc != 3 || strcmp(argv[1], "-s") != 0 || strstr(argv[2], ".in1") == NULL){
        exit(EXIT_FAILURE);
    }

    /* Assuming input's filename  */
    filename_in = argv[2];

    /* Creating the output file's name */
        //Counting its characters
    for (i = 0; i <= strlen(filename_in); i++){
        if (filename_in[i] == '.'){
            point = i;
        }
    }
        //Adding its termination
    filename_out = (char *)calloc((point + strlen(".sol1") + 1), sizeof(char));
    strncpy(filename_out, filename_in, point);
    strcat(filename_out, ".sol1");

    /* Opening input and output files */
    if ((fp_in = fopen(filename_in, "r")) == NULL){
        free(filename_out);
        exit(EXIT_FAILURE);
        
    } 
    if ((fp_out = fopen(filename_out, "w")) == NULL){
        free(filename_out);
        fclose(fp_in);
        exit(EXIT_FAILURE);
    }   

    /* Reading the whole file */
    while (!feof(fp_in) && fscanf(fp_in, "%d %d", &l, &c) == 2){

        /* Reading the first three lines independently since those are different from the rest (the first is read in the while loop) */
            //Calculating the number of cells of the maze
            cells_number = l * c;

        if (fscanf(fp_in, "%d %d A%d", &a, &b, &variant) != 3){
            free(filename_out);
            fclose(fp_in);
            fclose(fp_out);
            exit(EXIT_FAILURE);
        }
            //In case of variant A6, reading an extra pair of coordinates
            if (variant == 6){
                if (fscanf(fp_in, "%d %d", &a1, &b1) != 2){
                    free(filename_out);
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(EXIT_FAILURE);
                }
            }

        if (fscanf(fp_in, "%d", &walls) != 1){
            free(filename_out);
            fclose(fp_in);
            fclose(fp_out);
            exit(EXIT_FAILURE);
        }

        /* Checking if the given coordinates are actually valid. If not we either proceed to the next maze, printing '-2' or end the execution */
        if ((a < 1 || a > l || b < 1 || b > c) || ((variant == 6) && (a1 < 1 || a1 > l || b1 < 1 || b1 > c))){
            for (i = 0; i < walls; i++){
                if (fscanf(fp_in, "%d %d %d", &x, &y, &cell) != 3){
                    free(filename_out);
                    fclose(fp_in);
                    fclose(fp_out);
                    exit(EXIT_FAILURE);
                }
            }
            fprintf(fp_out, "-2\n\n");
            continue;
        }
        
        /* Allocating memory for one dimensional maze table */
        int *maze = (int *)calloc((cells_number + 1), sizeof(int));

        /* The first element of the table represent any element that is out of maze's boundaries - see conversion() function */
        maze[0] = -2;

        /* Filling the table with the given information */
        for (i = 0; i < walls; i++){
            if (fscanf(fp_in, "%d %d %d", &x, &y, &cell) != 3){
                free(filename_out);
                free(maze);
                fclose(fp_in);
                fclose(fp_out);
                exit(EXIT_FAILURE);
            }
            maze[conversion(x, y, l, c)] = cell;
        }

        /* Writing the requested value in the output file taking into account the given variation */
        variants(variant, fp_out, maze, l, c, cells_number, a, b, a1, b1);

        /* Freeing the data structure */
        free(maze);
    }

    /* Closing the files */
    fclose(fp_in);
    fclose(fp_out);

    free(filename_out);

    exit(EXIT_SUCCESS);
}

/******************************************************************************
 * conversion()
 *
 * Arguments: a, b, l, c
 * 
 * Returns: the number of the cell, given a pair of coordinates
 *
 * Description: converts a 2D coordinate into a 1D coordinate (to the number 
 * of the cell)
 *****************************************************************************/

int conversion(int a, int b, int l, int c){
    /* Testing if the cell is inside maze's boundaries */
    if (a <= l && b <= c && a > 0 && b > 0){
        int x = 0;
        x = (a - 1) * c + b;
        return x;
    }
     /* If not, it will return 0 which is the position of the maze array where -2 is stored (maze[0] = -2). */
    else{
        return 0;
    }
}
