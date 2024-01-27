#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

class Terminal {
private:
  struct termios original_state;

public:
  Terminal();

  void set_raw();

  void restore();

  int get_width();

  int get_height();
};

#endif
