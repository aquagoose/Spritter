#pragma once

#include <string>

#include <SDL3/SDL.h>

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

        /// Get the native handle for the window.
        /// @return The native SDL window handle for the window.
        [[nodiscard]] SDL_Window* Handle() const;
    };
}