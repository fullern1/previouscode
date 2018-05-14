#include "Shape.h"
#include <iostream>
using namespace std;

Shape::~Shape()
{
// no code
}

void Shape::Draw() const
{
// Write code here such that we can identify Shape's Draw is invoked
  cout << "Draw Shape." << endl;
}
