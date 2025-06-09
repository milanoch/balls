cmake_minimum_required(VERSION 3.5)
project(milan_pororo)

set(CMAKE_CXX_STANDARD 17)

add_executable(SPG main.cpp)

add_subdirectory(raylib)

target_link_libraries(SPG raylib)