#pragma once

#include <memory>
#include <string>

#include "Window.h"
#include "Math/Size.h"

namespace Spritter
{
    struct GameOptions
    {
        std::string name;
        Math::Size size;
    };

    class Game
    {
        GameOptions _options;
        bool _alive{};
        std::unique_ptr<Window> _window{};

    public:
        explicit Game(GameOptions options);

        void run();
        void close();

        [[nodiscard]] Window* window() const;
    };
}
