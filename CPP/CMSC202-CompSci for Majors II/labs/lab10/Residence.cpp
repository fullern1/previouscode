//residence.cpp

#include <iostream>
#include "Residence.h"

using namespace std;

Residence::Residence() :
  m_rooms(4), m_walls(4), m_washer(true){

}

Residence::Residence(int numRooms, int numWalls, bool WasherVal) :
  m_rooms(numRooms), m_walls(numWalls), m_washer(WasherVal)
{
  
}

double Residence::PropertyValue(){
  double value = m_rooms*10000;
  return value;
}

int Residence::NumWindows(){
  return m_walls*2;
}

bool Residence::HasWasher(){
  if(m_washer == true)
    return true;
  else 
    return false;
}

int Residence::GetRooms(){
  return m_rooms;
}

int Residence::GetWalls(){
  return m_walls;
}

bool Residence::GetWasher(){
  return m_washer;
}

ostream& operator<<(ostream& out, Residence& res){
  out << "Number of Rooms: " << res.GetRooms() << endl 
      << "Number of Walls: " << res.GetWalls() << endl
      << "Washer: " << res.GetWasher() << endl
      << "Number of Windows: " << res.NumWindows() << endl
      << "Property Value: " << res.PropertyValue() << endl;
  return out;
}
