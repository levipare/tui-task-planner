#ifndef PLANNER_H
#define PLANNER_H

#include "date.h"
#include "renderer.h"
#include "task.h"
#include <map>
#include <memory>
#include <optional>
#include <vector>

class Planner : public Renderable {
private:
  std::map<Date, std::shared_ptr<std::vector<std::shared_ptr<Task>>>> tasks;

  Date selected_date;
  Date current_date;
  std::shared_ptr<Task> selected_task;

public:
  Planner();

  // Getters
  Date get_selected_date() const;

  Date get_current_date() const;

  std::shared_ptr<Task> get_selected_task() const;

  // Setters
  void set_selected_date(Date date);

  void set_current_date(Date date);

  void set_selected_task(std::shared_ptr<Task> t_ptr);

  // Utils
  void add_task(std::shared_ptr<Task> t_ptr);

  void remove_task(std::shared_ptr<Task> t_ptr);

  void translate_days(int n);

  void translate_months(int n);

  std::map<Date, std::shared_ptr<std::vector<std::shared_ptr<Task>>>>
  get_monthly_tasks();

  std::shared_ptr<std::vector<std::shared_ptr<Task>>> get_date_tasks(Date d);

  // Renderable impl
  void render(std::ostream &os, int term_w, int term_h);
};

#endif
