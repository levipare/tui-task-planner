cmake_minimum_required(VERSION 3.8)
project(tui-task-planner)

set(CMAKE_CXX_STANDARD 17)

add_executable(M1OEP main.cpp csv.cpp task.cpp date.cpp planner.cpp renderer.cpp terminal.cpp input.cpp)
