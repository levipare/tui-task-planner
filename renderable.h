#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <iostream>

/*
 * This simple interface requires objects to implement a render method.
 */
class Renderable {
public:
  Renderable() = default;
  /**
   * @param outstream for drawing to
   * @param terminal width
   * @param terminal height
   */
  virtual void render(std::ostream &, int, int){};
};

#endif
