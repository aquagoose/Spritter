#pragma once

#include <grabs/grabs.h>
#include <SDL3/SDL.h>

#include "Spritter/Graphics/GraphicsDevice.h"

namespace Spritter::Graphics::Grabs
{
    class GrabsGraphicsDevice : public GraphicsDevice
    {
        SDL_Window* _window;

        GsInstance _instance{};
        GsDevice _device{};
        GsSurface _surface{};
        GsSwapchain _swapchain{};
        GsCommandList _commandList{};
        GsTexture _currentSwapchainTexture{};
        bool _isInRenderPass{};

    public:
        explicit GrabsGraphicsDevice(SDL_Window* window, const Math::Size& windowSize);
        ~GrabsGraphicsDevice() override;

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
