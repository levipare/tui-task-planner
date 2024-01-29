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
  /**
   * @brief Constructor to create a task obj
   * @param the name of the task that is shown
   * @param the date of the task
   */
  Task(std::string name, Date date);

  // Getters
  /**
   * @return the name of the task
   */
  std::string get_name() const;

  /**
   * @return the date of the task
   */
  Date get_date() const;

  /**
   * @return the completion status of the task
   */
  bool get_completed() const;

  // Setters
  /**
   * @param new_name the name of the task
   */
  void set_name(std::string new_name);

  /**
   * @param date the date of the task
   */
  void set_date(Date date);

  /**
   * @param c the completion status of the task
   */
  void set_completed(bool c);
};

#endif
