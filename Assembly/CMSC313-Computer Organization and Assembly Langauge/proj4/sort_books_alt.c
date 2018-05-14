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
  int numBooks = 0;
  int numEntries = 0;
  char temp[80];
  int i = 0;
  int j = 0;
  char names[200][80];
  char *ptr;

  /* array full of book data */
  while(scanf("%[^,]%*c%*c", &temp)==1)
    {
      strcpy(names[j], temp);
      j++;
      i++;
      if (i == 3)
        {
          scanf("%[^\n]", &temp);
          strcpy(names[j], temp);
          j++;
          i = 0;
          numEntries++;
          numBooks++;
          scanf("%*c", &temp); /* get rid of new line char */
        }
      numEntries++;
    }

  /* move data into struct */
  i = 0;
  j = 0;
  for (i; i<numEntries; i++)
    {
      strncat(books[j].title, names[i], TITLE_LEN);
      strcat(books[j].title, "\0"); /* null terminate string */
      i++;
      strncat(books[j].author, names[i], AUTHOR_LEN);
      strcat(books[j].author, "\0");
      i++;
      strncat(books[j].subject, names[i], SUBJECT_LEN);
      strcat(books[j].subject, "\0");
      i++;
      books[j].year = strtol(names[i], &ptr, 10);
      j++;
    }

  sort_books(books, numBooks);

  print_books(books, numBooks);

  exit(1);
}

void sort_books(struct book books[], int numBooks)
{
  int i, j, min;
  int cmpResult;

  for (i = 0; i < numBooks - 1; i++) {
    min = i;
    for (j = i + 1; j < numBooks; j++)
      {
        /* Copy pointers to the two books to be compared into the
         * global variables book1 and book2 for bookcmp() to see
         */
        book1 = &books[i];
        book2 = &books[j];

        cmpResult = bookcmp();
        /* bookcmp returns result in register EAX--above saves
         * it into cmpResult */

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

void print_books(struct book books[], int numBooks)
{
  int i = 0;
  for (i; i<numBooks; i++)
    {
      printf("%s, %s, %s, %ld\n", books[i].title, books[i].author, books[i].subject, books[i].year);
    }
}
