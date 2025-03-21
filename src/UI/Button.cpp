#include "Spritter/UI/Button.h"

namespace Spritter::UI
{
    Button::Button(UIManager& manager, const std::wstring& text, const Math::Size& size) : Control(manager.Theme)
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
