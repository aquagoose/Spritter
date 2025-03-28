#include "Spritter/UI/Label.h"

namespace Spritter::UI
{
    Label::Label(const UI::Theme& theme, const std::wstring& text, uint32_t fontSize) : Control(theme)
    {
        _text = text;
        _fontSize = fontSize;
        _size = Theme.Font->MeasureString(text, fontSize);
    }

    void Label::Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position)
    {
        Theme.Font->Draw(renderer, position.As<float>(), _text, _fontSize, Theme.LabelColor);
    }
}
