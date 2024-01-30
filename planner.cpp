#include "planner.h"
#include "date.h"
#include "renderer.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

Planner::Planner() {}

// Getters
Date Planner::get_selected_date() const { return this->selected_date; }

std::shared_ptr<Task> Planner::get_selected_task() const {
  return this->selected_task;
}

// Setters
void Planner::set_selected_date(Date date) { this->selected_date = date; }

void Planner::set_selected_task(std::shared_ptr<Task> t_ptr) {
  this->selected_task = t_ptr;
}

void Planner::add_task(std::shared_ptr<Task> t_ptr) {
  if (this->tasks[t_ptr->get_date()] == nullptr) {
    this->tasks[t_ptr->get_date()] =
        std::make_shared<std::vector<std::shared_ptr<Task>>>();
  }
  this->tasks[t_ptr->get_date()]->push_back(t_ptr);
}

void Planner::remove_task(std::shared_ptr<Task> t_ptr) {
  auto vec = this->tasks[t_ptr->get_date()];
  auto it = std::find(vec->begin(), vec->end(), t_ptr);
  if (it != vec->end()) {
    int index = it - vec->begin();
    vec->erase(vec->begin() + index);

    if (t_ptr == this->selected_task) {
      this->selected_task = nullptr;
    }
  }
}

void Planner::translate_days(int n) {
  Date sel = this->selected_date;
  sel.change_by_days(n);
  this->set_selected_date(sel);
  this->set_selected_task(nullptr);
}

void Planner::translate_months(int n) {
  Date sel = this->selected_date;
  sel.set_day(1);
  sel.change_by_months(n);
  this->set_selected_date(sel);
  this->set_selected_task(nullptr);
}

std::map<Date, std::shared_ptr<std::vector<std::shared_ptr<Task>>>>
Planner::get_monthly_tasks() {
  std::map<Date, std::shared_ptr<std::vector<std::shared_ptr<Task>>>>
      monthly_tasks;
  // Calculate number of days in month
  Date month_day_counter = this->selected_date;
  month_day_counter.set_day(1);

  int days_in_month = 0;
  do {
    days_in_month++;
    month_day_counter.change_by_days(1);
  } while (month_day_counter.get_day() != 1);

  int end_pad = 7 - static_cast<int>(month_day_counter.week_day_enum());

  // This date incrementer is used to get all the dates needed to show
  Date incrementer = this->selected_date;
  incrementer.set_day(1);

  int begin_pad = static_cast<int>(incrementer.week_day_enum());
  incrementer.change_by_days(-begin_pad);

  int days_to_show = begin_pad + days_in_month + end_pad;
  for (int i = 0; i < days_to_show; i++) {
    monthly_tasks.insert({incrementer, this->tasks[incrementer]});
    incrementer.change_by_days(1);
  }

  return monthly_tasks;
}

std::shared_ptr<std::vector<std::shared_ptr<Task>>>
Planner::get_date_tasks(Date d) {
  return this->tasks[d];
}

#define PRINT_WEEK_DAY(day)                                                    \
  os << std::setw(term_w / 7) << std::left << Date::week_day_to_string(day)

void Planner::render(std::ostream &os, int term_w, int term_h) {
  auto monthly_tasks = this->get_monthly_tasks();
  int box_w = term_w / 7;
  int box_h = (term_h - 3) / (monthly_tasks.size() / 7);

  // Month/year header
  Date selected = this->selected_date;
  os << SET_BOLD;
  os << SET_ITALIC;
  os << SET_STYLE(34);
  os << Date::month_to_string(selected.month_enum()) << ' '
     << selected.get_year();
  os << RESET;

  // Week days header
  os << SET_CURSOR(1, 0);
  PRINT_WEEK_DAY(Date::WeekDay::SUNDAY);
  PRINT_WEEK_DAY(Date::WeekDay::MONDAY);
  PRINT_WEEK_DAY(Date::WeekDay::TUESDAY);
  PRINT_WEEK_DAY(Date::WeekDay::WEDNESDAY);
  PRINT_WEEK_DAY(Date::WeekDay::THURSDAY);
  PRINT_WEEK_DAY(Date::WeekDay::FRIDAY);
  PRINT_WEEK_DAY(Date::WeekDay::SATURDAY);

  int selected_pos_row = 0;
  int selected_pos_col = 0;

  // Loop through the provided 35 given dates
  int day_count = 0;
  for (auto v : monthly_tasks) {
    os << SET_CURSOR(2 + box_h * (day_count / 7), box_w * (day_count % 7));

    // Highlight current day
    if (v.first == Date()) {
      os << SET_BOLD;
      os << SET_STYLE(34);
    }

    // Dim the padding days that are not in the selected month
    if (v.first.get_month() != this->selected_date.get_month()) {
      os << SET_DIM;
    }

    // Highlight selected day
    if (v.first == this->selected_date && !this->selected_task) {
      os << SET_STYLE(7);
    }

    os << std::setw(term_w / 7) << v.first.get_day();
    os << RESET;

    // Ensure there is a vector
    if (v.second != nullptr) {
      // Loop through each event
      int event_count = 0;
      for (auto t_ptr : *v.second) {
        os << SET_CURSOR(event_count + 3 + box_h * (day_count / 7),
                         box_w * (day_count % 7));
        if (t_ptr == this->selected_task) {
          selected_pos_row = event_count + 3 + box_h * (day_count / 7);

          selected_pos_col = box_w * (day_count % 7);
        } else {
          if (t_ptr->get_completed()) { // Completed tasks
            os << SET_STRIKE << SET_DIM;
          } else if (t_ptr->get_date() < Date()) { // Late tasks
            os << SET_STYLE(31);
          }

          // Add ellipses if the task name is too long
          if (t_ptr->get_name().size() > box_w) {
            os << t_ptr->get_name().substr(0, box_w - 3);
            os << "...";
          } else {
            os << t_ptr->get_name();
          }

          os << RESET;
        }

        event_count++;
      }
    }
    day_count++;
  }
  if (this->selected_task) {
    // Draw the selected task last to prevent occlusion conflicts
    os << SET_CURSOR(selected_pos_row, selected_pos_col);

    if (this->selected_task->get_completed()) {
      os << SET_STRIKE << SET_DIM;
    }

    os << SET_INVERT;

    os << this->selected_task->get_name();

    os << RESET;
  }
}
