#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "test.h"

int conversion(int a, int b, int l, int c)
{
    if (a <= l && b <= c && a > 0 && b > 0)
    {
        int x = 0;
        x = (a - 1) * c + b;
        return x;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{

    FILE *fp_in = NULL;
    FILE *fp_out = NULL;
    char *filename_in;
    int option = 0;
    int l = 0, c = 0, a = 0, b = 0, a1 = 0, b1 = 0, d = 0, e = 0, walls = 0, num_cells = 0, /* conversion, */ variant = 0, point = 0;
    short cell;

    if (argc != 3 || strcmp(argv[1], "-s") != 0 || strstr(argv[2], ".in1") == NULL)
    {
        exit(EXIT_FAILURE);
    }

    filename_in = argv[2];

    for (int i = 0; i <= strlen(filename_in); i++)
    { // encontar o ultimo ponto
        if (filename_in[i] == '.')
        {
            point = i;
        }
    }
    char *filename_out = NULL;
    filename_out = (char *)calloc((point + strlen(".sol1") + 1), sizeof(char));
    strncpy(filename_out, filename_in, point); // copiar ate ao '.'
    strcat(filename_out, ".sol1");

    if ((fp_in = fopen(filename_in, "r")) == NULL)
        exit(EXIT_FAILURE);
    if ((fp_out = fopen(filename_out, "w")) == NULL)
        exit(EXIT_FAILURE);

    while (fscanf(fp_in, "%d %d", &l, &c) == 2 && !feof(fp_in))
    {

        num_cells = l * c;

        if (fscanf(fp_in, "%d %d A%d", &a, &b, &variant) != 3)
        {
            exit(EXIT_FAILURE);
        }

        if (variant == 6)
        {
            if (fscanf(fp_in, "%d %d", &a1, &b1) != 2)
            {
                exit(EXIT_FAILURE);
            }
        }
        if (fscanf(fp_in, "%d", &walls) != 1)
        {
            exit(EXIT_FAILURE);
        }

        short *maze = (short *)malloc((num_cells + 1) * sizeof(short));
        for (int i = 1; i <= num_cells; i++)
        {
            maze[i] = 0;
        }

        maze[0] = -2;

        for (int i = 0; i < walls; i++)
        {
            if (fscanf(fp_in, "%d %d %hd", &d, &e, &cell) != 3)
            {
                exit(EXIT_FAILURE);
            }
            maze[conversion(d, e, l, c)] = cell;
        }

        option = variant;

        if (a < 1 || a > l || b < 1 || b > c)
        {
            fprintf(fp_out, "-2\n\n");
            free(maze);
            continue;
        }

        switch (option)
        {
        case 1:
            fprintf(fp_out, "%hd\n\n", maze[conversion(a, b, l, c)]);

            break;

        case 2:
            if (maze[conversion(a, b - 1, l, c)] == 0 || maze[conversion(a, b + 1, l, c)] == 0 || maze[conversion(a - 1, b, l, c)] == 0 || maze[conversion(a + 1, l, b, c)] == 0)
            {
                fprintf(fp_out, "1\n\n");
                break;
            }
            else
            {
                fprintf(fp_out, "0\n\n");
                break;
            }
            //-2 fora do lab e 0 ou 1 para af ou neg

            break;

        case 3:
            if (maze[conversion(a, b - 1, l, c)] > 0 || maze[conversion(a, b + 1, l, c)] > 0 || maze[conversion(a - 1, b, l, c)] > 0 || maze[conversion(a + 1, b, l, c)] > 0)
            {
                fprintf(fp_out, "1\n\n");
                break;
            }
            else
            {
                fprintf(fp_out, "0\n\n");
                break;
            }

            break;

        case 4:
            if (maze[conversion(a, b - 1, l, c)] == -1 || maze[conversion(a, b + 1, l, c)] == -1 || maze[conversion(a - 1, b, l, c)] == -1 || maze[conversion(a + 1, b, l, c)] == -1)
            {
                fprintf(fp_out, "1\n\n");
                break;
            }
            else
            {
                fprintf(fp_out, "0\n\n");
                break;
            }

            break;

        case 5:
            if (maze[conversion(a, b, l, c)] == 0 || maze[conversion(a, b, l, c)] == -1)
            {
                fprintf(fp_out, "-1\n\n");
                break;
            }
            else
            {
                int operand[4];
                operand[0] = maze[conversion(a, b - 1, l, c)];
                operand[1] = maze[conversion(a, b + 1, l, c)];
                operand[2] = maze[conversion(a + 1, b, l, c)];
                operand[3] = maze[conversion(a - 1, b, l, c)];

                if (a == 1)
                {
                    operand[2] = 2;
                }
                if (a == l)
                {
                    operand[3] = 2;
                }
                if (b == 1)
                {
                    operand[0] = 2;
                }
                if (b == c)
                {
                    operand[1] = 2;
                }

                if (((operand[0] + operand[1]) * (operand[2] + operand[3])) == 0)
                {
                    fprintf(fp_out, "1\n\n");
                    break;
                }
                else
                {
                    fprintf(fp_out, "0\n\n");
                    break;
                }
            }
            break;

        case 6:
            if (maze[conversion(a, b, l, c)] == -2 || maze[conversion(a1, b1, l, c)] == -2)
            {
                fprintf(fp_out, "-2\n\n");
                break;
            }
            else if (maze[conversion(a, b, l, c)] > 0 || maze[conversion(a1, b1, l, c)] > 0)
            {
                fprintf(fp_out, "0\n\n");
                break;
            }

            if (a6(a, b, a1, b1, l, c, num_cells, maze))
            {
                fprintf(fp_out, "1\n\n");
                break;
            }
            else
            {
                fprintf(fp_out, "0\n\n");
                break;
            }

            break;
        }
        free(maze);
    }

    fclose(fp_in);
    fclose(fp_out);
    free(filename_out);
}
