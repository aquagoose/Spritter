#pragma once

#include <SDL3/SDL.h>

#include "Spritter/Graphics/GraphicsDevice.h"

namespace Spritter::Graphics::GL
{
    class GLGraphicsDevice : public GraphicsDevice
    {
    private:
        SDL_Window* _window;
        bool _vsync{};

    public:
        explicit GLGraphicsDevice(SDL_Window* window);

        bool VSyncMode() override;
        void SetVSyncMode(bool vsync) override;

        std::unique_ptr<Shader> CreateShader(ShaderAttachment* attachments, int numAttachments) override;

        std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) override;

        std::unique_ptr<Texture> CreateTexture(uint32_t width, uint32_t height, PixelFormat format, void* data) override;

        void Clear(const Math::Color& color) override;

        void Present() override;
    };
}
