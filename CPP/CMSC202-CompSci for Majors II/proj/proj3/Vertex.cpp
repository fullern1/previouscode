//Vertex.cpp

#include <iostream>
#include "Vertex.h"

using namespace std;

static int vertexCount = 0;

Vertex::Vertex()
  : m_vertexID(vertexCount){
  vertexCount++;
}

int Vertex::GetID() const{
  return m_vertexID;
}

ostream& operator<<(ostream &sout, const Vertex &v){
  sout << "ID: " << v.GetID() << endl;

  return sout;
}
