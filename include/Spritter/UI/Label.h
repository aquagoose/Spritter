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

        void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) override;
    };
}
