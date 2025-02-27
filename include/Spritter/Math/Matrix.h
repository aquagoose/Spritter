#pragma once

#include <cmath>
#include <string>

#include "Vector4.h"

namespace Spritter::Math
{
    template <typename T>
    struct Matrix
    {
        Vector4<T> Row0;
        Vector4<T> Row1;
        Vector4<T> Row2;
        Vector4<T> Row3;

        Matrix()
        {
            Row0 = Vector4<T>::Zero();
            Row1 = Vector4<T>::Zero();
            Row2 = Vector4<T>::Zero();
            Row3 = Vector4<T>::Zero();
        }

        Matrix(const Vector4<T>& row0, const Vector4<T>& row1, const Vector4<T>& row2, const Vector4<T>& row3)
        {
            Row0 = row0;
            Row1 = row1;
            Row2 = row2;
            Row3 = row3;
        }

        [[nodiscard]] Vector4<T> Column0() const
        {
            return { Row0.X, Row1.X, Row2.X, Row3.X };
        }

        [[nodiscard]] Vector4<T> Column1() const
        {
            return { Row0.Y, Row1.Y, Row2.Y, Row3.Y };
        }

        [[nodiscard]] Vector4<T> Column2() const
        {
            return { Row0.Z, Row1.Z, Row2.Z, Row3.Z };
        }

        [[nodiscard]] Vector4<T> Column3() const
        {
            return { Row0.W, Row1.W, Row2.W, Row3.W };
        }

        [[nodiscard]] std::string ToString() const
        {
            return "{ Row0: " + Row0.ToString() + ", Row1: " + Row1.ToString() + ", Row2: " + Row2.ToString() + ", Row3: " + Row3.ToString() + " }";
        }

        Matrix operator *(const Matrix& other)
        {
            const auto col0 = other.Column0();
            const auto col1 = other.Column1();
            const auto col2 = other.Column2();
            const auto col3 = other.Column3();

            return
            {
                {
                    Vector4<T>::Dot(Row0, col0),
                    Vector4<T>::Dot(Row0, col1),
                    Vector4<T>::Dot(Row0, col2),
                    Vector4<T>::Dot(Row0, col3),
                },
                {
                    Vector4<T>::Dot(Row1, col0),
                    Vector4<T>::Dot(Row1, col1),
                    Vector4<T>::Dot(Row1, col2),
                    Vector4<T>::Dot(Row1, col3),
                },
                {
                    Vector4<T>::Dot(Row2, col0),
                    Vector4<T>::Dot(Row2, col1),
                    Vector4<T>::Dot(Row2, col2),
                    Vector4<T>::Dot(Row2, col3),
                },
                {
                    Vector4<T>::Dot(Row3, col0),
                    Vector4<T>::Dot(Row3, col1),
                    Vector4<T>::Dot(Row3, col2),
                    Vector4<T>::Dot(Row3, col3),
                }
            };
        }

        static Matrix Identity()
        {
            return
            {
                Vector4<T>::UnitX(),
                Vector4<T>::UnitY(),
                Vector4<T>::UnitZ(),
                Vector4<T>::UnitW(),
            };
        }

        static Matrix OrthographicProjection(const T left, const T right, const T bottom, const T top,
                                             const T nearPlane, const T farPlane)
        {
            constexpr T one = static_cast<T>(1.0);
            constexpr T two = static_cast<T>(2.0);

            return
            {
                { two / (right - left), 0, 0, 0 },
                { 0, two / (top - bottom), 0, 0 },
                { 0, 0, one / (farPlane - nearPlane), 0 },
                { (left + right) / (left - right), (top + bottom) / (bottom - top), nearPlane / (nearPlane - farPlane), 1 }
            };
        }

        static Matrix Translate(const T x, const T y, const T z)
        {
            auto matrix = Identity();

            matrix.Row3.X = x;
            matrix.Row3.Y = y;
            matrix.Row3.Z = z;

            return matrix;
        }

        static Matrix RotateZ(const T theta)
        {
            const auto sinTheta = std::sin(theta);
            const auto cosTheta = std::cos(theta);

            auto matrix = Identity();
            matrix.Row0.X = cosTheta;
            matrix.Row1.X = -sinTheta;
            matrix.Row0.Y = sinTheta;
            matrix.Row1.Y = cosTheta;

            return matrix;
        }
    };

    using Matrixf = Matrix<float>;
    using Matrixd = Matrix<double>;
}
