#include <utility>

#include "Spritter/Game.h"

namespace Spritter {
    Game::Game(GameOptions options) : _options(std::move(options)) {}

    void Game::run()
    {
        _window = std::make_unique<Window>(_options.name, _options.size);

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

    void Game::close()
    {
        _alive = false;
    }

    Window* Game::window() const
    {
        return _window.get();
    }
}
