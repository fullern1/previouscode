/* Nathaniel Fuller
 * CMSC 313 project 6
 */

/* frac_heap.c */
#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

union fraction_block{
  union fraction_block *next;
  fraction frac;
};
typedef union fraction_block fraction_block;

/* head of linked list pointer (empty free list?) */
static fraction_block *listHead;

void init_heap (){
  /* ??? Initialize empty free list ??? */
}

fraction *new_frac(){
  fraction *fp;
  int i;

  /* no available blocks, create 5 new and pass first */
  if (listHead == NULL){
    if (NULL == (listHead = malloc(sizeof(fraction_block)*5))){
      printf("malloc failed, program exiting.");
      exit(-1);
    }
    /* graders debugging message */
    printf("called malloc() (%d): returned %p\n", sizeof(fraction_block)*5, 
	   listHead);

    /* link allocated blocks together */
    for (i=0; i<4; i++){
      listHead[i].next = &listHead[i+1];
    }
    /* set last block link to null */
    listHead[i].next = NULL;

    fp = &listHead->frac;
    listHead = listHead->next;
  }
  /* if blocks available pass block and move to next */
  else{
    fp = &listHead->frac;
    listHead = listHead->next;
  }  
  return fp;
}

void del_frac(fraction *fp){
  int i = 0;
  fraction_block *fbp;
  /* set fraction values to 0 */
  fp->sign = 0;
  fp->numerator = 0;
  fp->denominator = 0;
  /* cast fraction pointer to fraction block pointer */
  fbp = (fraction_block *) fp;
  /* find end of list */
  if (listHead == NULL){
    listHead = fbp;
    listHead->next = NULL;
  }
  else{
    while (listHead[i].next != NULL){
      i++;
    } 
    /* add removed fraction to end of list */
    listHead[i].next = fbp;
    /* set end of list next value to NULL */
    listHead[i+1].next = NULL;
  }
}

void dump_heap(){
  int i = 0;
  printf("**** BEGIN HEAP DUMP ****\n\n");

  if (listHead == NULL){
    printf("Free list is empty.\n");
  }
  else{
    printf("%p\n", (void*) &listHead[i]);
    while (listHead[i].next != NULL){
      printf("%p\n", (void*) &listHead[i+1]);
      i++;
    }
  }
  printf("\n***** END HEAP DUMP *****\n\n");
}
