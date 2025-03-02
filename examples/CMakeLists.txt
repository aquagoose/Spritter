cmake_minimum_required(VERSION 3.20)
project(SpritterExamples)

add_custom_target(SpritterExamples ALL)
spritter_set_content(SpritterExamples ${CMAKE_CURRENT_SOURCE_DIR}/Content ${CMAKE_BINARY_DIR}/examples/Content)

function(add_example name)
    file(GLOB_RECURSE sources ${name}/*.h ${name}/*.cpp)
    add_executable(${name} ${sources})
    target_link_libraries(${name} Spritter)
    add_dependencies(${name} SpritterExamples)
endfunction()

add_example(01-ClearScreen)
add_example(02-Sprite)