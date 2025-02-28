#include "GrabsGraphicsDevice.h"

namespace Spritter::Graphics::Grabs
{
    GrabsGraphicsDevice::GrabsGraphicsDevice(SDL_Window* window)
    {
        _window = window;

        GsInstanceInfo instanceInfo
        {
            "Spritter",
            GS_BACKEND_UNKNOWN,
            true
        };

        gsCreateInstance(&instanceInfo, &_instance);
    }

    GrabsGraphicsDevice::~GrabsGraphicsDevice()
    {
        gsDestroyInstance(_instance);
    }

    bool GrabsGraphicsDevice::VSyncMode()
    {
        return false;
    }

    void GrabsGraphicsDevice::SetVSyncMode(bool vsync)
    {
    }

    Graphics::FullscreenMode GrabsGraphicsDevice::FullscreenMode()
    {
        return FullscreenMode::Windowed;
    }

    void GrabsGraphicsDevice::SetFullscreenMode(Graphics::FullscreenMode mode)
    {
    }

    Math::Rectangle GrabsGraphicsDevice::Viewport()
    {
        return { 0, 0, 0, 0 };
    }

    void GrabsGraphicsDevice::SetViewport(const Math::Rectangle& viewport)
    {
    }

    std::unique_ptr<Shader> GrabsGraphicsDevice::CreateShader(ShaderAttachment* attachments, int numAttachments)
    {
        return nullptr;
    }

    std::unique_ptr<Renderable> GrabsGraphicsDevice::CreateRenderable(const RenderableDefinition& definition)
    {
        return nullptr;
    }

    std::unique_ptr<Texture> GrabsGraphicsDevice::CreateTexture(uint32_t width, uint32_t height, PixelFormat format,
        void* data)
    {
        return nullptr;
    }

    void GrabsGraphicsDevice::Clear(const Math::Color& color)
    {
    }

    void GrabsGraphicsDevice::Present()
    {
    }

    void GrabsGraphicsDevice::ResizeSwapchain(const Math::Size& size)
    {
    }
}
