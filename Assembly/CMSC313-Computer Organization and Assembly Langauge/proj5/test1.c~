/*
 *  File: test1.c
 *
 *  This file tests out the functions in frac_heap.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

/*
 * Compute the greatest common divisor using Euclid's algorithm
 */
unsigned int gcd ( unsigned int a, unsigned int b) {

  if (b == 0) return a ;

  return gcd (b, a % b) ;
}

/*
 * Print a fraction out nicely
 */
void print_frac (fraction *fptr) {

  if (fptr->sign < 0) printf("-") ;

  printf("%d/%d", fptr->numerator, fptr->denominator) ;

}

/*
 * Initialize a fraction
 */
fraction *init_frac (signed char s, unsigned int n, unsigned int d) {

  fraction *fp ;

  fp = new_frac() ;
  fp->sign = s ;
  fp->numerator = n ;
  fp->denominator = d ;

  return fp ;
}

/*
 * Add two fractions
 * Return value is a pointer to allocated space.
 * This must be deallocated using del_frac().
 */
fraction *add_frac(fraction *fptr1, fraction *fptr2) {
  unsigned int lcm, div, g, m1, m2  ;
  fraction *answer ;


  g = gcd(fptr1->denominator, fptr2->denominator) ;
  lcm = (fptr1->denominator / g) * fptr2->denominator ;

  m1 = (fptr1->denominator / g) ;
  m2 = (fptr2->denominator / g) ;
  lcm = m1 * fptr2->denominator ;

  answer = new_frac() ;
  answer->denominator = lcm ;

  if (fptr1->sign == fptr2->sign) {

    answer->sign = fptr1->sign ;
    answer->numerator = fptr1->numerator * m2 + fptr2->numerator * m1 ;

  } else if (fptr1->numerator >= fptr2->numerator) {

    answer->sign = fptr1->sign ;
    answer->numerator = fptr1->numerator * m2 - fptr2->numerator * m1 ;

  } else {

    answer->sign = fptr2->sign ;
    answer->numerator = fptr2->numerator * m2 - fptr1->numerator * m1 ;

  }

  div = gcd(answer->numerator, answer->denominator) ;
  answer->numerator /= div ;
  answer->denominator /= div ;

  return answer ;

}


int main() {
  fraction *fp1, *fp2, *fp3, *fp14, *fp15, *fp16, *fp17, *fp18, *fp19, *fp20;
  /* init heap, create 3 fracs manually */
  init_heap() ;

  fp1 = new_frac() ;
  fp1->sign = -1 ;
  fp1->numerator = 2 ;
  fp1->denominator = 3 ;

  fp2 = new_frac() ;
  fp2->sign = 1 ;
  fp2->numerator = 1 ;
  fp2->denominator = 4 ;

  fp3 = add_frac(fp1, fp2) ;
  dump_heap();
  
  /* reinit heap, create 3 fracs w/ init_frac func */
  init_heap();
  fp1 = init_frac(1, 1, 1);
  fp2 = init_frac(2, 2, 2);
  fp3 = init_frac(-3, 3, 3);
  dump_heap();

  fraction *fp4, *fp5, *fp6, *fp7, *fp8, *fp9, *fp10, *fp11, *fp12, *fp13, *fp21;
  /* init fracs 4-20 w/ init_frac or add_frac */
  fp4 = init_frac(1, 8, 42) ;
  fp5 = init_frac(1, 17, 96) ;
  fp6 = add_frac(fp4, fp5) ;
  fp7 = init_frac(-1, 38, 19);
  fp8 = init_frac(1, 10, 98);
  fp9 = init_frac(1, 82, 2);
  fp10 = add_frac(fp3, fp9);
  fp11 = add_frac(fp8, fp9);
  dump_heap();
  fp12 = add_frac(fp6, fp8);
  fp13 = add_frac(fp8, fp6);
  fp14 = add_frac(fp13, fp1);
  fp15 = add_frac(fp7, fp2);
  fp16 = add_frac(fp12, fp5);
  fp17 = add_frac(fp2, fp2);
  fp18 = add_frac(fp1, fp14);
  fp19 = add_frac(fp18, fp12);
  fp20 = add_frac(fp10, fp4);
  /* show full heap */
  dump_heap();
  /* delete 2 fracs then add new ones */
  del_frac(fp18);
  del_frac(fp2);
  dump_heap() ;
  fp2 = init_frac(2, 2, 2);
  fp18 = init_frac(18, 18, 18);
  dump_heap();
  /* try to add to heap when full */
  fp21 = init_frac(1, 1, 1);

  return 0 ;
}
