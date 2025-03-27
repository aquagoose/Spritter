#include "Spritter/UI/Label.h"

namespace Spritter::UI
{
    Label::Label(const UIManager& manager, const std::wstring& text, uint32_t fontSize) : Control(manager.Theme)
    {
        _text = text;
        _fontSize = fontSize;
        _size = Theme.Font.MeasureString(text, fontSize);
    }

    void Label::Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position)
    {
        Theme.Font.Draw(renderer, position.As<float>(), _text, _fontSize);
    }
}
