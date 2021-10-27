/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: abl 2020-04-21
 *
 * NAME
 *   quicksortwords.c
 *
 * DESCRIPTION
 *   Main program for unique word finding and quicksorting with tables
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "word.h"

enum quicksort_order {ascending, descending};

enum quicksort_criteria {alphabetic, length, occurrences};


int OP_CNT = 0;     /* global variable, to simplify complexity assessment */

/******************************************************************************
 * quicksort ()
 *
 * Arguments: a - table of items to quicksort
 *            l, r - limits on table to consider
 *            less - item comparison function
 * Returns: (void)
 * Side-Effects: table is quicksorted in place
 *
 * Description: implements "some" quicksorting algorithm for abstract type (Item),
 *       using also an abstract type comparison function (*less)
 *           a[] - array of abstract type Item to be quicksorted
 *           l - index of first element in the array to be quicksorted
 *           r - last element of the array to be quicksorted
 *           (*less)(Item,Item) - abstract type comparison function
 *****************************************************************************/

void quicksort(Item a[], int l, int r,int (*less) (Item, Item))
{
int i,j;
Item v;
if (r <= l) return;
OP_CNT++;
v = a[r]; i = l-1; j = r;
for (;;) {
OP_CNT++;
while (less(a[++i], v))
   OP_CNT++;
OP_CNT++;
while (less(v, a[--j])){
   OP_CNT++;
   if (j == l) break;
}

if (i >= j) break;
exch(a[i], a[j]);
OP_CNT+=2;
}
exch(a[i], a[r]);
OP_CNT+=2;

quicksort(a, l, i-1,*less);
quicksort(a, i+1, r,*less);
}


/******************************************************************************
* main ()
*
*****************************************************************************/

int main(int argc, char **argv)
{
   int TnumWords;              /*total number of words in input file */
   int numWords;               /* number of distint words in input file */
   Tabword tabword;
   int flag=1;              /* table holding the structure */

   /* default initialization for alfabetic order and ascending */
   enum quicksort_criteria criterio = alphabetic;
   enum quicksort_order sentido  = ascending;
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

   /*  Call the quicksorting function using as argument the
       appropriate comparison function selected by user option */

   if ((criterio == alphabetic) && (sentido == ascending)) {
      quicksort((Item*) tabword, 0, numWords-1, LessAlphabetic);
   }
   else if ((criterio == alphabetic) && (sentido == descending)) {
      quicksort((Item*) tabword, 0, numWords-1, MoreAlphabetic);
   }
   else if ((criterio == occurrences) && (sentido == ascending)) {
      quicksort((Item*) tabword, 0, numWords-1, LessNumUses);
   }
   else if ((criterio == occurrences) && (sentido == descending)) {
      quicksort((Item*) tabword, 0, numWords-1, MoreNumUses);
   }
   else if ((criterio == length) && (sentido == ascending)) {
      quicksort((Item*) tabword, 0, numWords-1, LessLength);
   }
   else if ((criterio == length) && (sentido == descending)) {
      quicksort((Item*) tabword, 0, numWords-1, MoreLength);
   }

   /* ---------------------------------------- */
   printf("Accesses count for quicksort: %d\n", OP_CNT);

   

   WriteFile(tabword, file, numWords);
   
   /*printf("Number of different words: %d\n", n_palavras);*/

   /* -- Insert code to call functions to free allocated memory -- */
   FreeWordArray(tabword,numWords);
   /* ------------------------------------------------------------ */
    if(flag == 0){
       
      if(sentido==ascending){
         sentido=descending;
      }
      else{
          sentido=ascending;
      }
      flag=1;
      strcat(file,".palavras");
      goto jump ;
   }

   return 0;
}

