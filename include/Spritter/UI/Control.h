#pragma once

#include "Spritter/Graphics/SpriteRenderer.h"

#include "Common.h"

namespace Spritter::UI
{
    class Control
    {
    public:
        UI::Theme Theme;

        virtual ~Control() = default;

        virtual void Update(float dt) {};
        virtual void Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position) = 0;

    protected:
        explicit Control(const UI::Theme& theme) : Theme(theme) { }
    };
}
