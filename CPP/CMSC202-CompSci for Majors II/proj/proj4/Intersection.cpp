/*
 * STUDENTS - DO NOT MODIFY THIS FILE
 *
 * The Intersection class is derived from the WalkVertex class
 * and is provided as an example for the interface and implementation
 * of the SafeHouse and PoliceStation classes.
 *
 */

#include <iostream> 
#include <sstream>   // Needed for stringstream class
#include "Intersection.h"

using namespace std;

Intersection::Intersection() 
  : WalkVertex()
{ /* empty constructor body */ }

Intersection::Intersection(string description) 
  : WalkVertex(description)
{ /* empty constructor body */ }

string Intersection::ToString() const {
  // Use the stringstream class to create the string representation.
  stringstream ss;
  ss << "ID " << GetID() <<": Intersection (" << m_description << ")";
  return ss.str();
}

walk_status_t Intersection::Status() const {
  // Always return CONTINUE for an Intersection object.
  return CONTINUE;
}
