#include "task.h"
#include "date.h"
#include <chrono>
#include <string>

Task::Task(std::string name, Date date) {
  this->name = name;
  this->date = date;
}

// Getters
std::string Task::get_name() const { return this->name; }

Date Task::get_date() const { return this->date; }

bool Task::get_completed() const { return this->completed; }

// Setters
void Task::set_name(std::string name) { this->name = name; }

void Task::set_date(Date date) { this->date = date; }

void Task::set_completed(bool c) { this->completed = c; }
