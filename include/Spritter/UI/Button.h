#pragma once

#include "Control.h"

namespace Spritter::UI
{
    class Button final : public Control
    {
        Math::Size _size;

    public:
        Button(const UI::Theme& theme, const std::wstring& text, const Math::Size& size);

        Math::Size Size() override
        {
            return _size;
        }

        void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) override;
    };
}
