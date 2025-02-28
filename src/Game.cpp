#include "Spritter/Game.h"

#include "Spritter/Input.h"
#include "SDLUtils.h"
#include "Spritter/Time.h"

#ifdef SP_ENABLE_GRABS
#include "Graphics/grabs/GrabsGraphicsDevice.h"
#else
#include "Graphics/GL/GLGraphicsDevice.h"
#endif

namespace Spritter {
    void Game::Run(const GameOptions& options)
    {
        Window = std::make_unique<Spritter::Window>(options.Name, options.Size);
        Window->SetResizable(options.Resizable);

#ifdef SP_ENABLE_GRABS
        GraphicsDevice = std::make_unique<Graphics::Grabs::GrabsGraphicsDevice>(Window->Handle());
#else
        GraphicsDevice = std::make_unique<Graphics::GL::GLGraphicsDevice>(Window->Handle());
#endif
        GraphicsDevice->SetVSyncMode(options.VSync);
        GraphicsDevice->SetFullscreenMode(options.FullscreenMode);

        Time::SetTargetFPS(options.TargetFPS);

        Initialize();

        _alive = true;
        while (_alive)
        {
            if (Time::Update(GraphicsDevice->VSyncMode()))
                continue;

            Input::Update();

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                        _alive = false;
                        break;
                    case SDL_EVENT_WINDOW_RESIZED:
                        {
                            Math::Size size = Window->Size();
                            GraphicsDevice->ResizeSwapchain(size);
                            break;
                        }
                    case SDL_EVENT_KEY_DOWN:
                    {
                        const Key key = SDLUtils::KeycodeToKey(event.key.key);
                        if (event.key.down && !event.key.repeat)
                            Input::PushKeyDown(key);

                        break;
                    }
                    case SDL_EVENT_KEY_UP:
                    {
                        const Key key = SDLUtils::KeycodeToKey(event.key.key);
                        Input::PushKeyUp(key);
                        break;
                    }
                    case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    {
                        const MouseButton button = SDLUtils::ButtonIndexToButton(event.button.button);
                        Input::PushMouseButtonDown(button);
                        break;
                    }
                    case SDL_EVENT_MOUSE_BUTTON_UP:
                    {
                        const MouseButton button = SDLUtils::ButtonIndexToButton(event.button.button);
                        Input::PushMouseButtonUp(button);
                        break;
                    }
                    case SDL_EVENT_MOUSE_MOTION:
                    {
                        const Math::Vector2f position { event.motion.x, event.motion.y };
                        const Math::Vector2f delta { event.motion.xrel, event.motion.yrel };

                        Input::PushMouseMovement(position, delta);
                    }
                }
            }

            const double dt = Time::DeltaTime();

            Update(static_cast<float>(dt));
            Draw();

            GraphicsDevice->Present();
        }
    }

    void Game::Close()
    {
        _alive = false;
    }
}
