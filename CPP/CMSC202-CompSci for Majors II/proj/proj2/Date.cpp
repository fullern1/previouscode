/*
 * Template Date.cpp
 *
 * Students must implement the entire class, including full handling
 * of leap years.
 */


#include <iostream>
#include "Date.h"

using namespace std;

/* IMPLEMENTATION GOES HERE */
Date::Date()
  : m_month(1), m_day(1), m_year(MIN_YEAR)
{ /* Empty body */ }

Date::Date(int month, int day, int year) {
  SetMonth(month);
  SetYear(year);
  SetDay(day);
}

int Date::GetMonth() const {
  return m_month;
}

int Date::GetDay() const {
  return m_day;
}

int Date::GetYear() const {
  return m_year;
}

void Date::SetMonth(int month) {
  if (month >= 1 && month <= 12) {
    m_month = month;
  }
  else {
    m_month = 1;
    cout << "Invalid month. Set to default value 1." << endl;
  }
}

void Date::SetDay(int day) {
  char errMess[80] = "Invalid Day. Set to default value 1.";
  if (day >= 1 && day <= 31) {
    switch(m_month) {
      //Jan, Mar, May, Jul, Aug, Oct, Dec
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      m_day = day;
      break;

      //Apr, Jun, Sep, Nov
    case 4: case 6: case 9: case 11:
      if (day == 31) {
	cout << errMess << endl;
	m_day = 1;
      }
      else {
	m_day = day;
      }
      break;

      //Feb
    case 2:
      //Check if day is greater than 29, set to 1 if it is
      if (day > 29) {
	cout << errMess << endl;
	m_day = 1;
      }
      //Check if day is less than 29, if so set m_day = day
      if (day < 29) {
	m_day = day;
      }
      if (day == 29) {
	//Check if year is a leap year and set day accordingly
	if (m_year % 4 == 0) {
	  if (m_year % 100 == 0) {
	    if (m_year % 400 == 0) {
	      m_day = day;
	    }
	    else {
	      cout << errMess << endl;
	      m_day = 1;
	    }
	  }
	  else {
	    m_day = day;
	  }
	}
	else {
	  cout << errMess << endl;
	  m_day = 1;
	}
      }
      break;

      //If a wrong value somehow makes it in
    default:
      cout << errMess << endl;
      m_day = 1;
    }
  }
  else {
    m_day = 1;
    cout << errMess << endl;
  }
}

void Date::SetYear(int year) {
  //Check that year is between the accepted values
  if (year >= MIN_YEAR && year <= MAX_YEAR) {
    m_year = year;
  }
  else {
    m_year = MIN_YEAR;
    cout << "Invalid year. Set to default value " << MIN_YEAR << "." << endl;
  }
}

void Date::PrintDate() const {
  cout << "Date: " << m_month << "/" << m_day << "/" << m_year << endl;
}
