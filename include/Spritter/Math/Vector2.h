#pragma once

#include <cstdint>
#include <string>

#include "Matrix.h"

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

        friend Vector2 operator *(const Vector2& left, const Vector2& right)
        {
            return { left.X * right.X, left.Y * right.Y};
        }

        friend Vector2 operator *(const Vector2& left, const T right)
        {
            return { left.X * right, left.Y * right };
        }

        friend Vector2 operator *(const Vector2& vector, const Matrix<T>& matrix)
        {
            return
            {
                vector.X * matrix.Row0.X + vector.Y * matrix.Row1.X + matrix.Row3.X,
                vector.X * matrix.Row0.Y + vector.Y * matrix.Row1.Y + matrix.Row3.Y,
            };
        }

        static Vector2 Zero()
        {
            return { 0, 0 };
        }

        static Vector2 One()
        {
            return { 1, 1 };
        }
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int32_t>;
}
