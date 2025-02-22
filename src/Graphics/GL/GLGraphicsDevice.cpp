#include "GLGraphicsDevice.h"

#include <glad/glad.h>

#include "GLRenderable.h"

namespace Spritter::Graphics::GL
{
    GLGraphicsDevice::GLGraphicsDevice(SDL_Window* window) : _window(window)
    {
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    }

    std::unique_ptr<Renderable> GLGraphicsDevice::CreateRenderable(const RenderableDefinition& definition)
    {
        return std::make_unique<GLRenderable>(definition);
    }

    void GLGraphicsDevice::Clear(const Math::Color& color)
    {
        glClearColor(color.R, color.G, color.B, color.A);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLGraphicsDevice::Present()
    {
        SDL_GL_SetSwapInterval(1);
        SDL_GL_SwapWindow(_window);
    }
}
