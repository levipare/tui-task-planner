#include "date.h"
#include "input.h"
#include "planner.h"
#include "renderable.h"
#include "renderer.h"
#include "terminal.h"

#include <iostream>
#include <memory>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int main() {
  // Instantiate the essential components
  Terminal::setup();
  std::shared_ptr<Planner> planner = std::make_shared<Planner>();
  std::shared_ptr<Input> input = std::make_shared<Input>(planner);

  std::vector<std::shared_ptr<Renderable>> render_objects = {planner, input};
  Renderer renderer(render_objects);

  // TODO: Add a csv parser and generator to load/save tasks to a file
  // Some test tasks
  // Task t1("Do HW1 helllo world another task", Date(23, 0, 2024));
  // Task t2("Do HW2", Date(23, 0, 2024));
  // Task t3("Do HW3", Date(24, 0, 2024));
  // Task t4("Do HW4", Date(1, 1, 2024));
  // planner->add_task(std::make_shared<Task>(t1));
  // planner->add_task(std::make_shared<Task>(t2));
  // planner->add_task(std::make_shared<Task>(t3));
  // planner->add_task(std::make_shared<Task>(t4));

  // Setup terminal enviroment
  Terminal::set_raw();
  bool quit = false;
  while (!quit) {
    renderer.draw();
    quit = input->handle();
  }
  Terminal::restore();
}
