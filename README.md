# M1OEP - Task Planner

## Levi Pare

## Project Summary

This is a terminal based UI task planner app. It allows tasks to be created and assigned to certain days.
Tasks can be checked off or fully deleted. The UI is based around a full calendar view of the month and a user an navigate months.
Tasks are saved to a csv file so that they persist among sessions.

### How to Build and Run

Navigate to the project directory run the commands:

```
mkdir cmake-build-debug
cmake -S. -Bcmake-build-debug
cmake --build cmake-build-debug
```

Run the program using by running the following command:

```
./cmake-build-debug/M1OEP
```

### Note: This project depends on POSIX specific apis therefore it is only able to compile on POSIX systems i.e. MacOS or Linux

### Note: Do not run in the integrated CLion terminal -- it is feature incomplete. Run in a proper terminal emulator such as ITerm2.

### Module 1 Concepts Used

- Classes seperated into header and .cpp files
  - Task, Planner, Renderer, Input, Date, Csv
- Enums
  - Two enums in Date class
  - One enum in Input class
- Overloaded operators
  - Overloaded < operator for custom map key in Date class
  - Overloaded == operator for Date comparison
  - Overloaded << operator for custom printing of Date object

## Known Bugs

No known bugs at this time.

## Future Work

- Add a feature to customize the color of a task.
- The ability to edit a task.
- Create a task with a date other than what day is currently selected.

## Citations

Abstract class. cppreference.com. (n.d.). https://en.cppreference.com/w/cpp/language/abstract_class

C Time Library ctime. cplusplus.com. (n.d.). https://cplusplus.com/reference/ctime/

How to catch CTRL+C?. cplusplus.com. (2008) https://cplusplus.com/forum/beginner/1501/

termios. man7.org (n.d.) https://man7.org/linux/man-pages/man3/termios.3.html

ioctl. man7.org. (n.d.) https://man7.org/linux/man-pages/man2/ioctl_tty.2.html

## Grade
