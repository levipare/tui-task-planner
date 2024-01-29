#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

namespace Terminal {

void setup();

void set_raw();

void restore();

int get_width();

int get_height();
}; // namespace Terminal

#endif
