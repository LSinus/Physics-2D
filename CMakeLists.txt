cmake_minimum_required(VERSION 3.10)

project(Physics-2D)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Physics-2D main.cpp)
target_link_libraries(Physics-2D sfml-graphics sfml-window sfml-system)

