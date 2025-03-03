#include "D3D11GraphicsDevice.h"

namespace Spritter::Graphics::D3D11
{
    D3D11GraphicsDevice::D3D11GraphicsDevice(SDL_Window* window)
    {
    }

    D3D11GraphicsDevice::~D3D11GraphicsDevice()
    {
    }

    bool D3D11GraphicsDevice::VSyncMode()
    {
        return true;
    }

    void D3D11GraphicsDevice::SetVSyncMode(bool vsync)
    {
    }

    Graphics::FullscreenMode D3D11GraphicsDevice::FullscreenMode()
    {
        return FullscreenMode::Windowed;
    }

    void D3D11GraphicsDevice::SetFullscreenMode(Graphics::FullscreenMode mode)
    {
    }

    Math::Rectangle D3D11GraphicsDevice::Viewport()
    {
        return {};
    }

    void D3D11GraphicsDevice::SetViewport(const Math::Rectangle& viewport)
    {
    }

    std::unique_ptr<Shader> D3D11GraphicsDevice::CreateShader(ShaderAttachment* attachments, int numAttachments)
    {
        return nullptr;
    }

    std::unique_ptr<Renderable> D3D11GraphicsDevice::CreateRenderable(const RenderableDefinition& definition)
    {
        return nullptr;
    }

    std::unique_ptr<Texture> D3D11GraphicsDevice::CreateTexture(uint32_t width, uint32_t height, PixelFormat format,
        void* data)
    {
        return nullptr;
    }

    void D3D11GraphicsDevice::Clear(const Math::Color& color)
    {
    }

    void D3D11GraphicsDevice::Present()
    {
    }

    void D3D11GraphicsDevice::ResizeSwapchain(const Math::Size& size)
    {
    }
}
