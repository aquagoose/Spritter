#pragma once

#include <cstdint>

namespace Spritter::Math
{
    struct Color
    {
        float R;
        float G;
        float B;
        float A;

        Color()
        {
            R = 0;
            G = 0;
            B = 0;
            A = 0;
        }

        Color(const float r, const float g, const float b, const float a = 1.0f)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = UINT8_MAX)
        {
            constexpr float multiplier = 1.0f / static_cast<float>(UINT8_MAX);

            R = static_cast<float>(r) * multiplier;
            G = static_cast<float>(g) * multiplier;
            B = static_cast<float>(b) * multiplier;
            A = static_cast<float>(a) * multiplier;
        }
    };
}