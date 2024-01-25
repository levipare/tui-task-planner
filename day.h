#ifndef DAY_H
#define DAY_H

#include <string>

enum class Day {
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
};

std::string day_to_string(Day d);

std::string day_to_string_short(Day d);

#endif
