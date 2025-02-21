#pragma once

#include <memory>

#include "Window.h"

namespace Spritter
{

    class Game
    {
    private:
        bool _alive{};

        std::unique_ptr<Spritter::Window> _window{};

    public:
        Game();

        void Run();

        Spritter::Window* Window() const;
    };

}
