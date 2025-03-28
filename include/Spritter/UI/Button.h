#pragma once

#include "Control.h"

namespace Spritter::UI
{
    class Button final : public Control
    {
        Math::Size _size;
        std::wstring _text;

    public:
        Button(const UI::Theme& theme, const std::wstring& text, const Math::Size& size, std::function<void()> onClicked = nullptr);

        Math::Size Size() override
        {
            return _size;
        }

        void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) override;
    };
}
