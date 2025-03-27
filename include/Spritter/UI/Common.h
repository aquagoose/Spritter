#pragma once

#include "Spritter/Graphics/Font.h"

namespace Spritter::UI
{
    struct Theme
    {
        std::shared_ptr<Graphics::Font> Font;

        static Theme DefaultLight(std::shared_ptr<Graphics::Font> font)
        {
            return
            {
                font
            };
        }
    };
}
