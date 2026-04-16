/*************************************************************************
 * (c) 2021 by Duarte Domingues (99925) and Tiago Costa (100094)
 * Last modified: Nov. 2021-11-12
 *
 * NAME
 *   roap.h
 * DESCRIPTION
 *      Function declarations for roap problems.
 * 
 ************************************************************************/
#ifndef __roap__
#define __roap__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>
#include "adjacencyList.h"
#include "dijkstras.h"

int makeRooms(int* maze,int l,int c,int cells_number, int walls, int *walls_array);
void bfs(int *maze, int k, int l, int c, int src);

void printPath(FILE* fp_out,int l,int c,LinkedList** adjList,int* parent,int* maze, int j,int k);
int a5(int* maze, int l, int c, int a, int b);

int maze_solver(FILE* fp_out,int* maze, int l, int c, int cells_number, int walls, int* walls_array, int a, int b);
int conversion(int a,int b,int l, int c);
int* inverted_conversion(int x, int l, int c);

/******************************************************************************
 *  Data Type: LinkedListStruct
 *
 *  Description: Structure with:
 *      1) Integer vertex to store nodes in the queue.
 *      2) Next struct pointer.
 * 
 *****************************************************************************/

typedef struct queue
{
   int vertex;
   struct queue *next;
}Queue;

void push(Queue **head,Queue **final,int new_vertex);
Queue *pop(Queue **Queue);
int isEmpty(Queue *aux);
void freeQueue(Queue *head);

#endif    /* __roap__ */
