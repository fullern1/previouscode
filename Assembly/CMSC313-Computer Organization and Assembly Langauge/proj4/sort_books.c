#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Following is straight from the project description
 */
#define TITLE_LEN       32
#define AUTHOR_LEN      20
#define SUBJECT_LEN     10

struct book {
  char title[TITLE_LEN + 1];
  char author[AUTHOR_LEN + 1];    /* first author */
  char subject[SUBJECT_LEN + 1];  /* Nonfiction, Fantasy, Mystery, ... */
  unsigned int year;              /* year of e-book release */
};


/*
 * Declarations for functions that are defined in other files
 */
extern int bookcmp(void);

/*
 * Declarations for global variables that need to be accessed
 * from other files
 */

/* global book pointers book1 and book 2 */
struct book *book1;
struct book *book2;

#define MAX_BOOKS 100

int main(int argc, char **argv) {
  struct book books[MAX_BOOKS];
  int numBooks;
  char temptitle[80];
  int i;
  /*
  FILE *myFile;
    
  myFile = fopen("books.dat", "r");
  if (myFile == NULL)
    {
      printf("Failed to load file.\n");
      exit(-1);
    }
  */
  for (i = 0; i < MAX_BOOKS; i++) 
    {
      /* Sample line: "Breaking Point, Pamela Clare, Romance, 2011" */
      
      /* read file contents into approprate places */
      /*
	if (fscanf(myFile, "%80[^,], %20[^,], %10[^,], %u \n", temptitle, books[i].author, books[i].subject, &books[i].year) == EOF){
      */
      if (scanf("%80[^,], %20[^,], %10[^,], %u \n", temptitle, books[i].author,
		books[i].subject, &books[i].year) == EOF)
	{
	  numBooks = i;
	  break;
	}
      else
	{
	  strncpy(books[i].title, temptitle, 32);
	  books[i].title[32] = 0;
	}
    }
  /*
  fclose(myFile); /* Finished reading, close file */
  /* Following assumes you stored actual number of books read into
   * var numBooks
   */

  sort_books(books, numBooks);

  print_books(books, numBooks);

  exit(1);
}

/*
 * sort_books(): receives an array of struct book's, of length
 * numBooks.  Sorts the array in-place (i.e., actually modifies
 * the elements of the array).
 *
 * This is almost exactly what was given in the pseudocode in
 * the project spec--need to replace STUBS with real code
 */
void sort_books(struct book books[], int numBooks) {
  int i, j, min;
  int cmpResult;

  for (i = 0; i < numBooks - 1; i++) {
    min = i;
    for (j = i + 1; j < numBooks; j++)
      {
        /* Copy pointers to the two books to be compared into the
         * global variables book1 and book2 for bookcmp() to see
         */
        book1 = &books[min];
        book2 = &books[j];

	cmpResult = bookcmp();
        /* bookcmp returns result in register EAX--above saves
         * it into cmpResult 
	 */

        /* if book1 is greater than book2 cmpResult = 1 and min = j
         * if book1 is less than book2 cmpresult = -1 and nothing changes
         */
        if (cmpResult == 1)
          {
            min = j;
          }
      }
    if (min != i)
      {
        /* Swap books[i], books[min] */
        struct book temp = books[i];
        books[i] = books[min];
        books[min] = temp;
      }
  }
}

void print_books(struct book books[], int numBooks) {

  /* STUB: ADD CODE HERE TO OUTPUT LIST OF BOOKS */
  /* get number of books to print out */
  int i;
  for (i = 0; i < numBooks; i++)
    {
      printf("%s, %s, %s, %d\n", books[i].title, books[i].author, books[i].subject, books[i].year);
    }
}
