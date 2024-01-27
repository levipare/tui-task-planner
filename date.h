#ifndef DATE_H
#define DATE_H

#include <ctime>
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
  std::tm time;

public:
  // Constructors

  /**
   * @brief Default constructor. Sets the date to the current date.
   */
  Date();

  /**
   * @brief Constructor. Takes in a std::tm object and constructs a Date object
   * based off of it.
   * @param time a std::time object
   */
  Date(std::tm &time);

  /**
   * @brief Constructor. Sets the date to the specified values.
   * @param day the day of the month  1 - 31
   * @param month months since January 0 - 11
   * @param year the year
   */
  Date(int day, int month, int year);

  // Getters

  /**
   * @return the day of the month
   */
  int get_day() const;

  /**
   * @return the month of the year
   */
  int get_month() const;

  /*
   * @return the year
   */
  int get_year() const;

  // Setters
  /**
   * @param d the day of the month
   */
  void set_day(int d);

  /**
   * @param m the month of the year
   */
  void set_month(int m);

  /**
   * @param y the year
   */
  void set_year(int y);

  // Utils
  /**
   * @brief Change the date by +/- amount of days
   * @param days the amount of the days to add/remove
   */
  void change_by_days(int days);

  /**
   * @brief Change the date by +/- amount of days
   * @param days the amount of the days to add/remove
   */
  void change_by_months(int months);

  /**
   * @brief Change the date by +/- amount of days
   * @param days the amount of the days to add/remove
   */
  void change_by_years(int years);

  /**
   * @return week day enum
   */
  WeekDay week_day_enum() const;

  /**
   * @return month enum
   */
  Month month_enum() const;

  // Overloaded operators
  bool operator==(const Date &rhs) const;

  bool operator<(const Date &rhs) const;

  friend std::ostream &operator<<(std::ostream &os, const Date &d);

  /**
   * @brief Get string representation of WeekDay enum ex. Wednesday
   * @return week day name
   */
  static std::string week_day_to_string(Date::WeekDay);

  /**
   * @brief Get string representation of Month enum ex. February
   * @return month name
   */
  static std::string month_to_string(Date::Month);
};

#endif
