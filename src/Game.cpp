#include "Spritter/Game.h"

namespace Spritter {
    Game::Game() = default;

    void Game::Run()
    {
        _window = std::make_unique<Spritter::Window>();

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
        }
    }

    Spritter::Window* Game::Window() const
    {
        return _window.get();
    }
}
