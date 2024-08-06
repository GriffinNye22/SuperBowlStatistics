/**
 * @file Date.cpp
 * @author Dr. Spiegel
 * @brief Member function implementation for Date class
 */

#include <iostream>
#include "Date.h"

using namespace std;

// Initialize static member at file scope; 
// one class-wide copy.
const int Date::days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

/**Date(Constructor):
 * @brief Creates an instance of the date object.
 * @param m - the month
 * @param d - the day
 * @param y - the year
 */
Date::Date( int m, int d, int y ) 
{ setDate( m, d, y );}

/**Date(Copy Constructor):
 * @brief Creates a copy of the the date object
 * @param d - the Date object to copy
 */
Date::Date(const Date &d)
{setDate(d.month,d.day,d.year);}

/** setMonth:
 * @brief Sets month. If value is out of range, set to default of 1
 * @param mm - the month
 */
void Date::setMonth(int mm)
{  month = (mm >= 1 && mm <= 12) ? mm : 1;
}

/** setDay:
 * @brief Sets day. If value is out of range, set to default of 1
 * @param dd - the day
 */
void Date::setDay(int dd)
{  // Test for a leap year to determine #days in Feb.
   if (month == 2 && leapYear())  // Feb in a leap year
      day = (dd >= 1 && dd <= 29) ? dd : 1;
   else
      day = (dd >= 1 && dd <= days[month]) ? dd : 1;
}

/** setYear:
 * @brief Sets year. If value is out of range, set to default of 2005
 * @param yy - the year
 */
void Date::setYear(int yy)
{  year = (yy >= 1700 && yy <= 2100) ? yy : 2005;
}

/** getMonth:
 * @brief Returns the month
 * @return month - the month
 */
int Date::getMonth()
{  return(month); 
}

/** getDay:
 * @brief Returns the day
 * @return day - the day
 */
int Date::getDay()
{  return(day);
}

/** getYear:
 * @brief Returns the year.
 * @return year - the year
 */
int Date::getYear()
{  return(year);
}

/** setDate:
 * @brief Sets the date.
 * @param mm - the month
 * @param dd - the day
 * @param yy - the year
 */
void Date::setDate(int mm, int dd, int yy )
{  setMonth(mm);
   setDay(dd);
   setYear(yy);
}

/** getDate:
 * @brief Returns the date via reference parameters
 * @param m - the month data member
 * @param d - the day data member
 * @param y - the year data member
 */
void Date::getDate(int &m,int &d,int &y)
{  m=getMonth();
   d=getDay();
   y=getYear();
}

/** operator++():
 * @brief Preincrement operator overloaded as a member function.
 *        Calls helpIncrement to increment the date.
 * @return *this - the current date object.
 */
// Preincrement operator overloaded as a member function.
Date &Date::operator++()
{
   helpIncrement();
   return *this;  // reference return to create an lvalue
}

/** operator++(int):
 * @brief Postincrement operator overloaded as a member function.
 *        Calls helpIncrement to increment the date.
 * @param int - dummy parameter. Notice it does not have a parameter name.
 * @return temp - the non-incremented, saved, temporary object.
 */
Date Date::operator++( int )
{
   Date temp = *this;
   helpIncrement();

   // return non-incremented, saved, temporary object
   return temp;   // value return; not a reference return
}

/** operator+=:
 * @brief Addition assignment operator overloaded as a member function.
 *        Calls helpIncrement to increment the date.
 * @param additionalDays - the number of days to add to the date
 * @return *this - the incremented Date object
 */
const Date &Date::operator+=( int additionalDays )
{
   for ( int i = 0; i < additionalDays; i++ )
      helpIncrement();

   return *this;    // enables cascading
}


/** leapYear():
 * @brief Determines whether the year for the current Date object is a leap year.
 * @return Boolean - True, if a leap year, otherwise, false.
 */
bool Date::leapYear()
{
   if ( year % 400 == 0 || ( year % 100 != 0 && year % 4 == 0 ) )
      return true;   // a leap year
   else
      return false;  // not a leap year
}

/** leapYear(int):
 * @brief Determines whether the year entered is a leap year.
 * @param y - the year
 * @return Boolean - True, if a leap year, otherwise, false.
 */
bool leapYear(int y)
{
   if ( y % 400 == 0 || ( y % 100 != 0 && y % 4 == 0 ) )
      return true;   // a leap year
   else
      return false;  // not a leap year
}

/** endOfMonth:
 * @brief Determines whether a day is the end of the month.
 * @return Boolean - boolean expression checking the appropriate number of days.
 */
bool Date::endOfMonth()
{
   if ( month == 2 && leapYear() )
      return day == 29; // last day of Feb. in leap year
   else
      return day == days[ month ];
}

/** helpIncrement:
 * @brief Checks for end of month and end of year when incrementing date.
 */
void Date::helpIncrement()
{
   if ( endOfMonth() && month == 12 ) {  // end year
      day = 1;
      month = 1;
      ++year;
   }
   else if ( endOfMonth() ) {            // end month
      day = 1;
      ++month;
   }
   else       // not end of month or year; increment day
      ++day;
}

/** operator<<:
 * @brief Stream extraction operator overloaded as a member function.
 *        Prints and/or writes the date to a file.
 * @param output - the output stream
 * @param d - the date to pass to the stream extraction operator.
 * @return output - the output stream.
 */
ostream &operator<<( ostream &output, const Date &d )
{
   static char *monthName[ 13 ] = { "", "January",
      "February", "March", "April", "May", "June",
      "July", "August", "September", "October",
      "November", "December" };

   output << monthName[ d.month ] << ' '
          << d.day << ", " << d.year;

   return output;   // enables cascading
}

