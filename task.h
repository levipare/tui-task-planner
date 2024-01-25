#ifndef EVENT_H
#define EVENT_H

#include <chrono>
#include <string>

class Task {
private:
  std::string name;
  std::string detail;
  std::chrono::system_clock::time_point date;

public:
  Task(std::string name, std::string detail);

  // Getters
  std::string get_name() const;

  std::string get_detail() const;

  std::chrono::system_clock::time_point get_date() const;

  // Setters
  void set_name(std::string new_name);

  void set_detail(std::string new_detail);

  void set_date(std::chrono::system_clock::time_point date);

  // Overloaded operators
  bool operator==(const Task &rhs);
};

#endif
