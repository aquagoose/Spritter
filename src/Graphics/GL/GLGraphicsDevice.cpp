#include "GLGraphicsDevice.h"

#include <glad/glad.h>

namespace Spritter::Graphics::GL
{
    GLGraphicsDevice::GLGraphicsDevice(SDL_Window* window) : _window(window)
    {
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    }

    void GLGraphicsDevice::Clear()
    {
        glClearColor(1.0f, 0.5f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLGraphicsDevice::Present()
    {
        SDL_GL_SetSwapInterval(1);
        SDL_GL_SwapWindow(_window);
    }
}
