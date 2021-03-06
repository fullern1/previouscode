#include "Rectangle.h"
#include "Shape.h"
#include <iostream>

using namespace std;

Rectangle::Rectangle(int length, int width){
  m_length = length;
  m_width = width;
}

Rectangle::~Rectangle(){
}

int Rectangle::GetArea() const {
  return m_length*m_width;
}

void Rectangle::Draw() const {
  cout << "Draw Rectangle." << endl;
}
