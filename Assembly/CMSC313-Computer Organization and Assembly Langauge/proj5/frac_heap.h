/* Nathaniel Fuller
 * CMSC 313
 * Proj5
 */

/* create and def fraction */
typedef struct fraction {
  signed char sign;
  unsigned int numerator;
  unsigned int denominator;
} fraction;


/* function prototypes for functions in frac_heap.c */
void init_heap();
fraction *new_frac();
void del_frac(struct fraction *);
void dump_heap();
