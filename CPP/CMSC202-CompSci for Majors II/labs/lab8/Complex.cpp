#include "Complex.h"

// Complex class constructor
Complex::Complex(double real, double imaginary) : 
  m_real(real), m_imaginary(imaginary)
{
  
}

// Accessor that returns real part of complex number
double Complex::GetReal() const
{
  return m_real;
}

// Accessor that returns imaginary part of complex number
double Complex::GetImaginary() const
{
  return m_imaginary;
}

// Start writing your code here ....
//Overloaded operator +
const Complex Complex::operator+(const Complex & rhs) const
{
  double realResult = m_real+rhs.m_real;
  double imagResult = m_imaginary+rhs.m_imaginary;
  Complex result(realResult, imagResult);
  return result;
}

const Complex Complex::operator-() const
{
  double realResult = m_real;
  if (realResult != 0)
    realResult = -m_real;
  double imagResult = -m_imaginary;
  Complex result(realResult, imagResult);
  return result;
}

ostream& operator<<(ostream& out, const Complex& number)
{
  double realNum = number.GetReal();
  double imagNum = number.GetImaginary();
  if (imagNum > 0){
    out << realNum << "+" << imagNum << "i" << endl;
    return out;
  }
  else{
    out << realNum << imagNum << "i" << endl;
    return out;
  }
}
