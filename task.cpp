#include "task.h"
#include <chrono>
#include <string>

Task::Task(std::string name, std::string detail) {
  this->name = name;
  this->detail = detail;
}

// Getters
std::string Task::get_name() const { return this->name; }

std::string Task::get_detail() const { return this->detail; }

std::chrono::system_clock::time_point Task::get_date() const {
  return this->date;
}

// Setters
void Task::set_name(std::string name) { this->name = name; }

void Task::set_detail(std::string detail) { this->detail = detail; }

void Task::set_date(std::chrono::system_clock::time_point date) {
  this->date = date;
}

// Operator Overloading
bool Task::operator==(const Task &rhs) { return *this == rhs; }
