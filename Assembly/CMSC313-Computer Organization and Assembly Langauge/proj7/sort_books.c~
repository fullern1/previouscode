/* Nathaniel Fuller
 * CMSC 313 proj7
 * sort_books.c
 */

/* stdlib.h include doesn't seem to be needed
 * though leaving it out gives the warning:
 * warning: implicit declaration of function ‘qsort'
 */
#include <stdlib.h>
#include "book.h"

/* program seemed to work normally w/ following declaration instead of current
 * one being used:
 * extern int bookcmp(void);
 */
extern int bookcmp(const struct book*, const struct book*);
void sort_books(struct book books[], int numBooks);
typedef int (* COMP_FUNC_PTR)(const void *, const void *);

void sort_books(struct book books[], int numBooks)
{
  qsort(books, numBooks, sizeof(struct book), (COMP_FUNC_PTR) &bookcmp);
}
