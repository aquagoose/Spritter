#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Math/Size.h"

namespace Spritter
{
    class Window
    {
    private:
        SDL_Window* _window;
        SDL_GLContext _context;

    public:
        Window(const std::string& title, const Math::Size& size);
        ~Window();

        [[nodiscard]] SDL_Window* Handle() const;
    };
}