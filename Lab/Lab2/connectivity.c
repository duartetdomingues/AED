/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#include "connectivity.h"

#define DEBUG 0

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
   int i, p, q, t;
   int pairs_cnt = 0;                              /* connection pairs counter */
   int links_cnt = 0;                              /* number of links counter */
   unsigned long int opelem_cnt_f = 0;             /* number of elementar operations counter for find*/
   unsigned long int opelem_cnt_u = 0;             /* number of elementar operations counter for union*/

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i; //??? (O.E.)
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      /* do search first */
      opelem_cnt_f+=2;
      if (id[p] == id[q]) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      
      /* pair has new info; must perform union */
      opelem_cnt_u++;
      for (t = id[p], i = 0; i < N; i++) {
         opelem_cnt_u++;
         if (id[i] == t){
            opelem_cnt_u+=2;
            id[i] = id[q];
         }
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }

   printf("QF: The number of links performed is %d for %d input pairs.\n", links_cnt, pairs_cnt);
   printf("\nQF: The number of elementar operations of the algorithm is:\n       -For finding: %ld\n       -For union: %ld\n       -Total: %ld\n", opelem_cnt_f, opelem_cnt_u,(opelem_cnt_f+opelem_cnt_u));
   return;
}


/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int opelem_cnt_f = 0;             /* number of elementar operations counter for find*/
   unsigned long int opelem_cnt_u = 0;             /* number of elementar operations counter for union*/

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      i = p;
      j = q;

      /* do search first */
      opelem_cnt_f++;
      while (i != id[i]) {
         i = id[i];
         opelem_cnt_f+=2;
      }
      opelem_cnt_f++;
      while (j != id[j]) {
         j = id[j];
         opelem_cnt_f+=2;
      }
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      opelem_cnt_u++;
      id[i] = j;
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of links performed is %d for %d input pairs.\n",links_cnt, pairs_cnt);
   printf("\nQU: The number of elementar operations of the algorithm is:\n       -For finding: %ld\n       -For union: %ld\n       -Total: %ld\n", opelem_cnt_f, opelem_cnt_u,(opelem_cnt_f+opelem_cnt_u));
}


/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int opelem_cnt_f = 0;             /* number of elementar operations counter for find*/
   unsigned long int opelem_cnt_u = 0;             /* number of elementar operations counter for union*/

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      opelem_cnt_f+=2;
      for (i = p; i != id[i]; i = id[i])opelem_cnt_f+=2;;
      opelem_cnt_f+=2;
      for (j = q; j != id[j]; j = id[j])opelem_cnt_f+=2;;

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      opelem_cnt_u+=2;
      if (sz[i] < sz[j]) {
         id[i] = j;
         opelem_cnt_u+=3;
         sz[j] += sz[i];
      }
      else {
         id[j] = i;
         opelem_cnt_u+=3;
         sz[i] += sz[j];
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of links performed is %d for %d input pairs.\n",links_cnt, pairs_cnt);
   printf("\nWQU: The number of elementar operations of the algorithm is:\n       -For finding: %ld\n       -For union: %ld\n       -Total: %ld\n", opelem_cnt_f, opelem_cnt_u,(opelem_cnt_f+opelem_cnt_u));
}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
   int i, j, p, q, t, x;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;                              /* connection pairs counter */
   int links_cnt = 0;                              /* number of links counter */
   unsigned long int opelem_cnt_f = 0;             /* number of elementar operations counter for find*/
   unsigned long int opelem_cnt_u = 0;             /* number of elementar operations counter for union*/


   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      opelem_cnt_f+=2;
      for (i = p; i != id[i]; i = id[i])opelem_cnt_f+=2;;
      opelem_cnt_f+=2;
      for (j = q; j != id[j]; j = id[j])opelem_cnt_f+=2;;

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      opelem_cnt_u+=2;
      if (sz[i] < sz[j]) {
         id[i] = j;
         opelem_cnt_u+=3;
         sz[j] += sz[i];
         t = j;
      }
      else {
         id[j] = i;
         opelem_cnt_u+=3;
         sz[i] += sz[j];
         t = i;
      }
      links_cnt++;

      /* retrace the path and compress to the top */
      opelem_cnt_u++;
      for (i = p; i != id[i]; i = x) {
         opelem_cnt_u+=3;
         x = id[i];
         id[i] = t;
      }
      opelem_cnt_u++;
      for (j = q; j != id[j]; j = x) {
         opelem_cnt_u+=3;
         x = id[j];
         id[j] = t;
      }
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of links performed is %d for %d input pairs.\n",links_cnt, pairs_cnt);
   printf("\nWQU: The number of elementar operations of the algorithm is:\n       -For finding: %ld\n       -For union: %ld\n       -Total: %ld\n", opelem_cnt_f, opelem_cnt_u,(opelem_cnt_f+opelem_cnt_u));

   return;
}
