#pragma once

#include "Control.h"
#include "UIManager.h"

namespace Spritter::UI
{
    class Button final : public Control
    {
        Math::Size _size;

    public:
        Button(UIManager& manager, const std::wstring& text, const Math::Size& size);

        Math::Size Size() override
        {
            return _size;
        }

        void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) override;
    };
}
