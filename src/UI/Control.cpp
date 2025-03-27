#include "Spritter/UI/Control.h"

#include "Spritter/Input.h"

namespace Spritter::UI
{
    void Control::Update(float dt, const Math::Vector2i& position, const Math::Size& parentSize, bool* mouseCaptured)
    {
        auto mousePos = Input::MousePosition();
        auto size = Size();

        IsHovered = false;

        if (!*mouseCaptured && !AllowClickthrough &&
            mousePos.X >= position.X && mousePos.X < position.X + size.Width &&
            mousePos.Y >= position.Y && mousePos.Y < position.Y + size.Height)
        {
            *mouseCaptured = true;
            IsHovered = true;
        }
    }
}
