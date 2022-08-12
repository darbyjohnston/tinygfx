// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace math
    {
        template<typename T>
        constexpr Vector<4, T>::Vector()
        {}

        template<typename T>
        constexpr Vector<4, T>::Vector(T v) :
            _v({ v, v, v, v })
        {}

        template<typename T>
        constexpr Vector<4, T>::Vector(T x, T y, T z, T w) :
            _v({ x, y, z, w })
        {}

        template<typename T>
        constexpr T Vector<4, T>::x() const
        {
            return _v[0];
        }

        template<typename T>
        constexpr T Vector<4, T>::y() const
        {
            return _v[1];
        }

        template<typename T>
        constexpr T Vector<4, T>::z() const
        {
            return _v[2];
        }

        template<typename T>
        constexpr T Vector<4, T>::w() const
        {
            return _v[3];
        }

        template<typename T>
        inline void Vector<4, T>::setX(T value)
        {
            _v[0] = value;
        }

        template<typename T>
        inline void Vector<4, T>::setY(T value)
        {
            _v[1] = value;
        }

        template<typename T>
        inline void Vector<4, T>::setZ(T value)
        {
            _v[2] = value;
        }

        template<typename T>
        inline void Vector<4, T>::setW(T value)
        {
            _v[3] = value;
        }

        template<typename T>
        constexpr const std::array<T, 4>& Vector<4, T>::getArray() const
        {
            return _v;
        }

        template<typename T>
        constexpr const T* Vector<4, T>::getData() const
        {
            return _v.data();
        }

        template<typename T>
        inline T& Vector<4, T>::operator [] (size_t index)
        {
            return _v[index];
        }

        template<typename T>
        constexpr T Vector<4, T>::operator [] (size_t index) const
        {
            return _v[index];
        }

        template<typename T>
        bool Vector<4, T>::operator == (const Vector<4, T>& other) const
        {
            return _v == other._v;
        }

        template<typename T>
        bool Vector<4, T>::operator != (const Vector<4, T>& other) const
        {
            return _v != other._v;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator += (const Vector<4, T>& value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] += value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator -= (const Vector<4, T>& value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] -= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator *= (const Vector<4, T>& value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] *= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator /= (const Vector<4, T>& value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] /= value._v[i];
            }
            return *this;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator += (T value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] += value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator -= (T value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] -= value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator *= (T value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] *= value;
            }
            return *this;
        }

        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator /= (T value)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                _v[i] /= value;
            }
            return *this;
        }
    }
}
