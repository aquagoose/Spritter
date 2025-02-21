#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

namespace Spritter
{
    class Window
    {
    private:
        SDL_Window* _window;
        SDL_GLContext _context;

    public:
        Window();
        ~Window();
    };
}