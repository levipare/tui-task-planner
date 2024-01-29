#include "terminal.h"
#include "renderer.h"
#include <csignal>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace Terminal {
static struct termios original_state;

static void handle_sigint(int n) {
  restore();
  exit(0);
}

void setup() { std::signal(SIGINT, handle_sigint); }

void set_raw() {

  tcgetattr(STDIN_FILENO, &original_state); // Get current tty attributes

  // Modifying tty attributes
  original_state.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO, TCSAFLUSH,
            &original_state); // Set tty attributes
}

void restore() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_state);
  std::cout << "\033[2J"; // Clear screen
  std::cout << SET_CURSOR(0, 0);
  std::cout << "\033[?25h"; // Show cursor
}

int get_width() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int get_height() {

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_row;
}
}; // namespace Terminal
