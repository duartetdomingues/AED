#include <stdlib.h>
#include <stdio.h>
#include "test.h"

int a6(int a, int b, int a1, int b1, int l, int c, int num_cells, int *maze)
{

    unsigned int *id = (unsigned int *)malloc((num_cells + 1) * sizeof(unsigned int));

    for (int i = 0; i <= num_cells; i++)
    {
        id[i] = i;
    }

    int a2 = a, b2 = b;
    while (id[conversion(a1, b1, l, c)] != conversion(a, b, l, c))
    {

        if (maze[conversion(a2, b2 - 1, l, c)] == 0)
        {
            id[conversion(a2, b2 - 1, l, c)] = conversion(a, b, l, c);
        }
        if (maze[conversion(a2, b2 + 1, l, c)] == 0)
        {
            id[conversion(a2, b2 + 1, l, c)] = conversion(a, b, l, c);
        }

        if (maze[conversion(a2 - 1, b2, l, c)] == 0)
        {
            id[conversion(a2 - 1, b2, l, c)] = conversion(a, b, l, c);
        }
        if (maze[conversion(a2 + 1, b2, l, c)] == 0)
        {
            id[conversion(a2 + 1, b2, l, c)] = conversion(a, b, l, c);
        }
        maze[conversion(a2, b2, l, c)] = -1;

        int i, f;
        for (i = 1; i <= l; i++)
        {
            for (f = 1; f <= c; f++)
            {
                if (id[conversion(i, f, l, c)] == conversion(a, b, l, c) && maze[conversion(i, f, l, c)] == 0)
                {
                    a2 = i;
                    b2 = f;
                    break;
                }
            }
            if (i == a2 && f == b2)
            {
                break;
            }
        }

        if (maze[conversion(a2, b2, l, c)] == -1)
        {
            break;
        }
    }

    if (id[conversion(a1, b1, l, c)] == conversion(a, b, l, c))
    {
        free(id);
        return 1;
    }
    else
    {
        free(id);
        return 0;
    }
}