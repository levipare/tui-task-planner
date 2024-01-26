#include "date.h"
#include <ctime>
#include <string>

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
int Date::get_day() { return this->day; }

int Date::get_month() { return this->month; }

int Date::get_year() { return this->year; }

// Setters
void Date::set_day(int d) { this->day = d; }

void Date::set_month(int m) { this->month = m; }

void Date::set_year(int y) { this->year = y; }

// Utils
Date::WeekDay Date::week_day() { return WeekDay(static_cast<int>(this->day)); }

Date::Month Date::month_name() { return Month(this->month); }

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
