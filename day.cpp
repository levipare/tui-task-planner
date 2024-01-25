#include "day.h"
#include <string>

std::string day_to_string(Day d) {
  switch (d) {
  case Day::SUNDAY:
    return "Sunday";
  case Day::MONDAY:
    return "Monday";
  case Day::TUESDAY:
    return "Tuesday";
  case Day::WEDNESDAY:
    return "Wednesday";
  case Day::THURSDAY:
    return "Thursday";
  case Day::FRIDAY:
    return "Friday";
  case Day::SATURDAY:
    return "Saturday";
  }
}

std::string day_to_string_short(Day d) {
  switch (d) {
  case Day::SUNDAY:
    return "Sun";
  case Day::MONDAY:
    return "Mon";
  case Day::TUESDAY:
    return "Tue";
  case Day::WEDNESDAY:
    return "Wed";
  case Day::THURSDAY:
    return "Thu";
  case Day::FRIDAY:
    return "Fri";
  case Day::SATURDAY:
    return "Sat";
  }
}
