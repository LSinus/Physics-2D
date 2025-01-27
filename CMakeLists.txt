cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(Physics-2D)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Physics-2D main.cpp vec2.h
        physicsObject.h
        physicsWorld.h
        physicsWorld.cpp)
target_link_libraries(Physics-2D sfml-graphics sfml-window sfml-system)

