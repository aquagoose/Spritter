cmake_minimum_required(VERSION 3.20)
project(Spritter)

set(CMAKE_CXX_STANDARD 17)

add_library(Spritter STATIC library.cpp
        src/Game.cpp
        include/Spritter/Game.h
        src/Window.cpp
        include/Spritter/Window.h)

target_include_directories(Spritter PUBLIC include)

# ---------- SDL ----------

option(SDL_VENDORED "Use vendored SDL" OFF)

if (SDL_VENDORED)
    add_subdirectory(lib/SDL)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

target_link_libraries(Spritter PUBLIC SDL3::SDL3)

# ---------- GLAD ----------

add_subdirectory(lib/glad)
target_link_libraries(Spritter PUBLIC glad)