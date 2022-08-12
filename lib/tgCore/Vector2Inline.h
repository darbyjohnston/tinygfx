// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <cmath>

namespace tg
{
    namespace math
    {
        template<typename T>
        constexpr Vector<2, T>::Vector()
        {}

        template<typename T>
        constexpr Vector<2, T>::Vector(T v) :
            _v({ v, v })
        {}

        template<typename T>
        constexpr Vector<2, T>::Vector(T x, T y) :
            _v({ x, y })
        {}

        template<typename T>
        constexpr T Vector<2, T>::x() const
        {
            return _v[0];
        }

        template<typename T>
        constexpr T Vector<2, T>::y() const
        {
            return _v[1];
        }

        template<typename T>
        inline void Vector<2, T>::setX(T value)
        {
            _v[0] = value;
        }

        template<typename T>
        inline void Vector<2, T>::setY(T value)
        {
            _v[1] = value;
        }

        template<typename T>
        constexpr const std::array<T, 2>& Vector<2, T>::getArray() const
        {
            return _v;
        }

        template<typename T>
        constexpr const T* Vector<2, T>::getData() const
        {
            return _v.data();
        }

        template<typename T>
        inline T& Vector<2, T>::operator [] (size_t index)
        {
            return _v[index];
        }

        template<typename T>
        constexpr T Vector<2, T>::operator [] (size_t index) const
        {
            return _v[index];
        }

        template<typename T>
        bool Vector<2, T>::operator == (const Vector<2, T>& other) const
        {
            return _v == other._v;
        }

        template<typename T>
        bool Vector<2, T>::operator != (const Vector<2, T>& other) const
        {
            return _v != other._v;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator += (const Vector<2, T>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] += value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator -= (const Vector<2, T>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] -= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator *= (const Vector<2, T>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] *= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator /= (const Vector<2, T>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] /= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator += (T value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] += value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator -= (T value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] -= value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator *= (T value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] *= value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator /= (T value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] /= value;
            }
            return *this;
        }

        inline Vector<2, int>::Vector()
        {}

        inline Vector<2, int>::Vector(int v) :
            _v({ v, v })
        {}

        inline Vector<2, int>::Vector(int x, int y) :
            _v({ x, y })
        {}

        constexpr int Vector<2, int>::x() const
        {
            return _v[0];
        }

        constexpr int Vector<2, int>::y() const
        {
            return _v[1];
        }

        inline void Vector<2, int>::setX(int value)
        {
            _v[0] = value;
        }

        inline void Vector<2, int>::setY(int value)
        {
            _v[1] = value;
        }

        constexpr const std::array<int, 2>& Vector<2, int>::getArray() const
        {
            return _v;
        }

        constexpr const int* Vector<2, int>::getData() const
        {
            return _v.data();
        }

        constexpr int Vector<2, int>::operator [] (size_t index) const
        {
            return _v[index];
        }

        inline int& Vector<2, int>::operator [] (size_t index)
        {
            return _v[index];
        }

        inline bool Vector<2, int>::operator == (const Vector<2, int>& other) const
        {
            return _v == other._v;
        }

        inline bool Vector<2, int>::operator != (const Vector<2, int>& other) const
        {
            return _v != other._v;
        }

        inline Vector<2, int>& Vector<2, int>::operator += (const Vector<2, int>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] += value._v[i];
            }
            return *this;
        }

        inline Vector<2, int>& Vector<2, int>::operator -= (const Vector<2, int>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] -= value._v[i];
            }
            return *this;
        }

        inline Vector<2, int>& Vector<2, int>::operator *= (const Vector<2, int>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] *= value._v[i];
            }
            return *this;
        }

        inline Vector<2, int>& Vector<2, int>::operator /= (const Vector<2, int>& value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] /= value._v[i];
            }
            return *this;
        }

        inline Vector<2, int>& Vector<2, int>::operator += (int value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] += value;
            }
            return *this;
        }

        inline Vector<2, int>& Vector<2, int>::operator -= (int value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] -= value;
            }
            return *this;
        }

        inline Vector<2, int>& Vector<2, int>::operator *= (int value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] *= value;
            }
            return *this;
        }

        inline Vector<2, int>& Vector<2, int>::operator /= (int value)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                _v[i] /= value;
            }
            return *this;
        }

        template<typename T>
        inline float length(const Vector<2, T>& value)
        {
            float v = 0.F;
            for (size_t i = 0; i < 2; ++i)
            {
                v += value[i] * value[i];
            }
            return std::sqrt(v);
        }

        template<typename T>
        inline Vector<2, T> normalize(const Vector<2, T>& value)
        {
            Vector<2, T> out;
            zero(out);
            const T l = length(value);
            if (l != T(0))
            {
                out = value;
                for (size_t i = 0; i < 2; ++i)
                {
                    out[i] /= l;
                }
            }
            return out;
        }

        template<typename T>
        inline float distance(const Vector<2, T>& a, const Vector<2, T>& b)
        {
            return length(b - a);
        }
    }
}
