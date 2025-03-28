#include <utility>

#include "Spritter/UI/Button.h"

namespace Spritter::UI
{
    Button::Button(const UI::Theme& theme, const std::wstring& text, const Math::Size& size, std::function<void()> onClicked) : Control(theme)
    {
        _size = size;
        _text = text;
        OnClicked = std::move(onClicked);
    }

    void Button::Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position)
    {
        Math::Color color = Theme.ButtonBackground;

        if (IsHovered)
            color = Theme.ButtonHovered;
        if (IsHeld)
            color = Theme.ButtonClicked;

        renderer.DrawRectangle(position.As<float>(), _size, color, Theme.BorderWidth, Theme.ButtonBorder);

        const Math::Size fontSize = Theme.Font->MeasureString(_text, Theme.ButtonTextSize);

        Theme.Font->Draw(
            renderer, (position +
                Math::Vector2i(_size.Width / 2 - fontSize.Width / 2, _size.Height / 2 - fontSize.Height / 2)).As<float>(),
                _text, Theme.ButtonTextSize, Theme.ButtonText);
    }
}
