#include "date.h"
#include "planner.h"
#include "renderable.h"
#include "renderer.h"
#include "terminal.h"

#include <bits/stdc++.h>
#include <iostream>
#include <memory>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

#define CHANGE_DATE(n)                                                         \
  Date sel = planner->get_selected_date();                                     \
  sel.change_by_days(n);                                                       \
  planner->set_selected_date(sel);

void handle_input(std::shared_ptr<Planner> planner) {
  char c = cin.get();
  switch (c) {
  case '>': {
    Date sel = planner->get_selected_date();
    sel.change_by_months(1);
    planner->set_selected_date(sel);
    break;
  }
  case '<': {
    Date sel = planner->get_selected_date();
    sel.change_by_months(-1);
    planner->set_selected_date(sel);
    break;
  }
  case 'q': {
    exit(0);
  }
  case 'h': {
    CHANGE_DATE(-1);
    break;
  }
  case 'j': {
    CHANGE_DATE(7);
    break;
  }
  case 'k': {
    CHANGE_DATE(-7);
    break;
  }
  case 'l': {
    CHANGE_DATE(1);
    break;
  }
  case '\t': {
    auto vec = planner->get_date_tasks(planner->get_selected_date());
    if (!vec)
      break;

    auto it = std::find(vec->begin(), vec->end(), planner->get_selected_task());
    if (it != vec->end()) {
      int index = it - vec->begin();
      if (index + 1 < vec->size()) {
        planner->set_selected_task(vec->at(index + 1));
      } else {
        planner->set_selected_task(nullptr);
      }
    } else if (vec->size() > 0) {
      planner->set_selected_task(vec->at(0));
    } else {
      planner->set_selected_task(nullptr);
    }
    break;
  }

  case '\n': {
    auto t_ptr = planner->get_selected_task();
    if (!t_ptr)
      break;

    t_ptr->set_completed(!t_ptr->get_completed());
    break;
  }
  case '\033': { // Handle escape sequences
    char c2 = cin.peek();
    if (c2 != '[')
      break;
    c2 = cin.get();
    c2 = cin.get();
    switch (c2) {
    case 'D': {
      CHANGE_DATE(-1);
      break;
    }
    case 'B': {
      CHANGE_DATE(7);
      break;
    }
    case 'A': {
      CHANGE_DATE(-7);
      break;
    }
    case 'C': {
      CHANGE_DATE(1);
      break;
    }
    case 'Z': { // Shift + tab
      auto vec = planner->get_date_tasks(planner->get_selected_date());
      if (!vec)
        break;

      auto it =
          std::find(vec->begin(), vec->end(), planner->get_selected_task());
      if (it != vec->end()) {
        int index = it - vec->begin();
        if (index - 1 >= 0) {
          planner->set_selected_task(vec->at(index - 1));
        } else {
          planner->set_selected_task(nullptr);
        }
      } else if (vec->size() > 0) {
        planner->set_selected_task(vec->at(vec->size() - 1));
      } else {
        planner->set_selected_task(nullptr);
      }
      break;
    }
    }
  }
  }
}

int main() {
  // Instantiate the essential components
  std::shared_ptr<Terminal> term = make_shared<Terminal>();
  std::shared_ptr<Planner> planner = make_shared<Planner>();

  std::vector<std::shared_ptr<Renderable>> render_objects;
  render_objects.push_back(planner);

  Renderer renderer(term, render_objects);

  Task t1("Do HW1 helllo world another task", Date(23, 0, 2024));
  Task t2("Do HW2", Date(23, 0, 2024));
  Task t3("Do HW3", Date(24, 0, 2024));
  Task t4("Do HW4", Date(1, 1, 2024));
  planner->add_task(make_shared<Task>(t1));
  planner->add_task(make_shared<Task>(t2));
  planner->add_task(make_shared<Task>(t3));
  planner->add_task(make_shared<Task>(t4));

  // Setup terminal enviroment
  term->set_raw();

  while (true) {
    renderer.draw();
    handle_input(planner);
  }
}
