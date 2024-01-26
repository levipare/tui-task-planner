#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
  enum class Month {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
  };

  enum class WeekDay {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
  };

private:
  int year;
  int month;
  int day;

public:
  Date();

  Date(int day, int month, int year);

  // Getters
  int get_day();

  int get_month();

  int get_year();

  // Setters
  void set_day(int d);

  void set_month(int m);

  void set_year(int y);

  // Utils
  WeekDay week_day();

  Month month_name();
};

std::string week_day_to_string(Date::WeekDay);

std::string month_to_string(Date::Month);

#endif
