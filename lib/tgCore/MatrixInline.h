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
        template<size_t R, size_t C, typename T>
        inline Matrix<R, C, T>::Matrix()
        {
            for (size_t r = 0; r < R; ++r)
            {
                for (size_t c = 0; c < C; ++c)
                {
                    _v[r * C + c] = r == c ? T(1) : T(0);
                }
            }
        }

        template<size_t R, size_t C, typename T>
        constexpr const std::array<T, R* C>& Matrix<R, C, T>::getArray() const
        {
            return _v;
        }

        template<size_t R, size_t C, typename T>
        constexpr const T* Matrix<R, C, T>::getData() const
        {
            return _v.data();
        }

        template<size_t R, size_t C, typename T>
        inline constexpr T Matrix<R, C, T>::operator [] (size_t index) const
        {
            return _v[index];
        }

        template<size_t R, size_t C, typename T>
        inline T& Matrix<R, C, T>::operator [] (size_t index)
        {
            return _v[index];
        }

        template<size_t R, size_t C, typename T>
        inline bool Matrix<R, C, T>::operator == (const Matrix<R, C, T>& other) const
        {
            return _v == other._v;
        }

        template<size_t R, size_t C, typename T>
        inline bool Matrix<R, C, T>::operator != (const Matrix<R, C, T>& other) const
        {
            return _v != other._v;
        }
    }
}
