#include "Spritter/UI/Button.h"

namespace Spritter::UI
{
    Button::Button(const UI::Theme& theme, const std::wstring& text, const Math::Size& size) : Control(theme)
    {
        _size = size;
    }

    void Button::Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position)
    {
        Math::Color color = Math::Color::Gray();

        if (IsHovered)
            color = Math::Color::White();

        renderer.DrawRectangle(position.As<float>(), _size, color);
    }
}
