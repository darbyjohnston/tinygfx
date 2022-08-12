// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <sstream>

namespace tg
{
    namespace math
    {
        template<size_t D, typename T>
        constexpr Vector<D, T>::Vector()
        {}

        template<size_t D, typename T>
        constexpr const std::array<T, D>& Vector<D, T>::getArray() const
        {
            return _v;
        }

        template<size_t D, typename T>
        constexpr const T* Vector<D, T>::getData() const
        {
            return _v.data();
        }

        template<size_t D, typename T>
        inline T& Vector<D, T>::operator [] (size_t index)
        {
            return _v[index];
        }

        template<size_t D, typename T>
        constexpr T Vector<D, T>::operator [] (size_t index) const
        {
            return _v[index];
        }

        template<size_t D, typename T>
        bool Vector<D, T>::operator == (const Vector& other) const
        {
            return _v == other._v;
        }

        template<size_t D, typename T>
        bool Vector<D, T>::operator != (const Vector& other) const
        {
            return _v != other._v;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator += (const Vector<D, T>& value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] += value._v[i];
            }
            return *this;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator -= (const Vector<D, T>& value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] -= value._v[i];
            }
            return *this;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator *= (const Vector<D, T>& value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] *= value._v[i];
            }
            return *this;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator /= (const Vector<D, T>& value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] /= value._v[i];
            }
            return *this;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator += (T value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] += value;
            }
            return *this;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator -= (T value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] -= value;
            }
            return *this;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator *= (T value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] *= value;
            }
            return *this;
        }

        template<size_t D, typename T>
        inline Vector<D, T>& Vector<D, T>::operator /= (T value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                _v[i] /= value;
            }
            return *this;
        }

        template<size_t D, typename T>
        void zero(Vector<D, T>& value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                value[i] = T(0);
            }
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator + (const Vector<D, T>& a, const Vector<D, T>& b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] + b[i];
            }
            return out;
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator - (const Vector<D, T>& a, const Vector<D, T>& b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] - b[i];
            }
            return out;
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator * (const Vector<D, T>& a, const Vector<D, T>& b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] * b[i];
            }
            return out;
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator / (const Vector<D, T>& a, const Vector<D, T>& b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] / b[i];
            }
            return out;
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator + (const Vector<D, T>& a, T b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] + b;
            }
            return out;
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator - (const Vector<D, T>& a, T b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] - b;
            }
            return out;
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator * (const Vector<D, T>& a, T b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] * b;
            }
            return out;
        }

        template<size_t D, typename T>
        constexpr Vector<D, T> operator / (const Vector<D, T>& a, T b)
        {
            Vector<D, T> out;
            for (size_t i = 0; i < D; ++i)
            {
                out[i] = a[i] / b;
            }
            return out;
        }

        template<size_t D, typename T>
        inline std::ostream& operator << (std::ostream& os, const Vector<D, T>& value)
        {
            for (size_t i = 0; i < D; ++i)
            {
                os << value[i];
                if (i < D - 1)
                {
                    os << ",";
                }
            }
            return os;
        }

        template<size_t D, typename T>
        inline std::istream& operator >> (std::istream& is, Vector<D, T>& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, ',');
            if (split.size() != D)
            {
                throw error::ParseError();
            }
            for (size_t i = 0; i < D; ++i)
            {
                std::stringstream ss(split[i]);
                ss >> value[i];
            }
            return is;
        }
    }
}
