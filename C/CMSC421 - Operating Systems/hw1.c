/*
Nathaniel Fuller
fullern1@umbc.edu
hw1.c - This program accepts a command line input then scans /proc/ioports and 
iomem for the input. If found it displays the appropriate lines from each file, 
if not found displays the appropriate error message.

Accessed tutorialspoint.com page through google for info on c functions:
strcpy(), strcmp(), etc..
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
  // vars used for reading from files
  FILE *fptr;
  char inputString[100];

  // used to hold strings read in from ioports/iomem
  // iodata, colon, name1 unassigned as they are always going to be given
  char iodata[25];
  char colon[25];
  char name1[25];
  char name2[25] = "";
  char name3[25] = "";
  char clear[25] = "";
  // used to keep track of any lines found for given input
  // if either == 0 after scan then 'No matching entry found...' is output
  int numioports = 0;
  int numiomem = 0;

  if (argc == 1){
    // if == 1, no args given, display error and exit
    printf("No device given.\n");
    exit(0);
  } else if (argc > 2) {
    // if > 2 more than 1 arg given, display error and exit
    printf("Multiple devices given.\n");
    exit(0);
  } else {
    // if == 2 (only other possibility after prev 2 ifs) one device given
    // open ioports for reading, while loop to read through whole file
    fptr = fopen("/proc/ioports", "r");
    printf("ioports:\n");
    while (1){
      // scan file, if NULL (eof), break while loop
      if (fgets(inputString, 100, fptr) == NULL) break;

      sscanf(inputString, "%s %s %s %s %s", iodata, colon, name1, name2, name3);
      // special case for PCI Bus to remove trailing 00..etc
      if (strcmp(name1, "PCI") == 0 && strcmp(name2, "Bus") == 0){
	strcat(name1, " ");
	strcat(name1, name2);
      } else{
	// if not PCI Bus then no trailing numbers
	// if name 2 was changed concatenate to name1
	if (strcmp(name2, "") != 0){
	  strcat(name1, " ");
	  strcat(name1, name2);
	}
	// if name 3 was changed concatenate to name1
	if (strcmp(name3, "") != 0){
	  strcat(name1, " ");
	  strcat(name1, name3);
	}
      }

      // compare input string to name1, if equal print iodata
      if (strcmp(argv[1], name1) == 0){
	printf("%s\n", iodata);
	// increment numioports so "No matching entry" isn't printed
	numioports = numioports + 1;
      }      
      //printf("%s\n", inputString);
      // clear vars for re-use
      strcpy(iodata, clear);
      strcpy(colon, clear);
      strcpy(name1, clear);
      strcpy(name2, clear);
      strcpy(name3, clear);
    }
    if (numioports == 0){
      printf("No matching entry found in /proc/ioports\n");
    }
    // close ioports
    fclose(fptr);

    // open iomem for reading, same process as ioports
    fptr = fopen("/proc/iomem", "r");
    printf("iomem:\n");

    while (1){
      // scan file, if NULL (eof), break while loop
      if (fgets(inputString, 100, fptr) == NULL) break;

      sscanf(inputString, "%s %s %s %s %s", iodata, colon, name1, name2, name3);
      // special case for PCI Bus to remove trailing 00..etc
      if (strcmp(name1, "PCI") == 0 && strcmp(name2, "Bus") == 0){
	strcat(name1, " ");
	strcat(name1, name2);
      } else{
	// if not PCI Bus then no trailing numbers
	// if name 2 was changed concatenate to name1
	if (strcmp(name2, "") != 0){
	  strcat(name1, " ");
	  strcat(name1, name2);
	}
	// if name 3 was changed concatenate to name1
	if (strcmp(name3, "") != 0){
	  strcat(name1, " ");
	  strcat(name1, name3);
	}
      }

      // compare input string to name1, if equal print iodata
      if (strcmp(argv[1], name1) == 0){
	printf("%s\n", iodata);
	// increment numiomem so "No matching entry" isn't printed
	numiomem = numiomem + 1;
      }      
      //printf("%s\n", inputString);
      // clear vars for re-use
      strcpy(iodata, clear);
      strcpy(colon, clear);
      strcpy(name1, clear);
      strcpy(name2, clear);
      strcpy(name3, clear);
    }
    if (numiomem == 0){
      printf("No matching entry found in /proc/iomem\n");
    }
    // close iomem
    fclose(fptr);
  }
  return 0;
}
