//safehouse.h

#ifndef SAFEHOUSE_H
#define SAFEHOUSE_H

#include "WalkVertex.h"

using namespace std;

class SafeHouse : public WalkVertex {
 public:
  /* Default constructor - Creates SafeHouse object with unique ID and 
     description of "(none)" */
  SafeHouse();

  /* Non-default constructor - Creates SafeHouse object with unique ID and
     description given as the argument */
  SafeHouse(string description);

  /* Returns string representation of a SafeHouse object */
  virtual string ToString() const;

  /* Returns status SUCCESS */
  virtual walk_status_t Status() const;
};

#endif
