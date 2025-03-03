cmake_minimum_required(VERSION 3.20)
project(Spritter)

set(CMAKE_CXX_STANDARD 17)

option(SP_ENABLE_D3D11 "Enable DirectX 11 support" OFF)
option(SP_USE_GRABS "Use the experimental GRABS API" OFF)
option(SP_BUILD_TEST "Build the Spritter test project" OFF)
option(SP_BUILD_EXAMPLES "Build the Spritter examples" ON)

#if (WIN32)
#    set(SP_ENABLE_D3D11 ON)
#endif()

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
        include/Spritter/Graphics/SpriteRenderer.h
        include/Spritter/Graphics/Renderable.h
        src/Graphics/GL/GLRenderable.cpp
        src/Graphics/GL/GLRenderable.h
        src/Graphics/GL/GLShader.cpp
        src/Graphics/GL/GLShader.h
        include/Spritter/Graphics/Shader.h
        include/Spritter/Math/Vector2.h
        include/Spritter/Math/Math.h
        src/Graphics/SpriteRenderer.cpp
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
        src/Input.cpp
        include/Spritter/Spritter.h
        include/Spritter/Time.h
        src/Time.cpp
        include/Spritter/Graphics/Font.h
        src/Graphics/Font.cpp
)

target_include_directories(Spritter PUBLIC include)

# ---------- SDL ----------

#if (WIN32)
    add_subdirectory(lib/SDL)
    add_custom_command(
            TARGET Spritter POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> "${CMAKE_BINARY_DIR}"
            VERBATIM
    )
#else()
    #find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
#endif()

target_link_libraries(Spritter PUBLIC SDL3::SDL3)

# ---------- FreeType ----------
add_subdirectory(lib/freetype)
target_link_libraries(Spritter PUBLIC freetype)


# ---------- GRABS ----------
if (SP_USE_GRABS)
    add_compile_definitions(SP_ENABLE_GRABS)
    add_subdirectory(lib/grabs.Native)
    target_link_libraries(Spritter PUBLIC grabs)
endif()

# ---------- GLAD ----------

add_subdirectory(lib/glad)
target_link_libraries(Spritter PUBLIC glad)

# ---------- D3D11 ----------

if (SP_ENABLE_D3D11)
    target_link_libraries(Spritter PUBLIC d3d11 dxgi d3dcompiler)
    add_compile_definitions(SP_ENABLE_D3D11)
endif()

# ---------- STB ----------

add_subdirectory(lib/stb)
target_link_libraries(Spritter PUBLIC stb)

# ---------- Content ----------

function(spritter_set_content target srcdir destdir)
    add_custom_target(
            SpContentCopyFor${target} ALL
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${srcdir}" "${destdir}"
    )
    add_dependencies(${target} SpContentCopyFor${target})
endfunction()

# ----- Example -----
if (SP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ----- TEST -----

if (SP_BUILD_TEST)
    add_executable(SpTest tests/main.cpp)
    target_link_libraries(SpTest PRIVATE Spritter)
    target_link_libraries(SpTest PRIVATE stdc++)
    spritter_set_content(SpTest ${CMAKE_SOURCE_DIR}/tests/Content ${CMAKE_BINARY_DIR}/Content)
endif()