#include "Spritter/Window.h"

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

        _context = SDL_GL_CreateContext(_window);
        if (!_context)
            throw std::runtime_error("Failed to create GL context: " + std::string(SDL_GetError()));
    }

    Window::~Window()
    {
        SDL_GL_DestroyContext(_context);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    SDL_Window* Window::Handle() const
    {
        return _window;
    }
}
