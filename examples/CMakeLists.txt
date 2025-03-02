cmake_minimum_required(VERSION 3.20)
project(SpritterExamples)

function(add_example name)
    file(GLOB_RECURSE sources ${name}/*.h ${name}/*.cpp)
    add_executable(${name} ${sources})
    target_link_libraries(${name} Spritter)
endfunction()

add_example(01-ClearScreen)
add_example(02-Sprite)