#ifndef RENDERER_H
#define RENDERER_H

#include "renderable.h"
#include "terminal.h"
#include <memory>
#include <vector>

#define SET_CURSOR(row, col) "\033[" << row + 1 << ";" << col + 1 << "H"
#define CURSOR_UP(n) "\033[" << n << "A"
#define CURSOR_DOWN(n) "\033[" << n << "B"
#define CURSOR_RIGHT(n) "\033[" << n << "C"
#define CURSOR_LEFT(n) "\033[" << n << "D"
#define SET_STYLE(c) "\033[" << c << "m"
#define SET_BOLD SET_STYLE(1)
#define SET_ITALIC SET_STYLE(3)
#define SET_STRIKE SET_STYLE(9)
#define SET_DIM SET_STYLE(2)
#define SET_INVERT SET_STYLE(7)
#define RESET "\033[0m"

class Renderer {
private:
  std::shared_ptr<Terminal> term;
  std::vector<std::shared_ptr<Renderable>> render_objects;

public:
  Renderer(std::shared_ptr<Terminal> term,
           std::vector<std::shared_ptr<Renderable>> render_objs);

  void draw();
};

#endif
