// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <array>

namespace tg
{
    namespace math
    {
        //! Matrix template.
        template<size_t R, size_t C, typename T>
        class Matrix
        {
        public:
            Matrix();

            //! Get the underlying array.
            constexpr const std::array<T, R * C>& getArray() const;

            //! Get a pointer to the data.
            constexpr const T* getData() const;

            constexpr T operator [] (size_t) const;
            T& operator [] (size_t);

            bool operator == (const Matrix<R, C, T>&) const;
            bool operator != (const Matrix<R, C, T>&) const;

        private:
            std::array<T, R * C> _v;
        };
    }
}

#include <tgCore/MatrixInline.h>
