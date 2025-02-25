#pragma once

#include <memory>
#include <string>

#include "Window.h"
#include "Graphics/GraphicsDevice.h"
#include "Math/Size.h"

namespace Spritter
{
    struct GameOptions
    {
        std::string Name;
        Math::Size Size;
    };

    class Game
    {
        bool _alive{};
        static Game* _current;

    public:
        std::unique_ptr<Spritter::Window> Window{};
        std::unique_ptr<Graphics::GraphicsDevice> GraphicsDevice;

    protected:
        virtual void Initialize() {}
        virtual void Update(const float dt) {}
        virtual void Draw() {}

    public:
        Game();
        virtual ~Game() = default;

        void Run(const GameOptions& options);
        void Close();

        static Game* Current();
    };
}
