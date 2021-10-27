/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: abl 2020-04-21
 *
 * NAME
 *   sortwords.c
 *
 * DESCRIPTION
 *   Main program for unique word finding and sorting with tables
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "word.h"

enum sort_order {ascending, descending};

enum sort_criteria {alphabetic, length, occurrences};


int OP_CNT = 0;     /* global variable, to simplify complexity assessment */


/******************************************************************************
 * sort ()
 *
 * Arguments: a - table of items to sort
 *            l, r - limits on table to consider
 *            less - item comparison function
 * Returns: (void)
 * Side-Effects: table is sorted in place
 *
 * Description: implements "some" sorting algorithm for abstract type (Item),
 *       using also an abstract type comparison function (*less)
 *           a[] - array of abstract type Item to be sorted
 *           l - index of first element in the array to be sorted
 *           r - last element of the array to be sorted
 *           (*less)(Item,Item) - abstract type comparison function
 *****************************************************************************/

void sort(Item a[], int l, int r, int (*less) (Item, Item))
{
   int i, j;

   for (i = l + 1; i <= r; i++) {
      Item v = a[i];
      OP_CNT++;
      j = i;
      OP_CNT++;
      while (j > l && less(v, a[j - 1])) {
         a[j] = a[j - 1];
         OP_CNT+=2;
         j--;
         OP_CNT++;
      }
      a[j] = v;
      OP_CNT++;
   }
   return;
}


/******************************************************************************
* main ()
*
*****************************************************************************/

int main(int argc, char **argv)
{
   int TnumWords;              /* total number of words in input file */
   int numWords;               /* number of distint words in input file */
   Tabword tabword;             /* table holding the structure */
   int flag=1;

   /* default initialization for alfabetic order and ascending */

   enum sort_criteria criterio = alphabetic;
   enum sort_order sentido  = ascending;
   char *file = argv[1];

   argv++;             /* get past prog and file names */
   while (*(++argv)) {
      if (strcmp(*argv, "-alfabetica") == 0)
         criterio = alphabetic;
      else if (strcmp(*argv, "-ocorrencias") == 0)
         criterio = occurrences;
      else if (strcmp(*argv, "-comprimento") == 0)
         criterio = length;
      else if (strcmp(*argv, "-a") == 0)
         sentido = ascending;
      else if (strcmp(*argv, "-d") == 0)
         sentido = descending;
       else if (strcmp(*argv, "-i") == 0)
         flag=0;
      else {
         fprintf(stderr, "Wrong arguments\n");
         exit(3);
      }
   }

   jump:

   printf("\nFile:%s\n",file);
   TnumWords = AllocWordArray(&tabword, file);
   printf("Total number of words: %d\n", TnumWords);

   numWords = FillInWordArray(tabword, file);
   printf("Number of different words = %d\n", numWords);

   OP_CNT = 0;

   /*  Call the sorting function using as argument the
       appropriate comparison function selected by user option */

   if ((criterio == alphabetic) && (sentido == ascending)) {
      sort((Item*) tabword, 0, numWords-1, LessAlphabetic);
   }
   else if ((criterio == alphabetic) && (sentido == descending)) {
      sort((Item*) tabword, 0, numWords-1, MoreAlphabetic);
   }
   else if ((criterio == occurrences) && (sentido == ascending)) {
      sort((Item*) tabword, 0, numWords-1, LessNumUses);
   }
   else if ((criterio == occurrences) && (sentido == descending)) {
      sort((Item*) tabword, 0, numWords-1, MoreNumUses);
   }
   else if ((criterio == length) && (sentido == ascending)) {
      sort((Item*) tabword, 0, numWords-1, LessLength);
   }
   else if ((criterio == length) && (sentido == descending)) {
      sort((Item*) tabword, 0, numWords-1, MoreLength);
   }
   
   /* ---------------------------------------- */
   printf("Accesses count for sort: %d\n", OP_CNT);

   

   WriteFile(tabword, file, numWords);
   
   /*printf("Number of different words: %d\n", n_palavras);*/

   /* -- Insert code to call functions to free allocated memory -- */

   FreeWordArray(tabword,numWords);

   /* ------------------------------------------------------------ */


   if(flag==0){
      if(sentido==ascending){
         sentido=descending;
      }
      else{
          sentido=ascending;
      }
      strcat(file,".palavras");
      flag=1;
      goto jump ;
   }

   return 0;

}

