// File: Fraction.h

#ifndef FRACTION_H
#define FRACTION_H

class Fraction {
 public:
  void Output();
  Fraction Reciprocal();
  void frac();
  void frac(int numerator, int denominator);

 private:
  int m_numerator;
  int m_denominator;
};

#endif
