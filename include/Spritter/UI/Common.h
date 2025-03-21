#pragma once

#include "Spritter/Graphics/Font.h"

namespace Spritter::UI
{
    struct Theme
    {
        Graphics::Font& Font;

        static Theme DefaultLight(Graphics::Font& font)
        {
            return
            {
                font
            };
        }
    };
}
