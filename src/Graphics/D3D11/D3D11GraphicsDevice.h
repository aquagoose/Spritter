#pragma once

#include <SDL3/SDL.h>

#include "Spritter/Graphics/GraphicsDevice.h"

namespace Spritter::Graphics::D3D11
{
    class D3D11GraphicsDevice : public GraphicsDevice
    {
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
