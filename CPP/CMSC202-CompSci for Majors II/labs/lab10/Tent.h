//tent.h

#ifndef TENT_H
#define TENT_H

#include "Residence.h"

using namespace std;

class Tent : public Residence{
 public:
  //Constructor for tent
  Tent();

  //Overrides to return double value of 0
  double PropertyValue();

  //Overrides to return int value of 0
  int NumWindows();

};

#endif
