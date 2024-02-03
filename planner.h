#ifndef PLANNER_H
#define PLANNER_H

#include "csv.h"
#include "date.h"
#include "renderer.h"
#include "task.h"

#include <map>
#include <memory>
#include <optional>
#include <vector>

class Planner : public Renderable {
private:
  Csv csv;
  std::map<Date, std::shared_ptr<std::vector<std::shared_ptr<Task>>>> tasks;

  Date selected_date;
  std::shared_ptr<Task> selected_task;

public:
  /**
   * Default Constructor.
   */
  Planner();

  // Getters
  /**
   * @return the selected_date
   */
  Date get_selected_date() const;

  /**
   * @return shared pointer to the selected task
   */
  std::shared_ptr<Task> get_selected_task() const;

  // Setters
  /**
   * @param date a new selected date
   */
  void set_selected_date(Date date);

  /**
   * @param t_ptr a shared pointer to a task
   */
  void set_selected_task(std::shared_ptr<Task> t_ptr);

  // Utils
  /**
   * Add a task to the planner
   * @param t_ptr a shared pointer to a task
   */
  void add_task(std::shared_ptr<Task> t_ptr);

  /**
   * Remove a task from the planner.
   * @param t_ptr a shared pointer to a task
   */
  void remove_task(std::shared_ptr<Task> t_ptr);

  /**
   * Translate the planner selected_date by n amount of days.
   * @param n the number of days to translate by
   */
  void translate_days(int n);

  /**
   * Translate the planner selected_date by n amount of months.
   * @param n the number of months to translate by
   */
  void translate_months(int n);

  /**
   * Gets a map of all the dates to be displayed for a given calendar month.
   * This includes padding days.
   * @return a map keyed by a Date obj that contains vectors of tasks for each
   * Date
   */
  std::map<Date, std::shared_ptr<std::vector<std::shared_ptr<Task>>>>
  get_monthly_tasks();

  /**
   * Get the tasks for a given Date
   * @return a shared pointer to a vector of tasks
   */
  std::shared_ptr<std::vector<std::shared_ptr<Task>>> get_date_tasks(Date d);

  /**
   * Saves the current tasks to csv.
   */
  void save_to_csv();

  /**
   * Load the tasks from a csv file.
   */
  void load_from_csv();

  // Renderable impl
  void render(std::ostream &os, int term_w, int term_h);
};

#endif
