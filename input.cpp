#include "input.h"
#include "planner.h"
#include "renderer.h"
#include "task.h"

#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

Input::Input(std::shared_ptr<Planner> plnr) {
  this->input_string = "";
  this->planner = plnr;
  this->state = Mode::NAVIGATE;
}

bool Input::handle() {
  char c = std::cin.get();
  switch (this->state) {
  case Mode::NAVIGATE: {
    switch (c) {
    case '>': {
      this->planner->translate_months(1);
      break;
    }
    case '<': {
      this->planner->translate_months(-1);
      break;
    }
    case 'q': {
      return true;
    }
    case 'h': {
      this->planner->translate_days(-1);
      break;
    }
    case 'j': {
      this->planner->translate_days(7);
      break;
    }
    case 'k': {
      this->planner->translate_days(-7);
      break;
    }
    case 'l': {
      this->planner->translate_days(1);
      break;
    }
    case 'x': {
      if (this->planner->get_selected_task()) {
        this->planner->remove_task(this->planner->get_selected_task());
      }
      break;
    }
    case ' ': {
      this->state = Mode::CREATE;
      break;
    }
    case '\n': {
      auto t_ptr = this->planner->get_selected_task();
      if (!t_ptr)
        break;

      t_ptr->set_completed(!t_ptr->get_completed());
      break;
    }
    case '\t': {
      auto vec =
          this->planner->get_date_tasks(this->planner->get_selected_date());
      if (!vec)
        break;

      auto it = std::find(vec->begin(), vec->end(),
                          this->planner->get_selected_task());
      if (it != vec->end()) {
        int index = it - vec->begin();
        if (index + 1 < vec->size()) {
          this->planner->set_selected_task(vec->at(index + 1));
        } else {
          this->planner->set_selected_task(nullptr);
        }
      } else if (vec->size() > 0) {
        this->planner->set_selected_task(vec->at(0));
      } else {
        this->planner->set_selected_task(nullptr);
      }
      break;
    }

    case '\033': { // Handle escape sequences
      char c2 = std::cin.peek();
      if (c2 != '[') {
        break;
      }

      std::cin.get();
      c2 = std::cin.get();
      switch (c2) {
      case 'D': { // Left arrow
        this->planner->translate_days(-1);
        break;
      }
      case 'B': { // Down arrow
        this->planner->translate_days(7);
        break;
      }
      case 'A': { // Up arrow
        this->planner->translate_days(-7);
        break;
      }
      case 'C': { // Right arrow
        this->planner->translate_days(1);
        break;
      }
      case 'Z': { // Shift + tab
        auto vec =
            this->planner->get_date_tasks(this->planner->get_selected_date());
        if (!vec)
          break;

        auto it = std::find(vec->begin(), vec->end(),
                            this->planner->get_selected_task());
        if (it != vec->end()) {
          int index = it - vec->begin();
          if (index - 1 >= 0) {
            this->planner->set_selected_task(vec->at(index - 1));
          } else {
            this->planner->set_selected_task(nullptr);
          }
        } else if (vec->size() > 0) {
          this->planner->set_selected_task(vec->at(vec->size() - 1));
        } else {
          this->planner->set_selected_task(nullptr);
        }
        break;
      }
      }
    }
    }
    break;
  }
  case Mode::CREATE: {
    switch (c) {
    case 127: {
      if (!this->input_string.empty()) {
        this->input_string.pop_back();
      }
      break;
    }
    case '\n': {
      this->planner->add_task(std::make_shared<Task>(
          Task(this->input_string.size() ? this->input_string : "Unnamed Event",
               this->planner->get_selected_date())));
      this->state = Mode::NAVIGATE;
      this->input_string = "";
      break;
    }
    case '\033': { // Handle escape sequences
      char c2 = std::cin.peek();
      if (c2 != '[') {
        this->state = Mode::NAVIGATE;
        this->input_string = "";
        break;
      }
      break;
    }
    default: {
      std::cout << (int)c << std::endl;
      this->input_string += c;
      break;
    }
    }
  }
  }
  return false;
}

void Input::render(std::ostream &os, int term_w, int term_h) {
  switch (this->state) {
  case Mode::NAVIGATE: {
    os << SET_CURSOR(term_h, 0);
    os << SET_DIM;
    os << "q Quit | ";
    os << "hjkl/Arrows Navigate | ";
    os << "</> Change Month | ";
    os << "Tab/Shift+Tab Cycle Tasks | ";
    os << "Space Create Task | ";
    os << "Enter Check Off | ";
    os << "x Delete Task";
    os << RESET;
    break;
  }
  case Mode::CREATE: {
    os << SET_CURSOR(term_h, 0);
    os << SET_DIM;
    os << "Enter Create Task | ";
    os << "Esc Cancel";
    os << RESET;

    // This is a bunch of nonsense to make the text input box
    os << SET_CURSOR((term_h - 4) / 2, (term_w - 30) / 2);
    os << SET_STYLE(40);
    os << std::setw(30) << "";

    os << SET_CURSOR((term_h - 4) / 2 + 1, (term_w - 30) / 2);
    os << std::setw(30) << " Enter task name:";
    os << SET_CURSOR((term_h - 4) / 2 + 2, (term_w - 30) / 2);
    os << std::setw(30) << "";
    os << SET_CURSOR((term_h - 4) / 2 + 2, (term_w - 30) / 2);
    os << " " << this->input_string;
    os << SET_CURSOR((term_h - 4) / 2 + 3, (term_w - 30) / 2);
    os << std::setw(30) << "";
    os << SET_CURSOR((term_h - 4) / 2 + 2,
                     (term_w - 30) / 2 + 1 + this->input_string.size());
    os << "\033[?25h";
    os << RESET;
    break;
  }
  }
}
