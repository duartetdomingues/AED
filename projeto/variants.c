#include "test.h"

void variants(int variant, FILE* fp_out, int* maze, int l, int c, int num_cells, int a, int b, int a1, int b1){
    switch (variant){
        case 1:
            fprintf(fp_out, "%d\n\n", maze[conversion(a, b, l, c)]);
            break;

        case 2:
            if (maze[conversion(a, b - 1, l, c)] == 0 || maze[conversion(a, b + 1, l, c)] == 0 || maze[conversion(a - 1, b, l, c)] == 0 || maze[conversion(a + 1, l, b, c)] == 0){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }
            //-2 fora do lab e 0 ou 1 para af ou neg

        case 3:
            if (maze[conversion(a, b - 1, l, c)] > 0 || maze[conversion(a, b + 1, l, c)] > 0 || maze[conversion(a - 1, b, l, c)] > 0 || maze[conversion(a + 1, b, l, c)] > 0){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }

        case 4:
            if (maze[conversion(a, b - 1, l, c)] == -1 || maze[conversion(a, b + 1, l, c)] == -1 || maze[conversion(a - 1, b, l, c)] == -1 || maze[conversion(a + 1, b, l, c)] == -1){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }


        case 5:
            if (maze[conversion(a, b, l, c)] <= 0){
                fprintf(fp_out, "-1\n\n");
                break;
            }
            else{
                if((maze[conversion(a,b-1,l,c)]==0 && maze[conversion(a,b+1,l,c)]==0) || (maze[conversion(a-1,b,l,c)]==0 && maze[conversion(a+1,b,l,c)]==0)){
                    fprintf(fp_out, "1\n\n");
                    break;
                }
                else{
                    fprintf(fp_out, "0\n\n");
                    break;
                }
            }

        case 6:
            if (maze[conversion(a, b, l, c)] == -2 || maze[conversion(a1, b1, l, c)] == -2){
                fprintf(fp_out, "-2\n\n");
                break;
            }
            else if (maze[conversion(a, b, l, c)] != 0 || maze[conversion(a1, b1, l, c)] != 0){
                fprintf(fp_out, "0\n\n");
                break;
            }

            if (a6(a, b, a1, b1, l, c, num_cells, maze)){
                fprintf(fp_out, "1\n\n");
                break;
            }
            else{
                fprintf(fp_out, "0\n\n");
                break;
            }
        }
}