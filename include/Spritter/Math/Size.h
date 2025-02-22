#pragma once
#include <cstdint>

namespace Spritter::Math
{
    struct Size
    {
        int32_t Width;

        int32_t Height;

        Size(const int32_t width, const int32_t height)
        {
            Width = width;
            Height = height;
        }
    };
}
