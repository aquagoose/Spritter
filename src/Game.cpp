#include <utility>

#include "Spritter/Game.h"
#include "Graphics/GL/GLGraphicsDevice.h"

namespace Spritter {
    void Game::Run(const GameOptions& options)
    {
        Window = std::make_unique<Spritter::Window>(options.Name, options.Size);
        GraphicsDevice = std::make_unique<Graphics::GL::GLGraphicsDevice>(Window->Handle());

        Initialize();

        _alive = true;
        while (_alive)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                        _alive = false;
                        break;
                }
            }

            Update(1.0f / 60.0f);
            Draw();

            GraphicsDevice->Present();
        }
    }

    void Game::Close()
    {
        _alive = false;
    }
}
