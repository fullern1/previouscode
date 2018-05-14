//policestation.cpp

#include <iostream>
#include <sstream>
#include <cstdlib>
#include "PoliceStation.h"

using namespace std;

PoliceStation::PoliceStation()
  : WalkVertex("(none)"), m_probCaught(1.0){
  /* empty constructor body */
}

PoliceStation::PoliceStation(double probCaught, string description)
  : WalkVertex(description), m_probCaught(probCaught){
  /* empty constructor body */
}

string PoliceStation::ToString() const {
  //ss class to create string representation
  stringstream ss;
  ss << "ID " << GetID() << ": PoliceStation (" << m_description << ")";
  return ss.str();
}

walk_status_t PoliceStation::Status() const {
  //Return FAILURE or CONTINUE depending on m_probCaught and rand()
  double r = (RAND_MAX - rand()) / static_cast<double>(RAND_MAX);
  if (r < m_probCaught){
    return FAILURE;
  }
  else{
    return CONTINUE;
  }
}
