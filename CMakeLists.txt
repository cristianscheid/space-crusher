cmake_minimum_required(VERSION 3.27)

project(space_crusher C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED COMPONENTS SDL2::SDL2)

add_executable(space_crusher main.c)

target_link_libraries(space_crusher SDL2::SDL2)