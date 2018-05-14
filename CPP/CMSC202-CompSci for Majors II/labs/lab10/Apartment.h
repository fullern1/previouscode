//apartment.h

#ifndef APARTMENT_H
#define APARTMENT_H

#include "Residence.h"

using namespace std;

class Apartment : public Residence{
 public:
  //Constructor
  Apartment(int story, bool washer);

  //Returns value of m_story
  int GetStory();

 private:
  int m_story;

};

ostream& operator<<(ostream& out, Apartment& apt);

#endif

