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

    public:
        Window(const std::string& title, const Math::Size& size);
        ~Window();

        /// Get the native handle for the window.
        /// @return The native SDL window handle for the window.
        [[nodiscard]] SDL_Window* Handle() const
        {
            return _window;
        }

        /// Get the window size in pixels.
        [[nodiscard]] Math::Size Size() const
        {
            Math::Size size;
            SDL_GetWindowSizeInPixels(_window, &size.Width, &size.Height);
            return size;
        }

        /// Set the window size.
        /// @param size The size to set.
        void SetSize(const Math::Size& size) const
        {
            SDL_SetWindowSize(_window, size.Width, size.Height);
        }

        [[nodiscard]] bool Resizable() const
        {
            return SDL_GetWindowFlags(_window) & SDL_WINDOW_RESIZABLE;
        }

        void SetResizable(const bool resizable) const
        {
            SDL_SetWindowResizable(_window, resizable);
        }
    };
}