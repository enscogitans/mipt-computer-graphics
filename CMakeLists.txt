cmake_minimum_required(VERSION 3.14)
project(computer_graphics)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)
include_directories(${EXTERNAL_INCLUDES})
link_directories(${EXTERNAL_LINKS})

add_subdirectory(task1)
add_subdirectory(task2)
add_subdirectory(task3)
add_subdirectory(task4)
add_subdirectory(task5)
