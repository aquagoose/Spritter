#pragma once

#include <cstdint>

namespace Spritter::Math
{
    template <typename T>
    struct Vector2
    {
        T X;
        T Y;

        Vector2()
        {
            X = 0;
            Y = 0;
        }

        explicit Vector2(const T scalar)
        {
            X = scalar;
            Y = scalar;
        }

        Vector2(const T x, const T y)
        {
            X = x;
            Y = y;
        }
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int32_t>;
}
