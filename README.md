# TUI Task Planner

## Project Summary

This is a terminal based UI task planner app written in C++. It allows tasks to be created and assigned to certain days.
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
./cmake-build-debug/tui-task-planner
```

### Note: This project depends on POSIX specific apis therefore it is only able to compile on POSIX systems i.e. MacOS or Linux
