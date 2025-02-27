#include "GLGraphicsDevice.h"

#include <glad/glad.h>

#include "GLRenderable.h"
#include "GLShader.h"
#include "GLTexture.h"

namespace Spritter::Graphics::GL
{
    GLGraphicsDevice::GLGraphicsDevice(SDL_Window* window) : _window(window)
    {
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
        _vsync = true;
    }

    bool GLGraphicsDevice::VSyncMode()
    {
        return _vsync;
    }

    void GLGraphicsDevice::SetVSyncMode(bool vsync)
    {
        _vsync = vsync;
    }

    Math::Rectangle GLGraphicsDevice::Viewport()
    {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        return { viewport[0], viewport[1], viewport[2], viewport[3] };
    }

    void GLGraphicsDevice::SetViewport(const Math::Rectangle& viewport)
    {
        glViewport(viewport.X(), viewport.Y(), viewport.Width(), viewport.Height());
    }

    std::unique_ptr<Shader> GLGraphicsDevice::CreateShader(ShaderAttachment* attachments, int numAttachments)
    {
        return std::make_unique<GLShader>(attachments, numAttachments);
    }

    std::unique_ptr<Renderable> GLGraphicsDevice::CreateRenderable(const RenderableDefinition& definition)
    {
        return std::make_unique<GLRenderable>(definition);
    }

    std::unique_ptr<Texture> GLGraphicsDevice::CreateTexture(uint32_t width, uint32_t height, PixelFormat format,
        void* data)
    {
        return std::make_unique<GLTexture>(width, height, format, data);
    }

    void GLGraphicsDevice::Clear(const Math::Color& color)
    {
        glClearColor(color.R, color.G, color.B, color.A);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLGraphicsDevice::Present()
    {
        SDL_GL_SetSwapInterval(_vsync ? 1 : 0);
        SDL_GL_SwapWindow(_window);
    }
}
