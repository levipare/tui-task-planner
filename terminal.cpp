#include "terminal.h"
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

// Public
Terminal::Terminal() {}

void Terminal::set_raw() {
  tcgetattr(STDIN_FILENO, &this->original_state); // Get current tty attributes

  // Modifying tty attributes
  this->original_state.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO, TCSAFLUSH,
            &this->original_state); // Set tty attributes
}

void Terminal::restore() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &this->original_state);
}

int Terminal::get_width() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int Terminal::get_height() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_row;
}
