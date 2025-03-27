#pragma once

#include "Spritter/Graphics/SpriteRenderer.h"
#include "Spritter/Math/Math.h"

#include "Common.h"

namespace Spritter::UI
{
    class Control
    {
        Math::Size _size;

    protected:
        bool IsHovered{};

    public:
        UI::Theme Theme;

        virtual ~Control() = default;

        [[nodiscard]] virtual Math::Size Size() = 0;

        virtual void Update(float dt, const Math::Vector2i& position, const Math::Size& parentSize, bool* mouseCaptured);

        virtual void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) = 0;

    protected:
        explicit Control(const UI::Theme& theme) : Theme(theme) { }
    };
}
