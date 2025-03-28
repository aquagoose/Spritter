#pragma once

#include "Control.h"

namespace Spritter::UI
{
    class Panel : public Control
    {
    public:
        std::shared_ptr<Control> BaseControl;

        explicit Panel(const UI::Theme& theme) : Control(theme) { }

        [[nodiscard]] Math::Size Size() override;

        void Update(float dt, const Math::Vector2i& position, const Math::Size& parentSize, bool* mouseCaptured) override;
        void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) override;
    };
}