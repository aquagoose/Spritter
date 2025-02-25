#pragma once

#include "Vector2.h"
#include "Size.h"

namespace Spritter::Math
{
    struct Rectangle
    {
        Vector2i Position;
        Math::Size Size;

        Rectangle(const Vector2i& position, const Math::Size& size)
        {
            Position = position;
            Size = size;
        }

        Rectangle(int32_t x, int32_t y, int32_t width, int32_t height)
        {
            Position = { x, y };
            Size = { width, height };
        }

        [[nodiscard]] int32_t X() const
        {
            return Position.X;
        }

        [[nodiscard]] int32_t Y() const
        {
            return Position.Y;
        }

        [[nodiscard]] int32_t Width() const
        {
            return Size.Width;
        }

        [[nodiscard]] int32_t Height() const
        {
            return Size.Height;
        }
    };
}
