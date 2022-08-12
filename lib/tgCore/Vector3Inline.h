// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <cmath>
#include <numeric>

namespace tg
{
    namespace math
    {
        template<typename T>
        constexpr Vector<3, T>::Vector()
        {}

        template<typename T>
        constexpr Vector<3, T>::Vector(T v) :
            _v({ v, v, v })
        {}

        template<typename T>
        constexpr Vector<3, T>::Vector(T x, T y, T z) :
            _v({ x, y, z })
        {}

        template<typename T>
        constexpr T Vector<3, T>::x() const
        {
            return _v[0];
        }

        template<typename T>
        constexpr T Vector<3, T>::y() const
        {
            return _v[1];
        }

        template<typename T>
        constexpr T Vector<3, T>::z() const
        {
            return _v[2];
        }

        template<typename T>
        inline void Vector<3, T>::setX(T value)
        {
            _v[0] = value;
        }

        template<typename T>
        inline void Vector<3, T>::setY(T value)
        {
            _v[1] = value;
        }

        template<typename T>
        inline void Vector<3, T>::setZ(T value)
        {
            _v[2] = value;
        }

        template<typename T>
        constexpr const std::array<T, 3>& Vector<3, T>::getArray() const
        {
            return _v;
        }

        template<typename T>
        constexpr const T* Vector<3, T>::getData() const
        {
            return _v.data();
        }

        template<typename T>
        inline T& Vector<3, T>::operator [] (size_t index)
        {
            return _v[index];
        }

        template<typename T>
        constexpr T Vector<3, T>::operator [] (size_t index) const
        {
            return _v[index];
        }

        template<typename T>
        bool Vector<3, T>::operator == (const Vector<3, T>& other) const
        {
            return _v == other._v;
        }

        template<typename T>
        bool Vector<3, T>::operator != (const Vector<3, T>& other) const
        {
            return _v != other._v;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator += (const Vector<3, T>& value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] += value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator -= (const Vector<3, T>& value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] -= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator *= (const Vector<3, T>& value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] *= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator /= (const Vector<3, T>& value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] /= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator += (T value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] += value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator -= (T value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] -= value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator *= (T value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] *= value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator /= (T value)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                _v[i] /= value;
            }
            return *this;
        }

        template<typename T>
        inline T length()
        {
            T v = T(0);
            for (size_t i = 0; i < 3; ++i)
            {
                v += _v[i] * _v[i];
            }
            return std::sqrt(v);
        }

        template<typename T>
        inline Vector<3, T> normalize(const Vector<3, T>& value)
        {
            Vector<3, T> out;
            zero(out);
            const T l = length();
            if (l != T(0))
            {
                out = value;
                for (size_t i = 0; i < 3; ++i)
                {
                    out[i] /= l;
                }
            }
            return out;
        }

        template<typename T>
        inline T distance(const Vector<3, T>& a, const Vector<3, T>& b)
        {
            return length(b - a);
        }

        template<typename T>
        inline T dot(const Vector<3, T>& a, const Vector<3, T>& b)
        {
            return std::inner_product(a.getArray(), b.getArray());
        }

        template<typename T>
        inline Vector<3, T> cross(const Vector<3, T>& a, const Vector<3, T>& b)
        {
            return Vector<3, T>(
                a[1] * b[2] - a[2] * b[1],
                a[2] * b[0] - a[0] * b[2],
                a[0] * b[1] - a[1] * b[0]);
        }
    }
}
