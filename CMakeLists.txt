cmake_minimum_required(VERSION 3.30)
project(Spritter)

set(CMAKE_CXX_STANDARD 17)

add_library(Spritter STATIC library.cpp)

option(SDL_VENDORED "Use vendored SDL" OFF)

if (SDL_VENDORED)
    add_subdirectory(lib/SDL)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()


target_link_libraries(Spritter PUBLIC SDL3::SDL3)