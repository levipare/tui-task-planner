#include "date.h"
#include <ctime>
#include <iostream>
#include <string>

// Constructors
Date::Date() {
  std::time_t t = std::time(nullptr);
  std::tm *now = std::localtime(&t);
  this->time = *now;
  std::mktime(&this->time);
}

Date::Date(std::tm &t) {
  this->time.tm_mday = t.tm_mday;
  this->time.tm_mon = t.tm_mon;
  this->time.tm_year = t.tm_year;
  std::mktime(&this->time);
}

Date::Date(int day, int month, int year) {
  // Weird behavior with ctime where the firt call of
  // std::mktime uses a seemingly random timezone
  std::time_t t = std::time(nullptr);
  this->time = *std::localtime(&t);
  this->time.tm_mday = day;
  this->time.tm_mon = month;
  this->time.tm_year = year - 1900;
  std::mktime(&this->time);
}

// Getters
int Date::get_day() const { return this->time.tm_mday; }

int Date::get_month() const { return this->time.tm_mon; }

int Date::get_year() const { return this->time.tm_year + 1900; }

// Setters
void Date::set_day(int d) {
  this->time.tm_mday = d;
  std::mktime(&this->time);
}

void Date::set_month(int m) {
  this->time.tm_mon = m;
  std::mktime(&this->time);
}

void Date::set_year(int y) {
  this->time.tm_year = y - 1900;
  std::mktime(&this->time);
}

// Utils
void Date::change_by_days(int days) {
  this->time.tm_mday += days;
  std::mktime(&this->time);
}

void Date::change_by_months(int months) {
  this->time.tm_mon += months;
  std::mktime(&this->time);
}

void Date::change_by_years(int years) {
  this->time.tm_year += years;
  std::mktime(&this->time);
}

Date::Month Date::month_enum() const { return Month(this->time.tm_mon); }

Date::WeekDay Date::week_day_enum() const {
  return WeekDay(this->time.tm_wday);
}

// Overloaded operators
bool Date::operator==(const Date &rhs) const {
  return this->time.tm_mday == rhs.time.tm_mday &&
         this->time.tm_mon == rhs.time.tm_mon &&
         this->time.tm_year == rhs.time.tm_year;
}

bool Date::operator<(const Date &rhs) const {
  if (this->time.tm_year < rhs.time.tm_year) {
    return true;
  } else if (this->time.tm_year == rhs.time.tm_year) {
    if (this->time.tm_mon < rhs.time.tm_mon) {
      return true;
    } else if (this->time.tm_mon == rhs.time.tm_mon) {
      return this->time.tm_mday < rhs.time.tm_mday;
    }
  }

  return false;
}

std::ostream &operator<<(std::ostream &os, const Date &d) {
  os << d.time.tm_mon + 1 << '/' << d.time.tm_mday << '/'
     << d.time.tm_year + 1900;
  return os;
}

// Extra
std::string Date::week_day_to_string(Date::WeekDay d) {
  switch (d) {
  case Date::WeekDay::SUNDAY:
    return "Sunday";
  case Date::WeekDay::MONDAY:
    return "Monday";
  case Date::WeekDay::TUESDAY:
    return "Tuesday";
  case Date::WeekDay::WEDNESDAY:
    return "Wednesday";
  case Date::WeekDay::THURSDAY:
    return "Thursday";
  case Date::WeekDay::FRIDAY:
    return "Friday";
  case Date::WeekDay::SATURDAY:
    return "Saturday";
  }
}

std::string Date::month_to_string(Date::Month m) {
  switch (m) {
  case Date::Month::JANUARY:
    return "January";
  case Date::Month::FEBRUARY:
    return "February";
  case Date::Month::MARCH:
    return "March";
  case Date::Month::APRIL:
    return "April";
  case Date::Month::MAY:
    return "May";
  case Date::Month::JUNE:
    return "June";
  case Date::Month::JULY:
    return "July";
  case Date::Month::AUGUST:
    return "August";
  case Date::Month::SEPTEMBER:
    return "September";
  case Date::Month::OCTOBER:
    return "October";
  case Date::Month::NOVEMBER:
    return "November";
  case Date::Month::DECEMBER:
    return "December";
  }
}
