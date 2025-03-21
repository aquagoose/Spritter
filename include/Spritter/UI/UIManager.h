#pragma once

#include <cassert>

#include "Control.h"

namespace Spritter::UI
{
    class UIManager
    {
        std::unique_ptr<Graphics::SpriteRenderer> _spriteRenderer;
        std::unique_ptr<Control> _baseControl;

    public:
        UI::Theme Theme;

        explicit UIManager(Graphics::GraphicsDevice& device, const UI::Theme& theme);

        [[nodiscard]] Control& BaseControl() const
        {
            return *_baseControl;
        }

        void SetBaseControl(std::unique_ptr<Control> control)
        {
            _baseControl = std::move(control);
        }

        void Update(float dt) const;
        void Draw() const;
    };
}