/******************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Oct. 2021-10-20
 *
 * NAME
 *   roap.h
 * DESCRIPTION
 *      Function declarations for roap problems.
 ************************************************************************/
#ifndef __roap__
#define __roap__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>
#include "LinkedList.h"
#include "dijkstras.h"


int make_rooms(int* maze,int l,int c,int cells_number, int walls,int* walls_array);
void bfs(int *maze, int k, int l, int c, int src);
int** dijkstras(LinkedList **adjList, int *maze, int n_vertex, int inicial_vertex, int final_vertex);
void printPath(FILE* fp_out,int l,int c,LinkedList** adjList,int* parent,int* maze, int j,int k);
//void printSolution(FILE *fp_out,int *maze,int l,int c,LinkedList** adjList,int* dist, int V, int* parent, int final_vertix);
int a5(int* maze, int l, int c, int a, int b);


int conversion(int a,int b,int l, int c);
int* inverted_conversion(int x, int l, int c);
int maze_solver(FILE* fp_out,int* maze, int l, int c, int cells_number, int walls, int* walls_array, int a, int b);
void print_table(int* table,int l,int c);

#endif    /* __roap__ */
