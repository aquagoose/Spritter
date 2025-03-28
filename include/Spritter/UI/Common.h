#pragma once

#include <utility>

#include "Spritter/Graphics/Font.h"
#include "Spritter/Math/Math.h"

namespace Spritter::UI
{
    struct Theme
    {
        std::shared_ptr<Graphics::Font> Font;

        Math::Color TextColor;

        Math::Color BackgroundColor;

        Math::Color ButtonBackground;
        Math::Color ButtonHovered;
        Math::Color ButtonClicked;
        Math::Color ButtonBorder;

        static Theme DefaultLight(std::shared_ptr<Graphics::Font> font)
        {
            return
            {
                /* Font: */ std::move(font),

                /* TextColor: */ Math::Color::White(),

                /* BackgroundColor: */ Math::Color::White(),

                /* ButtonBackground: */ Math::Color::Gray(),
                /* ButtonHovered: */ Math::Color::LightGray(),
                /* ButtonClicked: */ Math::Color::Gray(),
                /* ButtonBorder: */ Math::Color::White()
            };
        }
    };
}
