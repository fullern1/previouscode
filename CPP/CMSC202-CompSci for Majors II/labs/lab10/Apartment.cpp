//apartment.cpp

#include <iostream>
#include "Apartment.h"

using namespace std;

Apartment::Apartment(int story, bool washer) :
  m_story(story){
  m_washer = washer;
}

int Apartment::GetStory(){
  return m_story;
}

ostream& operator<<(ostream& out, Apartment& apt){
  out << "Number of Rooms: " << apt.GetRooms() << endl
      << "Number of Walls: " << apt.GetWalls() << endl
      << "Washer: " << apt.GetWasher() << endl
      << "Number of Windows: " << apt.NumWindows() << endl
      << "Property Value: " << apt.PropertyValue() << endl
      << "Story: " << apt.GetStory() << endl;
  
  return out;
}
