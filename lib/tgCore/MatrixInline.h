// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Math.h>

#include <cmath>

namespace tg
{
    namespace math
    {
        template<typename T>
        constexpr Matrix3x3<T>::Matrix3x3() noexcept
        {
            e[0] = T(1); e[1] = T(0); e[2] = T(0);
            e[3] = T(0); e[4] = T(1); e[5] = T(0);
            e[6] = T(0); e[7] = T(0); e[8] = T(1);
        }

        template<typename T>
        constexpr Matrix3x3<T>::Matrix3x3(
            T e0, T e1, T e2,
            T e3, T e4, T e5,
            T e6, T e7, T e8) noexcept
        {
            e[0] = e0; e[1] = e1; e[2] = e2;
            e[3] = e3; e[4] = e4; e[5] = e5;
            e[6] = e6; e[7] = e7; e[8] = e8;
        }

        template<typename T>
        constexpr Matrix4x4<T>::Matrix4x4() noexcept
        {
            e[ 0] = T(1); e[ 1] = T(0); e[ 2] = T(0); e[ 3] = T(0);
            e[ 4] = T(0); e[ 5] = T(1); e[ 6] = T(0); e[ 7] = T(0);
            e[ 8] = T(0); e[ 9] = T(0); e[10] = T(1); e[11] = T(0);
            e[12] = T(0); e[13] = T(0); e[14] = T(0); e[15] = T(1);
        }

        template<typename T>
        constexpr Matrix4x4<T>::Matrix4x4(
            T e0, T e1, T e2, T e3,
            T e4, T e5, T e6, T e7,
            T e8, T e9, T e10, T e11,
            T e12, T e13, T e14, T e15) noexcept
        {
            e[ 0] =  e0; e[ 1] =  e1; e[ 2] =  e2; e[ 3] =  e3;
            e[ 4] =  e4; e[ 5] =  e5; e[ 6] =  e6; e[ 7] =  e7;
            e[ 8] =  e8; e[ 9] =  e9; e[10] = e10; e[11] = e11;
            e[12] = e12; e[13] = e13; e[14] = e14; e[15] = e15;
        }

        template<typename T>
        constexpr bool Matrix3x3<T>::operator == (const Matrix3x3<T>& other) const
        {
            return
                e[0] == other.e[0] &&
                e[1] == other.e[1] &&
                e[2] == other.e[2] &&
                e[3] == other.e[3] &&
                e[4] == other.e[4] &&
                e[5] == other.e[5] &&
                e[6] == other.e[6] &&
                e[7] == other.e[7] &&
                e[8] == other.e[8];
        }

        template<typename T>
        constexpr bool Matrix3x3<T>::operator != (const Matrix3x3<T>& other) const
        {
            return !(*this == other);
        }

        template<typename T>
        constexpr bool Matrix4x4<T>::operator == (const Matrix4x4<T>& other) const
        {
            return
                e[0] == other.e[0] &&
                e[1] == other.e[1] &&
                e[2] == other.e[2] &&
                e[3] == other.e[3] &&
                e[4] == other.e[4] &&
                e[5] == other.e[5] &&
                e[6] == other.e[6] &&
                e[7] == other.e[7] &&
                e[8] == other.e[8] &&
                e[9] == other.e[9] &&
                e[10] == other.e[10] &&
                e[11] == other.e[11] &&
                e[12] == other.e[12] &&
                e[13] == other.e[13] &&
                e[14] == other.e[14] &&
                e[15] == other.e[15];
        }

        template<typename T>
        constexpr bool Matrix4x4<T>::operator != (const Matrix4x4<T>& other) const
        {
            return !(*this == other);
        }

        template<typename T>
        constexpr Matrix4x4<T> translate(const Vector3<T>& value)
        {
            return Matrix4x4<float>(
                T(1), T(0), T(0), T(0),
                T(0), T(1), T(0), T(0),
                T(0), T(0), T(1), T(0),
                value.x, value.y, value.z, T(1));
        }

        template<>
        inline Matrix4x4<float> rotateX(float angle)
        {
            const float a = std::cosf(deg2rad(-angle));
            const float b = std::sinf(deg2rad(-angle));
            return Matrix4x4<float>(
                1.F, 0.F, 0.F, 0.F,
                0.F, a,  -b,   0.F,
                0.F, b,   a,   0.F,
                0.F, 0.F, 0.F, 1.F);
        }

        template<>
        inline Matrix4x4<float> rotateY(float angle)
        {
            const float a = std::cosf(deg2rad(-angle));
            const float b = std::sinf(deg2rad(-angle));
            return Matrix4x4<float>(
                a,   0.F, b,   0.F,
                0.F, 1.F, 0.F, 0.F,
                -b,  0.F, a,   0.F,
                0.F, 0.F, 0.F, 1.F);
        }

        template<>
        inline Matrix4x4<float> rotateZ(float angle)
        {
            const float a = std::cosf(deg2rad(-angle));
            const float b = std::sinf(deg2rad(-angle));
            return Matrix4x4<float>(
                a,  -b,   0.F, 0.F,
                b,   a,   0.F, 0.F,
                0.F, 0.F, 1.F, 0.F,
                0.F, 0.F, 0.F, 1.F);
        }

        template<typename T>
        constexpr Matrix4x4<T> scale(const Vector3<T>& value)
        {
            return Matrix4x4<float>(
                value.x, T(0),    T(0),    T(0),
                T(0),    value.y, T(0),    T(0),
                T(0),    T(0),    value.z, T(0),
                T(0),    T(0),    T(0),    T(1));
        }

        template<typename T>
        inline Matrix4x4<T> ortho(T left, T right, T bottom, T top, T near, T far)
        {
            const T a = T(2) / (right - left);
            const T b = T(2) / (top - bottom);
            const T c = T(-2) / (far - near);
            const T x = -(right + left) / (right - left);
            const T y = -(top + bottom) / (top - bottom);
            const T z = -(far + near) / (far - near);
            return Matrix4x4<T>(
                a,    T(0), T(0), T(0),
                T(0), b,    T(0), T(0),
                T(0), T(0), c,    T(0),
                x,    y,    z,    T(1));
        }

        template<>
        inline Matrix4x4<float> perspective(float fov, float aspect, float near, float far)
        {
            const float f = 1.F / std::tanf(deg2rad(fov) / 2.F);
            const float a = f / aspect;
            const float b = (far + near) / (near - far);
            const float c = 2.F * far * near / (near - far);
            return Matrix4x4<float>(
                a,   0.F, 0.F, 0.F,
                0.F, f,   0.F, 0.F,
                0.F, 0.F, b,  -1.F,
                0.F, 0.F, c,   0.F);
        }

        template<typename T>
        constexpr Matrix3x3<T> operator * (const Matrix3x3<T>& a, const Matrix3x3<T>& b)
        {
            Matrix3x3<T> out;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    T tmp = T(0);
                    for (int k = 0; k < 3; ++k)
                    {
                        tmp += b.e[i * 3 + k] * a.e[k * 3 + j];
                    }
                    out.e[i * 3 + j] = tmp;
                }
            }
            return out;
        }

        template<typename T>
        constexpr Matrix4x4<T> operator * (const Matrix4x4<T>& a, const Matrix4x4<T>& b)
        {
            Matrix4x4<T> out;
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    T tmp = T(0);
                    for (int k = 0; k < 4; ++k)
                    {
                        tmp += b.e[i * 4 + k] * a.e[k * 4 + j];
                    }
                    out.e[i * 4 + j] = tmp;
                }
            }
            return out;
        }
    }
}
