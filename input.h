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
  Input(std::shared_ptr<Planner> plnr);

  void handle();

  void render(std::ostream &os, int term_w, int term_h);
};

#endif
