//policestation.h

#ifndef POLICESTATION_H
#define POLICESTATION_H

#include "WalkVertex.h"

using namespace std;

class PoliceStation : public WalkVertex {
 public:
  /*Default constructor - creates policestation with unique ID and 
    description of "(none)" */
  PoliceStation();

  /*Non-default constructor - creates policestation with unique ID and
   description that are given as arguments*/
  PoliceStation(double probCaught, string description);

  /*Overrides virtual ToString() function
   Returns string representation of PoliceStation object*/
  virtual string ToString() const;

  /*Overrides virtual Status() function
   Returns status FAILURE or CONTINUE - Determined pseudo-randomly using 
   m_probCaught and rand()*/
  virtual walk_status_t Status() const;

 private:
  double m_probCaught;
};

#endif
