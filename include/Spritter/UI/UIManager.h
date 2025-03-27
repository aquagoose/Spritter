#pragma once

#include <cassert>

#include "Control.h"

namespace Spritter::UI
{
    class UIManager
    {
        Graphics::GraphicsDevice& _device;
        std::unique_ptr<Graphics::SpriteRenderer> _spriteRenderer;
        std::shared_ptr<Control> _baseControl;

        Math::Size _baseSize{};

    public:
        UI::Theme Theme;

        explicit UIManager(Graphics::GraphicsDevice& device, const UI::Theme& theme);

        [[nodiscard]] std::shared_ptr<Control> BaseControl() const
        {
            return _baseControl;
        }

        void SetBaseControl(const std::shared_ptr<Control>& control);

        void Update(float dt);
        void Draw() const;
    };
}