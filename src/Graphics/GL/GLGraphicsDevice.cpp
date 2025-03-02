#include "GLGraphicsDevice.h"

#include <stdexcept>

#include <glad/glad.h>

#include "GLRenderable.h"
#include "GLShader.h"
#include "GLTexture.h"

namespace Spritter::Graphics::GL
{
    GLGraphicsDevice::GLGraphicsDevice(SDL_Window* window) : _window(window)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        _context = SDL_GL_CreateContext(_window);
        if (!_context)
            throw std::runtime_error("Failed to create GL context: " + std::string(SDL_GetError()));

        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
        _vsync = true;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
    }

    GLGraphicsDevice::~GLGraphicsDevice()
    {
        SDL_GL_DestroyContext(_context);
    }

    bool GLGraphicsDevice::VSyncMode()
    {
        return _vsync;
    }

    void GLGraphicsDevice::SetVSyncMode(const bool vsync)
    {
        _vsync = vsync;
    }

    Graphics::FullscreenMode GLGraphicsDevice::FullscreenMode()
    {
        const auto flags = SDL_GetWindowFlags(_window);

        if (flags & SDL_WINDOW_FULLSCREEN)
            return FullscreenMode::BorderlessFullscreen;

        return FullscreenMode::Windowed;
    }

    void GLGraphicsDevice::SetFullscreenMode(const Graphics::FullscreenMode mode)
    {
        switch (mode)
        {
            case FullscreenMode::Windowed:
                SDL_SetWindowFullscreen(_window, false);
                break;
            case FullscreenMode::BorderlessFullscreen:
                SDL_SetWindowFullscreen(_window, true);
                break;
            //case FullscreenMode::ExclusiveFullscreen:
            //    break;
        }
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

    void GLGraphicsDevice::ResizeSwapchain(const Math::Size& size)
    {
        glViewport(0, 0, size.Width, size.Height);
    }
}
