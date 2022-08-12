// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Math.h>

#include <cmath>
#include <sstream>

namespace tg
{
    namespace math
    {
        template<typename T>
        inline Matrix<4, 4, T>::Matrix()
        {
            _v[ 0] = T(1); _v[ 1] = T(0); _v[ 2] = T(0); _v[ 3] = T(0);
            _v[ 4] = T(0); _v[ 5] = T(1); _v[ 6] = T(0); _v[ 7] = T(0);
            _v[ 8] = T(0); _v[ 9] = T(0); _v[10] = T(1); _v[11] = T(0);
            _v[12] = T(0); _v[13] = T(0); _v[14] = T(0); _v[15] = T(1);
        }

        template<typename T>
        inline Matrix<4, 4, T>::Matrix(
            T e0, T e1, T e2, T e3,
            T e4, T e5, T e6, T e7,
            T e8, T e9, T e10, T e11,
            T e12, T e13, T e14, T e15)
        {
            _v[ 0] =  e0; _v[ 1] =  e1; _v[ 2] =  e2; _v[ 3] =  e3;
            _v[ 4] =  e4; _v[ 5] =  e5; _v[ 6] =  e6; _v[ 7] =  e7;
            _v[ 8] =  e8; _v[ 9] =  e9; _v[10] = e10; _v[11] = e11;
            _v[12] = e12; _v[13] = e13; _v[14] = e14; _v[15] = e15;
        }

        template<typename T>
        constexpr const std::array<T, 4 * 4>& Matrix<4, 4, T>::getArray() const
        {
            return _v;
        }

        template<typename T>
        constexpr const T* Matrix<4, 4, T>::getData() const
        {
            return _v.data();
        }

        template<typename T>
        inline constexpr T Matrix<4, 4, T>::operator [] (size_t index) const
        {
            return _v[index];
        }

        template<typename T>
        inline T& Matrix<4, 4, T>::operator [] (size_t index)
        {
            return _v[index];
        }

        template<typename T>
        inline bool Matrix<4, 4, T>::operator == (const Matrix<4, 4, T>& other) const
        {
            return _v == other._v;
        }

        template<typename T>
        inline bool Matrix<4, 4, T>::operator != (const Matrix<4, 4, T>& other) const
        {
            return _v != other._v;
        }

        template<typename T>
        constexpr Matrix<4, 4, T> translate(const Vector<3, T>& value)
        {
            return Matrix<4, 4, T>(
                T(1), T(0), T(0), T(0),
                T(0), T(1), T(0), T(0),
                T(0), T(0), T(1), T(0),
                value[0], value[1], value[2], T(1));
        }

        template<typename T>
        inline Matrix<4, 4, T> rotateX(T angle)
        {
            const T a = std::cos(deg2rad(-angle));
            const T b = std::sin(deg2rad(-angle));
            return Matrix<4, 4, T>(
                T(1), T(0),  T(0), T(0),
                T(0),    a,    -b, T(0),
                T(0),    b,     a, T(0),
                T(0), T(0),  T(0), T(1));
        }

        template<typename T>
        inline Matrix<4, 4, T> rotateY(T angle)
        {
            const T a = std::cos(deg2rad(-angle));
            const T b = std::sin(deg2rad(-angle));
            return Matrix<4, 4, T>(
                   a, T(0),    b, T(0),
                T(0), T(1), T(0), T(0),
                  -b, T(0),    a, T(0),
                T(0), T(0), T(0), T(1));
        }

        template<typename T>
        inline Matrix<4, 4, T> rotateZ(T angle)
        {
            const T a = std::cos(deg2rad(-angle));
            const T b = std::sin(deg2rad(-angle));
            return Matrix<4, 4, T>(
                a,      -b, T(0), T(0),
                b,       a, T(0), T(0),
                T(0), T(0), T(1), T(0),
                T(0), T(0), T(0), T(1));
        }

        template<typename T>
        constexpr Matrix<4, 4, T> scale(const Vector<3, T>& value)
        {
            return Matrix<4, 4, T>(
                value[0], T(0),     T(0),     T(0),
                T(0),     value[1], T(0),     T(0),
                T(0),     T(0),     value[2], T(0),
                T(0),     T(0),     T(0),     T(1));
        }

        template<typename T>
        inline Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far)
        {
            const T a = T(2) / (right - left);
            const T b = T(2) / (top - bottom);
            const T c = T(-2) / (far - near);
            const T x = -(right + left) / (right - left);
            const T y = -(top + bottom) / (top - bottom);
            const T z = -(far + near) / (far - near);
            return Matrix<4, 4, T>(
                a,    T(0), T(0), T(0),
                T(0), b,    T(0), T(0),
                T(0), T(0), c,    T(0),
                x,    y,    z,    T(1));
        }

        template<typename T>
        inline Matrix<4, 4, T> perspective(T fov, T aspect, T near, T far)
        {
            const T f = T(1) / std::tan(deg2rad(fov) / T(2));
            const T a = f / aspect;
            const T b = (far + near) / (near - far);
            const T c = T(2) * far * near / (near - far);
            return Matrix<4, 4, T>(
                   a, T(0), T(0), T( 0),
                T(0), f,    T(0), T( 0),
                T(0), T(0), b,    T(-1),
                T(0), T(0), c,    T( 0));
        }

        template<typename T>
        constexpr Matrix<4, 4, T> operator * (const Matrix<4, 4, T>& a, const Matrix<4, 4, T>& b)
        {
            Matrix<4, 4, T> out;
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    T tmp = T(0);
                    for (int k = 0; k < 4; ++k)
                    {
                        tmp += b[i * 4 + k] * a[k * 4 + j];
                    }
                    out[i * 4 + j] = tmp;
                }
            }
            return out;
        }

        template<typename T>
        inline std::ostream& operator << (std::ostream& os, const Matrix<4, 4, T>& value)
        {
            os << value[0] << ",";
            os << value[1] << ",";
            os << value[2] << ",";
            os << value[3] << "/";
            os << value[4] << ",";
            os << value[5] << ",";
            os << value[6] << ",";
            os << value[7] << "/";
            os << value[8] << ",";
            os << value[9] << ",";
            os << value[10] << ",";
            os << value[11] << "/";
            os << value[12] << ",";
            os << value[13] << ",";
            os << value[14] << ",";
            os << value[15];
            return os;
        }
    }
}
