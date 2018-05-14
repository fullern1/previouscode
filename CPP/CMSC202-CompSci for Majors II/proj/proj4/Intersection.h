/*
 * STUDENTS - DO NOT MODIFY THIS FILE
 *
 * The Intersection class is derived from the WalkVertex class
 * and is provided as an example for the interface and implementation
 * of the SafeHouse and PoliceStation classes.
 *
 */

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "WalkVertex.h"

using namespace std;

class Intersection : public WalkVertex {
 public:

  /* Intersection() - default constructor
     Preconditions: none
     Postconditions: creates Intersection object with unique ID and
     description "(none)".                                           */

  Intersection();

  /* Intersection() - non-default constructor
     Preconditions: none
     Postconditions: creates Intersection object with unique ID and
     description specified in the argument.                          */

  Intersection(string description);
  
  /* ToString() - string representation of a Intersection object
     Preconditions: none
     Postconditions: returns a string representation of the object.  */

  virtual string ToString() const;

  /* Status() - walk status
     Preconditions: none
     Postconditions: returns status CONTINUE.                        */

  virtual walk_status_t Status() const;
};

#endif
