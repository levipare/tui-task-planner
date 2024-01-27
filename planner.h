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
  std::map<Date, std::shared_ptr<std::vector<Task>>> tasks;

  Date selected;
  Date current;

public:
  Planner();

  // Getters
  Date get_selected_date() const;

  Date get_current_date() const;

  std::map<Date, std::shared_ptr<std::vector<Task>>> get_tasks();

  // Setters
  void set_selected_date(Date date);

  void set_current_date(Date date);

  // Utils
  void add_task(Task t);

  void remove_task(Task t);

  std::map<Date, std::shared_ptr<std::vector<Task>>> get_monthly_tasks();

  // Renderable impl
  void render(std::ostream &os, int term_w, int term_h);
};

#endif
