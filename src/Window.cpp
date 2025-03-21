#include "Spritter/Window.h"

#include <iostream>
#include <stdexcept>

namespace Spritter
{
    Window::Window(const std::string& title, const Math::Size& size)
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
            throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));

        _window = SDL_CreateWindow(title.c_str(), size.Width, size.Height, SDL_WINDOW_OPENGL);
        if (!_window)
            throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }

    Window::~Window()
    {
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }
}
