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

        void Clear() override;

        void Present() override;
    };
}
