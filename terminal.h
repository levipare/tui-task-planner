#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

namespace Terminal {

/**
 * @brief Setups signal handling.
 */
void setup();

/**
 * @brief Disables canonical mode.
 */
void set_raw();

/**
 * @brief Restores the terminal to canonical mode.
 */
void restore();

/**
 * @brief Get the height (# of cols) of the current terminal
 * @return the width of the terminal
 */
int get_width();

/**
 * @brief Get the height (# of rows) of the current terminal
 * @return the height of the terminal
 */
int get_height();
}; // namespace Terminal

#endif
