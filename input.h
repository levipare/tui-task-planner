#ifndef INPUT_H
#define INPUT_H

#include "planner.h"
#include "renderable.h"
#include <iostream>
#include <memory>
#include <string>

class Input : public Renderable {
public:
  enum class Mode { NAVIGATE, CREATE };

private:
  Mode state;
  std::string input_string;
  std::shared_ptr<Planner> planner;

public:
  /**
   * @brief Constructor
   */
  Input(std::shared_ptr<Planner> plnr);

  /**
   * @brief Handle inputs
   * @return true if the handling indicates to quit
   */
  bool handle();

  // Interface impl
  void render(std::ostream &os, int term_w, int term_h);
};

#endif
