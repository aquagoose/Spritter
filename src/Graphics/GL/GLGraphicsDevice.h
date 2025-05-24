#pragma once

#include <SDL3/SDL.h>

#include "Spritter/Graphics/GraphicsDevice.h"

namespace Spritter::Graphics::GL
{
    class GLGraphicsDevice : public GraphicsDevice
    {
    private:
        SDL_Window* _window;
        SDL_GLContext _context;
        bool _vsync{};
        bool _isRendering{};

    public:
        explicit GLGraphicsDevice(SDL_Window* window);
        ~GLGraphicsDevice() override;

        bool VSyncMode() override;
        void SetVSyncMode(bool vsync) override;

        Graphics::FullscreenMode FullscreenMode() override;
        void SetFullscreenMode(Graphics::FullscreenMode mode) override;

        Math::Rectangle Viewport() override;
        void SetViewport(const Math::Rectangle& viewport) override;

        std::unique_ptr<Shader> CreateShader(ShaderAttachment* attachments, int numAttachments) override;

        std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) override;

        std::unique_ptr<Texture> CreateTexture(uint32_t width, uint32_t height, PixelFormat format, void* data) override;

        void BeginRendering(const Math::Color& color) override;
        void EndRendering() override;

        void Present() override;

        void ResizeSwapchain(const Math::Size& size) override;
    };
}
