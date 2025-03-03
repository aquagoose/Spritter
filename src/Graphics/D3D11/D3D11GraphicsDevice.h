#pragma once

#include <SDL3/SDL.h>
#include <d3d11.h>

#include "Spritter/Graphics/GraphicsDevice.h"

namespace Spritter::Graphics::D3D11
{
    class D3D11GraphicsDevice final : public GraphicsDevice
    {
        ID3D11Device* _device{};
        ID3D11DeviceContext* _context{};
        IDXGISwapChain* _swapchain{};
        ID3D11Texture2D* _swapchainTexture{};
        ID3D11RenderTargetView* _swapchainTarget{};

    public:
        explicit D3D11GraphicsDevice(SDL_Window* window);
        ~D3D11GraphicsDevice() override;

        bool VSyncMode() override;
        void SetVSyncMode(bool vsync) override;

        Graphics::FullscreenMode FullscreenMode() override;
        void SetFullscreenMode(Graphics::FullscreenMode mode) override;

        Math::Rectangle Viewport() override;
        void SetViewport(const Math::Rectangle& viewport) override;

        std::unique_ptr<Shader> CreateShader(ShaderAttachment* attachments, int numAttachments) override;

        std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) override;

        std::unique_ptr<Texture> CreateTexture(uint32_t width, uint32_t height, PixelFormat format, void* data) override;

        void Clear(const Math::Color& color) override;

        void Present() override;

        void ResizeSwapchain(const Math::Size& size) override;
    };
}
