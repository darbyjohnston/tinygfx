// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace math
    {
        template<typename T>
        constexpr Vector2<T>::Vector2() noexcept
        {}

        template<typename T>
        constexpr Vector2<T>::Vector2(T x, T y) noexcept :
            x(x),
            y(y)
        {}

        template<typename T>
        constexpr bool Vector2<T>::operator == (const Vector2<T>& that) const
        {
            return x == that.x && y == that.y;
        }

        template<typename T>
        constexpr bool Vector2<T>::operator != (const Vector2<T>& that) const
        {
            return !(*this == that);
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator += (const Vector2<T>& that)
        {
            x += that.x;
            y += that.y;
            return *this;
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator -= (const Vector2<T>& that)
        {
            x -= that.x;
            y -= that.y;
            return *this;
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator *= (const Vector2<T>& that)
        {
            x *= that.x;
            y *= that.y;
            return *this;
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator /= (const Vector2<T>& that)
        {
            x /= that.x;
            y /= that.y;
            return *this;
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator += (T that)
        {
            x += that;
            y += that;
            return *this;
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator -= (T that)
        {
            x -= that;
            y -= that;
            return *this;
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator *= (T that)
        {
            x *= that;
            y *= that;
            return *this;
        }

        template<typename T>
        inline Vector2<T>& Vector2<T>::operator /= (T that)
        {
            x /= that;
            y /= that;
            return *this;
        }

        template<typename T>
        inline Vector2<T>::operator Vector2<float>() const
        {
            return Vector2<float>(x, y);
        }

        template<typename T>
        constexpr Vector3<T>::Vector3() noexcept
        {}

        template<typename T>
        constexpr Vector3<T>::Vector3(T x, T y, T z) noexcept :
            x(x),
            y(y),
            z(z)
        {}

        template<typename T>
        constexpr bool Vector3<T>::operator == (const Vector3<T>&that) const
        {
            return x == that.x && y == that.y && z == that.z;
        }

        template<typename T>
        constexpr bool Vector3<T>::operator != (const Vector3<T>&that) const
        {
            return !(*this == that);
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator += (const Vector3<T>& that)
        {
            x += that.x;
            y += that.y;
            z += that.z;
            return *this;
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator -= (const Vector3<T>& that)
        {
            x -= that.x;
            y -= that.y;
            z -= that.z;
            return *this;
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator *= (const Vector3<T>& that)
        {
            x *= that.x;
            y *= that.y;
            z *= that.z;
            return *this;
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator /= (const Vector3<T>& that)
        {
            x /= that.x;
            y /= that.y;
            z /= that.z;
            return *this;
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator += (T that)
        {
            x += that;
            y += that;
            z += that;
            return *this;
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator -= (T that)
        {
            x -= that;
            y -= that;
            z -= that;
            return *this;
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator *= (T that)
        {
            x *= that;
            y *= that;
            z *= that;
            return *this;
        }

        template<typename T>
        inline Vector3<T>& Vector3<T>::operator /= (T that)
        {
            x /= that;
            y /= that;
            z /= that;
            return *this;
        }

        template<typename T>
        constexpr Vector4<T>::Vector4() noexcept
        {}

        template<typename T>
        constexpr Vector4<T>::Vector4(T x, T y, T z, T w) noexcept :
            x(x),
            y(y),
            z(z),
            w(w)
        {}

        template<typename T>
        constexpr bool Vector4<T>::operator == (const Vector4<T>&that) const
        {
            return x == that.x && y == that.y && z == that.z && w == that.w;
        }

        template<typename T>
        constexpr bool Vector4<T>::operator != (const Vector4<T>&that) const
        {
            return !(*this == that);
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator += (const Vector4<T>& that)
        {
            x += that.x;
            y += that.y;
            z += that.z;
            w += that.w;
            return *this;
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator -= (const Vector4<T>& that)
        {
            x -= that.x;
            y -= that.y;
            z -= that.z;
            w -= that.w;
            return *this;
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator *= (const Vector4<T>& that)
        {
            x *= that.x;
            y *= that.y;
            z *= that.z;
            w *= that.w;
            return *this;
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator /= (const Vector4<T>& that)
        {
            x /= that.x;
            y /= that.y;
            z /= that.z;
            w /= that.w;
            return *this;
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator += (T that)
        {
            x += that;
            y += that;
            z += that;
            w += that;
            return *this;
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator -= (T that)
        {
            x -= that;
            y -= that;
            z -= that;
            w -= that;
            return *this;
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator *= (T that)
        {
            x *= that;
            y *= that;
            z *= that;
            w *= that;
            return *this;
        }

        template<typename T>
        inline Vector4<T>& Vector4<T>::operator /= (T that)
        {
            x /= that;
            y /= that;
            z /= that;
            w /= that;
            return *this;
        }

        template<typename T>
        constexpr Vector2<T> operator + (const Vector2<T>& a, const Vector2<T>& b)
        {
            return Vector2<T>(a.x + b.x, a.y + b.y);
        }

        template<typename T>
        constexpr Vector2<T> operator - (const Vector2<T>& a, const Vector2<T>& b)
        {
            return Vector2<T>(a.x - b.x, a.y - b.y);
        }

        template<typename T>
        constexpr Vector2<T> operator * (const Vector2<T>& a, const Vector2<T>& b)
        {
            return Vector2<T>(a.x * b.x, a.y * b.y);
        }

        template<typename T>
        constexpr Vector2<T> operator / (const Vector2<T>& a, const Vector2<T>& b)
        {
            return Vector2<T>(a.x / b.x, a.y / b.y);
        }

        template<typename T>
        constexpr Vector2<T> operator + (const Vector2<T>& a, T b)
        {
            return Vector2<T>(a.x + b, a.y + b);
        }

        template<typename T>
        constexpr Vector2<T> operator - (const Vector2<T>& a, T b)
        {
            return Vector2<T>(a.x - b, a.y - b);
        }

        template<typename T>
        constexpr Vector2<T> operator * (const Vector2<T>& a, T b)
        {
            return Vector2<T>(a.x * b, a.y * b);
        }

        template<typename T>
        constexpr Vector2<T> operator / (const Vector2<T>& a, T b)
        {
            return Vector2<T>(a.x / b, a.y / b);
        }

        template<typename T>
        constexpr Vector3<T> operator + (const Vector3<T>& a, const Vector3<T>& b)
        {
            return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        template<typename T>
        constexpr Vector3<T> operator - (const Vector3<T>& a, const Vector3<T>& b)
        {
            return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        template<typename T>
        constexpr Vector3<T> operator * (const Vector3<T>& a, const Vector3<T>& b)
        {
            return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        template<typename T>
        constexpr Vector3<T> operator / (const Vector3<T>& a, const Vector3<T>& b)
        {
            return Vector3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
        }

        template<typename T>
        constexpr Vector3<T> operator + (const Vector3<T>& a, T b)
        {
            return Vector3<T>(a.x + b, a.y + b, a.z + b);
        }

        template<typename T>
        constexpr Vector3<T> operator - (const Vector3<T>& a, T b)
        {
            return Vector3<T>(a.x - b, a.y - b, a.z - b);
        }

        template<typename T>
        constexpr Vector3<T> operator * (const Vector3<T>& a, T b)
        {
            return Vector3<T>(a.x * b, a.y * b, a.z * b);
        }

        template<typename T>
        constexpr Vector3<T> operator / (const Vector3<T>& a, T b)
        {
            return Vector3<T>(a.x / b, a.y / b, a.z / b);
        }

        template<typename T>
        constexpr Vector4<T> operator + (const Vector4<T>& a, const Vector4<T>& b)
        {
            return Vector4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
        }

        template<typename T>
        constexpr Vector4<T> operator - (const Vector4<T>& a, const Vector4<T>& b)
        {
            return Vector4<T>(a.x + b.x, a.y - b.y, a.z - b.z, a.w - b.w);
        }

        template<typename T>
        constexpr Vector4<T> operator * (const Vector4<T>& a, const Vector4<T>& b)
        {
            return Vector4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
        }

        template<typename T>
        constexpr Vector4<T> operator / (const Vector4<T>& a, const Vector4<T>& b)
        {
            return Vector4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
        }

        template<typename T>
        constexpr Vector4<T> operator + (const Vector4<T>& a, T b)
        {
            return Vector4<T>(a.x + b, a.y + b, a.z + b, a.w + b);
        }

        template<typename T>
        constexpr Vector4<T> operator - (const Vector4<T>& a, T b)
        {
            return Vector4<T>(a.x + b, a.y - b, a.z - b, a.w - b);
        }

        template<typename T>
        constexpr Vector4<T> operator * (const Vector4<T>& a, T b)
        {
            return Vector4<T>(a.x * b, a.y * b, a.z * b, a.w * b);
        }

        template<typename T>
        constexpr Vector4<T> operator / (const Vector4<T>& a, T b)
        {
            return Vector4<T>(a.x / b, a.y / b, a.z / b, a.w / b);
        }
    }
}
