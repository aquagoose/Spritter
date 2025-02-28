#pragma once

#include <memory>
#include <string>

#include "Window.h"
#include "Graphics/GraphicsDevice.h"
#include "Math/Size.h"

namespace Spritter
{
    // TODO: WindowOptions, GraphicsOptions, etc.
    struct GameOptions
    {
        std::string Name = "Spritter";
        Math::Size Size = { 1280, 720 };

        bool Resizable = false;
        Graphics::FullscreenMode FullscreenMode = Graphics::FullscreenMode::Windowed;

        bool VSync = true;
        uint32_t TargetFPS = 0;
    };

    class Game
    {
        bool _alive{};
        inline static Game* _current;

    public:
        std::unique_ptr<Spritter::Window> Window{};
        std::unique_ptr<Graphics::GraphicsDevice> GraphicsDevice;

    protected:
        /// Called once the game is initialized and ready.
        virtual void Initialize() {}

        /// Called once per frame. Put game logic in here.
        /// @param dt The time, in seconds, since the last frame.
        virtual void Update(const float dt) {}

        /// Called once per frame. Put drawing commands in here.
        virtual void Draw() {}

    public:
        Game()
        {
            _current = this;
        }

        virtual ~Game() = default;

        /// Start and initialize the game.
        /// @param options The game options to use on startup.
        void Run(const GameOptions& options);

        /// Gracefully close and exit the game.
        void Close();

        /// Get the currently active game instance.
        /// @return The currently active game instance.
        static Game* Current()
        {
            return _current;
        }
    };
}
