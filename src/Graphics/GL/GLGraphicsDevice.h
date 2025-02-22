#pragma once

#include <SDL3/SDL.h>

#include "Spritter/Graphics/GraphicsDevice.h"

namespace Spritter::Graphics::GL
{
    class GLGraphicsDevice : public GraphicsDevice
    {
    private:
        SDL_Window* _window;

    public:
        explicit GLGraphicsDevice(SDL_Window* window);

        std::unique_ptr<Shader> CreateShader(ShaderAttachment* attachments, int numAttachments) override;

        std::unique_ptr<Renderable> CreateRenderable(const RenderableDefinition& definition) override;

        void Clear(const Math::Color& color) override;

        void Present() override;
    };
}
