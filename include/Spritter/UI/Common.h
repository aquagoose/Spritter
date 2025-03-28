#pragma once

#include <utility>

#include "Spritter/Graphics/Font.h"
#include "Spritter/Math/Math.h"

namespace Spritter::UI
{
    struct Theme
    {
        std::shared_ptr<Graphics::Font> Font;

        Math::Color LabelColor;

        Math::Color BackgroundColor;

        Math::Color ButtonBackground;
        Math::Color ButtonHovered;
        Math::Color ButtonClicked;
        Math::Color ButtonBorder;
        int32_t BorderWidth;
        Math::Color ButtonText;
        uint32_t ButtonTextSize;

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
                /* ButtonBorder: */ Math::Color::White(),
                /* BorderWidth: */ 1,
                /* ButtonText: */ Math::Color::White(),
                /* ButtonTextSize: */ 32
            };
        }

        static Theme DefaultDark(std::shared_ptr<Graphics::Font> font)
        {
            return
            {
                /* Font: */ std::move(font),

                /* TextColor: */ Math::Color::White(),

                /* BackgroundColor: */ Math::Color::Black(),

                /* ButtonBackground: */ Math::Color::Black(),
                /* ButtonHovered: */ Math::Color(0.2f, 0.2f, 0.2f),
                /* ButtonClicked: */ Math::Color::Black(),
                /* ButtonBorder: */ Math::Color::LightGray(),
                /* BorderWidth: */ 1,
                /* ButtonText: */ Math::Color::White(),
                /* ButtonTextSize: */ 32
            };
        }
    };
}
