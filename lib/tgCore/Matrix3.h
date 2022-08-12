// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Matrix.h>

#include <sstream>

namespace tg
{
    namespace math
    {
        //! 3x3 matrix.
        template<typename T>
        class Matrix<3, 3, T>
        {
        public:
            Matrix();
            Matrix(
                T e0, T e1, T e2,
                T e3, T e4, T e5,
                T e6, T e7, T e8);

            //! Get the underlying array.
            constexpr const std::array<T, 3 * 3>& getArray() const;

            //! Get a pointer to the data.
            constexpr const T* getData() const;

            constexpr T operator [] (size_t) const;
            T& operator [] (size_t);

            bool operator == (const Matrix<3, 3, T>&) const;
            bool operator != (const Matrix<3, 3, T>&) const;

        private:
            std::array<T, 3 * 3> _v;
        };

        //! 3x3 floating point matrix.
        typedef Matrix<3, 3, float> Matrix3x3f;

        //! \name Operators
        ///@{

        template<typename T>
        constexpr Matrix<3, 3, T> operator * (const Matrix<3, 3, T>&, const Matrix<3, 3, T>&);

        template<typename T>
        std::ostream& operator << (std::ostream&, const Matrix<3, 3, T>&);

        ///@}
    }
}

#include <tgCore/Matrix3Inline.h>
