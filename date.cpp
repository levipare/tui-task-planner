#include "date.h"
#include <ctime>
#include <iostream>
#include <string>

// Constructors
Date::Date() {
  std::time_t t = std::time(nullptr);
  std::tm *now = std::localtime(&t);
  this->day = now->tm_mday;
  this->month = now->tm_mon;
  this->year = now->tm_year + 1900;
}

Date::Date(int day, int month, int year) {
  this->day = day;
  this->month = month;
  this->year = year;
}

// Getters
int Date::get_day() const { return this->day; }

int Date::get_month() const { return this->month; }

int Date::get_year() const { return this->year; }

// Setters
void Date::set_day(int d) { this->day = d; }

void Date::set_month(int m) { this->month = m; }

void Date::set_year(int y) { this->year = y; }

// Overloaded operators
bool Date::operator==(const Date &rhs) const {
  return this->day == rhs.day && this->month == rhs.month &&

         this->year == rhs.year;
}

std::ostream &operator<<(std::ostream &os, const Date &d) {
  os << d.month + 1 << '/' << d.day << '/' << d.year;
  return os;
}

std::size_t Date::operator()(const Date &d) const {
  return std::hash<int>()(d.day) + std::hash<int>()(d.month) +
         std::hash<int>()(d.year);
}

// Utils
Date::WeekDay Date::week_day_enum() const {
  std::tm tm = {};
  tm.tm_year = this->year - 1900;
  tm.tm_mon = this->month;
  tm.tm_mday = this->day;
  std::mktime(&tm);

  return WeekDay(tm.tm_wday);
}

Date::Month Date::month_enum() const { return Month(this->month); }

std::string week_day_to_string(Date::WeekDay d) {
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

std::string month_to_string(Date::Month m) {
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
