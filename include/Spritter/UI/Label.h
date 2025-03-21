#pragma once

#include <string>

#include "Control.h"
#include "UIManager.h"

namespace Spritter::UI
{
    class Label final : public Control
    {
        std::wstring _text;
        uint32_t _fontSize;

    public:
        Label(const UIManager& manager, const std::wstring& text, uint32_t fontSize);

        [[nodiscard]] const std::wstring& Text() const
        {
            return _text;
        }

        void SetText(const std::wstring& text)
        {
            _text = text;
        }

        [[nodiscard]] uint32_t FontSize() const
        {
            return _fontSize;
        }

        void SetFontSize(uint32_t size)
        {
            _fontSize = size;
        }

        void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) override;
    };
}
