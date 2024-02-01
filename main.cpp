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

  // Setup terminal enviroment
  Terminal::set_raw();
  bool quit = false;
  while (!quit) {
    renderer.draw();
    quit = input->handle();
  }
  Terminal::restore();
}
