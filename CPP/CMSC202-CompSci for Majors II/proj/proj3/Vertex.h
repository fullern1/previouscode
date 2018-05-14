//Vertex.h

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

using namespace std;

class Vertex {
 public:

  /* Vertex() - default constructor
     Preconditions: none
     Postconditions: creates a Vertex object with
     unique integer ID. */

  Vertex();

  /* GetID() - returns the ID of the Vertex object.
     Preconditions: none
     Postconditions: returns the integer ID of the
     Vertex object. */

  int GetID() const;

  /* operator<< - overload output operator
     Preconditions: none
     Postconditions: Prints a vertex as 
     "ID: v"
     where v is the given vertex ID */
  
 private:

  friend ostream& operator<<(ostream &sout, const Vertex &v);

  int m_vertexID;
};

#endif
