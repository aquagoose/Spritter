#pragma once
#include <cstdint>

namespace Spritter::Math
{
    struct Size
    {
        int32_t Width;

        int32_t Height;

        Size()
        {
            Width = 0;
            Height = 0;
        }

        Size(const int32_t width, const int32_t height)
        {
            Width = width;
            Height = height;
        }
    };
}
