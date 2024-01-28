#include "input.h"
#include "planner.h"
#include "renderer.h"
#include "task.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

Input::Input(std::shared_ptr<Planner> plnr) {
  this->input_string = "";
  this->planner = plnr;
  this->state = State::NAVIGATE;
}

void Input::handle() {
  char c = std::cin.get();
  switch (this->state) {
  case State::NAVIGATE: {
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
      exit(0);
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
    case ' ': {
      this->state = State::CREATE;
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
      case 'D': {
        this->planner->translate_days(-1);
        break;
      }
      case 'B': {
        this->planner->translate_days(7);
        break;
      }
      case 'A': {
        this->planner->translate_days(-7);
        break;
      }
      case 'C': {
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
  case State::CREATE: {
    switch (c) {
    case '\n': {
      Task t("hello", Date(28, 0, 2024));
      this->planner->add_task(std::make_shared<Task>(t));
      break;
    }
    }
    break;
  }
  }
}

void Input::render(std::ostream &os, int term_w, int term_h) {
  switch (this->state) {
  case State::NAVIGATE: {
    os << SET_CURSOR(term_h, 0);
    os << SET_DIM;
    os << "hjkl/Arrows Navigate | ";
    os << "< Prev Month | ";
    os << "> Next Month | ";
    os << "Tab Next Task | ";
    os << "Shift + Tab Prev Task | ";
    os << "Space Create event | ";
    os << "Enter Check off | ";
    os << RESET;
    break;
  }
  }
}
