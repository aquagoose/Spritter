#include <utility>

#include "Spritter/Game.h"

namespace Spritter {
    Game::Game(GameOptions options) : _options(std::move(options)) {}

    void Game::Run()
    {
        _window = std::make_unique<Window_>(_options.Name, _options.Size);

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

    void Game::Close()
    {
        _alive = false;
    }

    Window* Game::Window() const
    {
        return _window.get();
    }
}
