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

        Vector2& operator +=(const Vector2& delta)
        {
            this->X += delta.X;
            this->Y += delta.Y;

            return *this;
        }

        friend Vector2 operator +(const Vector2& left, const Vector2& right)
        {
            return { left.X + right.X, left.Y + right.Y };
        }

        static Vector2 Zero()
        {
            return { 0, 0 };
        }
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int32_t>;
}
