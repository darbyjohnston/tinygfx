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
        inline Matrix<3, 3, T>::Matrix()
        {
            _v[0] = T(1); _v[1] = T(0); _v[2] = T(0);
            _v[3] = T(0); _v[4] = T(1); _v[5] = T(0);
            _v[6] = T(0); _v[7] = T(0); _v[8] = T(1);
        }

        template<typename T>
        inline Matrix<3, 3, T>::Matrix(
            T e0, T e1, T e2,
            T e3, T e4, T e5,
            T e6, T e7, T e8)
        {
            _v[0] = e0; _v[1] = e1; _v[2] = e2;
            _v[3] = e3; _v[4] = e4; _v[5] = e5;
            _v[6] = e6; _v[7] = e7; _v[8] = e8;
        }

        template<typename T>
        constexpr const std::array<T, 3 * 3>& Matrix<3, 3, T>::getArray() const
        {
            return _v;
        }

        template<typename T>
        constexpr const T* Matrix<3, 3, T>::getData() const
        {
            return _v.data();
        }

        template<typename T>
        inline constexpr T Matrix<3, 3, T>::operator [] (size_t index) const
        {
            return _v[index];
        }

        template<typename T>
        inline T& Matrix<3, 3, T>::operator [] (size_t index)
        {
            return _v[index];
        }

        template<typename T>
        inline bool Matrix<3, 3, T>::operator == (const Matrix<3, 3, T>& other) const
        {
            return _v == other._v;
        }

        template<typename T>
        inline bool Matrix<3, 3, T>::operator != (const Matrix<3, 3, T>& other) const
        {
            return _v != other._v;
        }

        template<typename T>
        constexpr Matrix<3, 3, T> operator * (const Matrix<3, 3, T>& a, const Matrix<3, 3, T>& b)
        {
            Matrix<3, 3, T> out;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    T tmp = T(0);
                    for (int k = 0; k < 3; ++k)
                    {
                        tmp += b[i * 3 + k] * a[k * 3 + j];
                    }
                    out[i * 3 + j] = tmp;
                }
            }
            return out;
        }

        template<typename T>
        inline std::ostream& operator << (std::ostream& os, const Matrix<3, 3, T>& value)
        {
            os << value[0] << ",";
            os << value[1] << ",";
            os << value[2] << "/";
            os << value[3] << ",";
            os << value[4] << ",";
            os << value[5] << "/";
            os << value[6] << ",";
            os << value[7] << ",";
            os << value[8];
            return os;
        }
    }
}
