#ifndef EVENT_H
#define EVENT_H

#include "date.h"

#include <chrono>
#include <string>

class Task {
private:
  std::string name;
  Date date;
  bool completed;

public:
  Task(std::string name, Date date);

  // Getters
  std::string get_name() const;

  Date get_date() const;

  bool get_completed() const;

  // Setters
  void set_name(std::string new_name);

  void set_date(Date date);

  void set_completed(bool c);
};

#endif
