#pragma once

#include <cstdint>
#include <string>

namespace Spritter::Math
{
    template <typename T>
    struct Vector4
    {
        T X;
        T Y;
        T Z;
        T W;

        Vector4()
        {
            X = 0;
            Y = 0;
            Z = 0;
            W = 0;
        }

        explicit Vector4(const T scalar)
        {
            X = scalar;
            Y = scalar;
            Z = scalar;
            W = scalar;
        }

        Vector4(const T x, const T y, const T z, const T w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        [[nodiscard]] std::string ToString() const
        {
            return "{ X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + ", W: " + std::to_string(W) + " }";
        }

        static Vector4 Zero()
        {
            return Vector4(0);
        }

        static Vector4 One()
        {
            return Vector4(1);
        }

        static Vector4 UnitX()
        {
            return Vector4(1, 0, 0, 0);
        }

        static Vector4 UnitY()
        {
            return Vector4(0, 1, 0, 0);
        }

        static Vector4 UnitZ()
        {
            return Vector4(0, 0, 1, 0);
        }

        static Vector4 UnitW()
        {
            return Vector4(0, 0, 0, 1);
        }

        static T Dot(const Vector4& a, const Vector4& b)
        {
            return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
        }
    };

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;
    using Vector4i = Vector4<int32_t>;
}
