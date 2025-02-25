#include "Spritter/Game.h"

#include "SDLUtils.h"
#include "Graphics/GL/GLGraphicsDevice.h"

namespace Spritter {
    Game::Game()
    {
        _current = this;
    }

    void Game::Run(const GameOptions& options)
    {
        Window = std::make_unique<Spritter::Window>(options.Name, options.Size);
        Window->OnClose.Subscribe([this] { _alive = false; } );

        GraphicsDevice = std::make_unique<Graphics::GL::GLGraphicsDevice>(Window->Handle());

        Initialize();

        _alive = true;
        while (_alive)
        {
            _keysPressed.clear();

            Window->ProcessEvents();

            /*SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                        _alive = false;
                        break;
                    case SDL_EVENT_KEY_DOWN:
                    {
                        Key key = SDLUtils::KeycodeToKey(event.key.key);
                        if (event.key.down && !event.key.repeat)
                        {
                            _keysDown.emplace(key);
                            _keysPressed.emplace(key);
                        }

                        break;
                    }
                    case SDL_EVENT_KEY_UP:
                    {
                        Key key = SDLUtils::KeycodeToKey(event.key.key);
                        _keysDown.erase(key);
                        _keysPressed.erase(key);
                        break;
                    }
                }
            }*/

            Update(1.0f / 60.0f);
            Draw();

            GraphicsDevice->Present();
        }
    }

    void Game::Close()
    {
        _alive = false;
    }

    bool Game::IsKeyDown(const Key key) const
    {
        return _keysDown.count(key);
    }

    bool Game::IsKeyPressed(const Key key) const
    {
        return _keysPressed.count(key);
    }

    Game* Game::_current;
    Game* Game::Current()
    {
        return _current;
    }
}
