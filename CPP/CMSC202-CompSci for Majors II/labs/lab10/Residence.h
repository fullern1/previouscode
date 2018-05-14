//residence.h

#ifndef RESIDENCE_H
#define RESIDENCE_H

#include <iostream>

using namespace std;

class Residence {
 public:
  //Default constructor, values set to 4, 4, true
  Residence();

  //Class constructor from user input
  Residence(int numRooms, int numWalls, bool WasherVal);

  //Returns double value of property value (number of rooms * 10000)
  double PropertyValue();

  //Returns int value of num of windows (num of walls * 2)
  int NumWindows();

  //Return values for rooms/walls/washer
  int GetRooms();
  int GetWalls();
  bool GetWasher();

 protected:
  //Returns bool value if residence has washer or not
  bool HasWasher();

  int m_rooms;
  int m_walls;
  bool m_washer;

};

ostream& operator<<(ostream& out, Residence& res);

#endif
