/*
  Nathaniel Fuller
  fullern1@umbc.edu
  CMSC 421 hw3

  --pthread_join may be giving threads extra time to get candy - more than 
  allowed (finishing last house)

  https://computing.llnl.gov/tutorials/pthreads/samples/hello.c
  http://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/
  http://www.thegeekstuff.com/2012/05/c-mutex-examples/?refcom
  https://stackoverflow.com/questions/11624545/how-to-make-main-thread-wait-for-all-child-threads-finish
  https://stackoverflow.com/questions/8487380/how-to-cast-an-integer-to-void-pointer
  https://stackoverflow.com/questions/26805461/why-do-i-get-cast-from-pointer-to-integer-of-different-size-error

  QUESTIONS:
  1) A group may collect candy during this print out
  2) To prevent this you could lock all houses while printing info out
 */

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

// house struct to store data for each house (pos and num of candy)
struct house{
  int candy; // amount of candy at house
  int x; // x coordinate
  int y; // y coordinate
  pthread_mutex_t lock;
};

struct group{
  int candyCount;
  int homeHouse;
  int goingTo;
  int size;
};

// global variables
struct house houses[10];
struct group groups[500];
int numGroups;
int currTime = 0;
int timeLimit;

void *NBThread(void *myFile){
  char input[50];
  char a[10];
  char b[10];
  FILE *fptr = (FILE *)myFile;

  // wait for 250 ms
  if(usleep(250*1000) == -1){
    printf("Error sleeping\n");
    exit(1);
  }
  
  while (fgets(input, 50, fptr) != NULL){
    // check time limit
    if (currTime >= timeLimit){
      pthread_exit(NULL);
    }

    // get data from line
    sscanf(input, "%s %s", a, b);

    //get lock for appropriate house
    pthread_mutex_lock(&houses[atoi(a)].lock);

    // add candy to house
    houses[atoi(a)].candy += atoi(b);
    /* debugging output
    printf("NB: added %d to house %d\n", atoi(b), atoi(a)); 
    */
    
    // release lock
    pthread_mutex_unlock(&houses[atoi(a)].lock);
    
    // sleep
    if(usleep(250*1000) == -1){
      printf("Error sleeping\n");
      exit(1);
    }
  }

  pthread_exit(NULL);
}

void *ChildThread(void *group){
  int gNum = (uintptr_t)group;

  int temp = 0;
  temp += abs(houses[groups[gNum].goingTo].x-houses[groups[gNum].homeHouse].x);
  temp += abs(houses[groups[gNum].goingTo].y-houses[groups[gNum].homeHouse].y);

  /* debugging output
  printf("Group %d: from house %d to %d (travel time = %d)\n", gNum,
	 groups[gNum].homeHouse, groups[gNum].goingTo, 250*temp);
  */
  // sleep for time needed to get to house
  if(usleep(temp*250*1000) == -1){
    printf("Error sleeping\n");
    exit(1);
  }
  
  while (1){
    // get lock
    pthread_mutex_lock(&houses[groups[gNum].goingTo].lock);
    
    // do work - trick or treating
    if (houses[groups[gNum].goingTo].candy >= groups[gNum].size){
      groups[gNum].candyCount += groups[gNum].size;
      houses[groups[gNum].goingTo].candy -= groups[gNum].size;

      /* debugging output
      printf("Group %d took %d from house %d\n", gNum, groups[gNum].size,
	     groups[gNum].goingTo);
      */
    }
    
    // release lock
    pthread_mutex_unlock(&houses[groups[gNum].goingTo].lock);
    
    // check if time limit reached 
    if (currTime >= timeLimit){
      // close thread and exit if time limit reached
      pthread_exit(NULL);
    } else {
      // get random house num
      int rnum = rand() % 10; // rand value from 0 - 9
      int mySum = 0; // x and y of new minus x and y of old (abs value)
      mySum += abs(houses[rnum].x - houses[groups[gNum].goingTo].x);
      mySum += abs(houses[rnum].y - houses[groups[gNum].goingTo].y);

      /* debugging output
      printf("Group %d: from house %d to %d (travel time = %d)\n", gNum,
	 groups[gNum].goingTo, rnum, 250*temp);
      */

      groups[gNum].goingTo = rnum;
      
      // sleep for time needed to get to house
      if(usleep(mySum*250*1000) == -1){
	printf("Error sleeping\n");
	exit(1);
      }
    }
  }
}

int main(int argc, char ** argv){
  // program only takes 2 arguments - input data file and time to simulate
  // minimum verification of correct input
  // assuming user will at least enter arguments correctly
  if (argc != 3){
    printf("Incorrect input\n");
    return 0; // exit
  }

  srand((unsigned int) time(NULL));

  // initialize needed vars
  FILE *fptr;
  char input[50];
  timeLimit = atoi(argv[2]);
  char a[10]; // used for reading in  values as strings before converting to int
  char b[10]; // at least it works
  char c[10];
  
  // open file to read
  fptr = fopen(argv[1], "r"); 

  // get number of groups from first line and store in G
  if (fgets(input, 50, fptr) == NULL){
    printf("Error reading from file\n");
    return 0; // exit
  }
  numGroups = atoi(input);

  // get data about 10 houses from next 10 lines and store in houses var
  for (int i = 0; i < 10; i++){
    if (fgets(input, 50, fptr) == NULL){
      printf("Error reading from file\n");
      return 0;
    }
    sscanf(input, "%s %s %s", a, b, c); // reading directly in as int wasn't
    houses[i].x = atoi(a); // working so using this workaround to get data
    houses[i].y = atoi(b);
    houses[i].candy = atoi(c);
    if (pthread_mutex_init(&houses[i].lock, NULL) != 0){
      printf("Error with mutex init\n");
      return 1;
    }
  }

  pthread_t threads[numGroups+1]; // groups threads + 1 for neighborhood thread

  // spawn child threads
  for (int i = 0; i < numGroups; i++){
    // read in child data for each group
    if (fgets(input, 50, fptr) == NULL){
      printf("Error reading from file\n");
      return 0;
    }
    sscanf(input, "%s %s", a, b);
    groups[i].homeHouse = atoi(a);
    groups[i].size = atoi(b);
    groups[i].candyCount = 0;
    groups[i].goingTo = rand() % 10;
    if (pthread_create(&threads[i], NULL, ChildThread, (void *)(intptr_t)i)){
      fprintf(stderr, "Error creating thread\n");
      return 1;
    }
  }

  // spawn NBThread
  if (pthread_create(&threads[numGroups], NULL, NBThread, fptr)){
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }

  // all threads spawned, once per second print info till time is up
  while (1){
    // check if time limit exceeded
    if (currTime > timeLimit){
      break;
    }
    if (currTime == timeLimit){
      // wait for group threads to finish
      printf("Waiting for all groups to finish...\n");
      for (int i = 0; i < numGroups; i++){
	if(pthread_join(threads[i], NULL) != 0){
	  printf("Error joining threads\n");
	  return 1;
	}
      }
    }
    
    // get all locks so nothing can be changed
    for (int i = 0; i < 10; i++){
      pthread_mutex_lock(&houses[i].lock);
    }
    // print info
    printf("After %d seconds:\n", currTime);
    printf(" Group statuses:\n");
    for (int i = 0; i < numGroups; i++){
      printf("  %d: size %d, going to %d, collected %d\n", i, groups[i].size, groups[i].goingTo, groups[i].candyCount);
    }
    printf(" House statuses:\n");
    int sum = 0;
    for (int i = 0; i < 10; i++){
      printf("  %d @ (%d, %d): %d available\n", i, houses[i].x, houses[i].y, houses[i].candy);
      sum = sum + houses[i].candy;
    }
    printf(" Total candy: %d\n", sum);
    // unlock all locks in reverse order
    for (int i = 9; i >= 0; i--){
      pthread_mutex_unlock(&houses[i].lock);
    }
    
    // wait 1 second
    if (usleep(1000000) == -1){
      printf("Error sleeping\n");
      return 1;
    }
    currTime = currTime + 1;
  }
  
  // close file when finished reading from file
  fclose(fptr);
  // destroy locks
  for (int i = 0; i < 10; i++){
    pthread_mutex_destroy(&houses[i].lock);
  }
  return 0;
}
