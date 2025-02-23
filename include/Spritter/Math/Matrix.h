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
    };

    using Matrixf = Matrix<float>;
    using Matrixd = Matrix<double>;
}
