#pragma once

#include <memory>
#include <string>

#include "Window.h"
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
        using Window_ = Spritter::Window;

        GameOptions _options;
        bool _alive{};
        std::unique_ptr<Window_> _window{};

    public:
        explicit Game(GameOptions  options);

        void Run();
        void Close();

        [[nodiscard]] Window_* Window() const;
    };
}
