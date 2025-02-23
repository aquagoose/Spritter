#pragma once

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

        static Matrix OrthographicProjectionOffCenter(const float left, const float right, const float bottom,
                                                      const float top, const float nearPlane, const float farPlane)
        {
            return
            {
                { 2.0 / (right - left), 0, 0, 0 },
                { 0, 2.0 / (top - bottom), 0, 0 },
                { 0, 0, 1.0 / (farPlane - nearPlane), 0 },
                { (left + right) / (left - right), (top + bottom) / (bottom - top), nearPlane / (nearPlane - farPlane), 1 }
            };
        }
    };

    using Matrixf = Matrix<float>;
    using Matrixd = Matrix<double>;
}
