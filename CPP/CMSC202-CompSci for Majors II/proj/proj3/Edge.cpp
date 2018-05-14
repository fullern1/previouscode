//Edge.cpp
#include <cstdlib>
#include <iostream>
#include "Edge.h"
#include "Vertex.h"

using namespace std;

Edge::Edge(Vertex *v1, Vertex *v2){
  if (v1 != NULL && v2 != NULL){
    m_v1 = v1;
    m_v2 = v2;
  }
  else{
    cout << "Error: v1 or v2 is NULL." << endl;
    exit(1);
  }
}

Vertex* Edge::GetV1() const{
  return m_v1;
}

Vertex* Edge::GetV2() const{
  return m_v2;
}

void Edge::SetV1(Vertex *v){
  if (v == NULL){
    cout << "Warning: v is NULL, nothing changed." << endl;
  }
  else{
    m_v1 = v;
  }
}

void Edge::SetV2(Vertex *v){
  if (v == NULL){
    cout << "Warning: v is NULL, nothing changed." << endl;
  }
  else{
    m_v2 = v;
  }
}

ostream& operator<<(ostream &sout, const Edge &e){
  sout << "ID: " << e.GetV1()->GetID() << " <--> " << "ID: " 
       << e.GetV2()->GetID() << endl;
  return sout;
}
