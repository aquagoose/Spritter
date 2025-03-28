#include "Spritter/UI/Panel.h"

namespace Spritter::UI
{
    Math::Size Panel::Size()
    {
        return { 0, 0 };
    }

    void Panel::Update(float dt, const Math::Vector2i& position, const Math::Size& parentSize, bool* mouseCaptured)
    {
        Control::Update(dt, position, parentSize, mouseCaptured);
    }

    void Panel::Draw(Graphics::SpriteRenderer& renderer, const Math::Vector2i& position)
    {
        renderer.DrawRectangle(position.As<float>(), { 100, 100 }, Theme.BackgroundColor);
    }
}
