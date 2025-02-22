#pragma once
#include <cstdint>

namespace Spritter::Math
{
    struct Size
    {
        int32_t width;

        int32_t height;

        Size(const int32_t width, const int32_t height)
        {
            this->width = width;
            this->height = height;
        }
    };
}
