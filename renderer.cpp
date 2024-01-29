#include "renderer.h"
#include "date.h"
#include "renderable.h"
#include "terminal.h"
#include <iostream>

Renderer::Renderer(std::shared_ptr<Terminal> term,
                   std::vector<std::shared_ptr<Renderable>> render_objs) {
  this->term = term;
  this->render_objects = render_objs;
}

void Renderer::draw() {
  std::cout << "\033[?25l"; // Hide cursor
  std::cout << "\033[2J";   // Clear screen
  std::cout << SET_CURSOR(0, 0);

  for (std::shared_ptr<Renderable> r : this->render_objects) {
    r->render(std::cout, this->term->get_width(), this->term->get_height());
  }

  std::cout << std::flush; // Flush changes to STDOUT
}
