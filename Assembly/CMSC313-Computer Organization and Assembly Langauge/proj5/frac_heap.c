/* Nathaniel Fuller
 * CMSC 313
 * Proj5
 */

/* frac_heap.c */
#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

static fraction myFracs[20];

void init_heap (){
  int i;
  for (i=0; i<20; i++)
    {
      myFracs[i].sign = 0;
      myFracs[i].numerator = 0;
      /* -1 used as signal of list end */
      if (i==19)
        {
          myFracs[i].denominator = -1;
        }
      else
        {
          myFracs[i].denominator = i+1;
        }
    }
}

fraction *new_frac(){
  fraction *fp = NULL;
  int i;
  /* find lowest frac w/ sign+numerator+denominator all 0 and ret pointer */
  for (i=0; i<20; i++)
    {
      if (myFracs[i].sign == 0 && myFracs[i].numerator == 0)
        {
          fp = &myFracs[i];
          break;
        }
    }
  if (fp == NULL)
    {
      printf("Error: No space available. Cannot create new fraction.\n");
      printf("Exiting program.\n");
      exit(-1);
    }
  return fp;
}

void del_frac(fraction *fp){
  int i;
  for (i=0; i<20; i++)
    {
      /* if frac matches, remove by setting all values to 0 */
      if (fp->sign == myFracs[i].sign && fp->numerator == myFracs[i].numerator
          && fp->denominator == myFracs[i].denominator)
        {
          myFracs[i].sign = 0;
          myFracs[i].numerator = 0;
          myFracs[i].denominator = 0;
          break;
        }
    }
}

void dump_heap(){
  int i;
  printf("**** BEGIN HEAP DUMP****\n");
  /* loop through to find first free and print it */
  for (i=0; i<20; i++)
    {
      if (myFracs[i].sign == 0 && myFracs[i].numerator == 0)
        {
          printf("First free = %d\n", i);
          /* end loop */
          i = 20;
        }
    }
  /* loop through global array and print out each frac */
  for (i=0; i<20; i++)
    {
      printf("%d: %d %d %d\n", i, myFracs[i].sign, myFracs[i].numerator,
             myFracs[i].denominator);
    }
  printf("**** END HEAP DUMP ****\n\n");
}

