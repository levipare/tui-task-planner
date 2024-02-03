# M1OEP - Task Planner

## Levi Pare

## Project Summary

This is a terminal based UI task planner app. It allows tasks to be created and assigned to certain days.
Tasks can be checked off or fully deleted. The UI is based around a full calendar view of the month and the user can navigate across days/months.
Tasks are saved to a csv file so that they persist among sessions.

### How to Build and Run

Navigate to the project directory and run the commands:

```
mkdir cmake-build-debug
cmake -S. -Bcmake-build-debug
cmake --build cmake-build-debug
```

Run the program by running the following command:

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
  - Overloaded < operator for custom std::map key in Date class
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

| Rubric category                                                                         | Points  | Justification                                                                                                                                                                                                                                                                                                |
| --------------------------------------------------------------------------------------- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Main program complexity and usability                                                   | 40 pts  | My program uses complex terminal IO and in return the user gets an easy to use interface. Because of the complexity main.cpp contains just the necessary instantiates and delegates the complexity out to each respective component.                                                                         |
| Concept: class Planner                                                                  | 20 pts  | This is a large class with complex functionality and is the heart of the program.                                                                                                                                                                                                                            |
| Concept: class Date                                                                     | 20 pts  | This class puts the ctime library to good use and provides a nice abstraction over date handling.                                                                                                                                                                                                            |
| Concept: class Input                                                                    | 20 pts  | This class handles and validates all input and is what makes the program enjoyable to use. Having input handling seperated from the main loop contributed to cleaner result.                                                                                                                                 |
| Concept: classes Task, Csv, Renderer, abstract class Renderable, and namespace Terminal | 20 pts  | I think the combination of these classes, while not implementing the required spec of 2 fields and 1 non trival method, are seperated into header and cpp files and should be considered for a total of 20 points as they provide functionality that needed to be abstracted away from individual functions. |
| Concept: enum WeekDay in class Date                                                     | 5 pts   | Week days are essential to a calendar and enum provides a safe way to reference the idea of them.                                                                                                                                                                                                            |
| Concept: enum Month in class Date                                                       | 5 pts   | Similarly to the WeekDay enum, having a month enum made the source code more readable semantically sound. Both the date enums had methods that would convert them to a string for easy printing purposes.                                                                                                    |
| Concept: overloaded operator < in Date class                                            | 5 pts   | Overloading this operator is required to use the class as a key to a map. Having a map that is keyed by a date made perfect sense for my program.                                                                                                                                                            |
| Concept: overloaded operator == in Date class                                           | 5 pts   | Overloading this operator proved very useful as there are significant instances in which dates are compared for equality.                                                                                                                                                                                    |
| Style and documention                                                                   | 0 pts   | All classes have robust documentation and inline comments are present when necessary.                                                                                                                                                                                                                        |
| Video                                                                                   | 0 pts   | My video shows all the functionality of my program and demonstrates its unique input.                                                                                                                                                                                                                        |
| Lifespan of project                                                                     | 0 pts   | Commits span more than 7 days and significant constributions were made on more than 3 days.                                                                                                                                                                                                                  |
| Total points                                                                            | 140 pts |                                                                                                                                                                                                                                                                                                              |
