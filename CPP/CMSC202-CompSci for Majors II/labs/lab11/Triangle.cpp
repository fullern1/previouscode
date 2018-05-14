#include "Triangle.h"
#include "Shape.h"
#include <iostream>

using namespace std;

Triangle::Triangle(int length, int height){
  m_length = length;
  m_height = height;
}

Triangle::~Triangle(){
}

int Triangle::GetArea() const {
  return ((m_length*m_height)/2);
}

void Triangle::Draw() const {
  cout << "Triangle Draw." << endl;
}
