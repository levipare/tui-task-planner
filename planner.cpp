#include "planner.h"
#include "date.h"
#include "renderer.h"

#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

Planner::Planner() {}

// Getters
Date Planner::get_selected_date() const { return this->selected; }

Date Planner::get_current_date() const { return this->current; }

std::map<Date, std::shared_ptr<std::vector<Task>>> Planner::get_tasks() {
  return this->tasks;
}

// Setters
void Planner::set_selected_date(Date date) { this->selected = date; }

void Planner::set_current_date(Date date) { this->current = date; }

void Planner::add_task(Task t) {
  this->tasks.insert({t.get_date(), std::make_shared<std::vector<Task>>()});
  this->tasks[t.get_date()]->push_back(t);
}

void Planner::remove_task(Task t) {}

std::map<Date, std::shared_ptr<std::vector<Task>>>
Planner::get_monthly_tasks() {
  std::map<Date, std::shared_ptr<std::vector<Task>>> monthly_tasks;

  Date incrementer = this->selected;
  // Calculate dates to show
  incrementer.set_day(1);

  // Calc the padding at the beginning of the calendar
  incrementer.change_by_days(-static_cast<int>(incrementer.week_day_enum()));

  // Calc 35 total dates (5 rows of 7 days)
  for (int i = 0; i < 35; i++) {
    monthly_tasks.insert({incrementer, this->tasks[incrementer]});
    incrementer.change_by_days(1);
  }

  return monthly_tasks;
}

#define PRINT_WEEK_DAY(day)                                                    \
  os << std::setw(term_w / 7) << std::left << Date::week_day_to_string(day)

void Planner::render(std::ostream &os, int term_w, int term_h) {
  int box_w = term_w / 7;
  int box_h = (term_h - 3) / 5; // Subtract 3 to account for the month/year,
                                // week day and bindings lines

  // Month/year header
  Date selected = this->selected;
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

  // Loop through the provided 35 given dates
  int day_count = 0;
  for (auto v : this->get_monthly_tasks()) {
    os << SET_CURSOR(2 + box_h * (day_count / 7), box_w * (day_count % 7));

    // Highlight current day
    if (v.first == this->get_current_date()) {
      os << SET_BOLD;
      os << SET_STYLE(34);
    }

    // Dim the padding days that are not in the selected month
    if (v.first.get_month() != this->get_selected_date().get_month()) {
      os << SET_STYLE(90);
    }

    if (v.first == this->selected) {
      os << SET_STYLE(100);
    }

    os << std::setw(term_w / 7) << v.first.get_day();
    os << RESET;

    // Ensure there is a vector
    if (v.second != nullptr) {
      // Loop through each event
      int event_count = 0;
      for (Task &t : *v.second) {
        os << SET_CURSOR(event_count + 3 + box_h * (day_count / 7),
                         box_w * (day_count % 7));
        os << t.get_name();
        event_count++;
      }
    }
    day_count++;
  }
}
