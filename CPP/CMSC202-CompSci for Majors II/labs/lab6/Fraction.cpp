// File: Fraction.cpp
#include <iostream>
#include "Fraction.h"
#include <stdlib.h>

using namespace std;

void Fraction::frac(){
  m_numerator = 1;
  m_denominator = 1;
}

//PreConditions: denominator != 0.
void Fraction::frac(int numerator, int denominator){
  if (denominator  != 0){
    m_numerator = numerator;
    m_denominator = denominator;
  }
  else{
    cout << "Error: Denominator cannot be zero. Exiting." << endl;
    exit(0);
  }
}

//PreConditions: numerator != 0.
Fraction Fraction::Reciprocal(){
  if (m_numerator != 0){
    int num = m_numerator;
    int den = m_denominator;
    Fraction recip;
    recip.frac(den, num);
    return recip;
  }
  else{
    cout << "Error: Numerator is zero. No reciporical." << endl;
  }
}

void Fraction::Output(){
  cout <<  m_numerator << "/" << m_denominator << endl;
}
