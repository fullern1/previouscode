#include <iostream>
#include "Fraction.h"

using namespace std;

int main()
{
  Fraction frac;
  int numerator;
  int denominator;
  // Create 3 fractions:
  //  - Read the first fraction from the keyboard using cin.
  //    Find the reciprocal of this fraction and print it to the screen.
  cout << "Enter a numerator: ";
  cin >> numerator;
  cout << "Enter a denominator: ";
  cin >> denominator;

  frac.frac(numerator, denominator);
  frac.Output();
  
  Fraction newFrac = frac.Reciprocal();
  newFrac.Output();
  
  //  - The second fraction will be created with default values. You
  //    should also print this to the screen.
  newFrac.frac();
  newFrac.Output();

  //  - Attempt to create a fraction with a denominator of zero, which 
  //    should print an error
  frac.frac(1, 0);

  return 0;  
}
