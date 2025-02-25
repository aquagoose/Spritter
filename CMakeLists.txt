cmake_minimum_required(VERSION 3.20)
project(Spritter)

set(CMAKE_CXX_STANDARD 17)

add_library(Spritter STATIC
        src/Game.cpp
        include/Spritter/Game.h
        src/Window.cpp
        include/Spritter/Window.h
        include/Spritter/Math/Size.h
        include/Spritter/Graphics/GraphicsDevice.h
        src/Graphics/GL/GLGraphicsDevice.cpp
        src/Graphics/GL/GLGraphicsDevice.h
        include/Spritter/Math/Color.h
        include/Spritter/Graphics/TextureBatcher.h
        include/Spritter/Graphics/Renderable.h
        src/Graphics/GL/GLRenderable.cpp
        src/Graphics/GL/GLRenderable.h
        src/Graphics/GL/GLShader.cpp
        src/Graphics/GL/GLShader.h
        include/Spritter/Graphics/Shader.h
        include/Spritter/Math/Vector2.h
        include/Spritter/Math/Math.h
        src/Graphics/TextureBatcher.cpp
        include/Spritter/Math/Vector4.h
        include/Spritter/Math/Matrix.h
        include/Spritter/Graphics/Texture.h
        src/Graphics/GraphicsDevice.cpp
        src/Graphics/GL/GLTexture.cpp
        src/Graphics/GL/GLTexture.h
        include/Spritter/Math/Rectangle.h
        include/Spritter/Input.h
        src/SDLUtils.cpp
        src/SDLUtils.h
        include/Spritter/Event.h
)

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

# ---------- STB ----------

add_subdirectory(lib/stb)
target_link_libraries(Spritter PUBLIC stb)

# ----- TEST -----

add_executable(SpTest tests/main.cpp)
target_link_libraries(SpTest PRIVATE Spritter)
target_link_libraries(SpTest PRIVATE stdc++)