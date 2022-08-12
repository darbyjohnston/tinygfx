// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

namespace tg
{
    namespace math
    {
        //! Four-dimensional vector.
        template<typename T>
        class Vector<4, T>
        {
        public:
            constexpr Vector();
            constexpr Vector(T);
            constexpr Vector(T, T, T, T);

            //! \name Components
            ///@{

            constexpr T x() const;
            constexpr T y() const;
            constexpr T z() const;
            constexpr T w() const;

            void setX(T);
            void setY(T);
            void setZ(T);
            void setW(T);

            constexpr const std::array<T, 4>& getArray() const;

            constexpr const T* getData() const;

            ///@}

            //! \name Operators
            ///@{

            constexpr T operator [] (size_t) const;
            T& operator [] (size_t);

            bool operator == (const Vector<4, T>&) const;
            bool operator != (const Vector<4, T>&) const;

            Vector<4, T>& operator += (const Vector<4, T>&);
            Vector<4, T>& operator -= (const Vector<4, T>&);
            Vector<4, T>& operator *= (const Vector<4, T>&);
            Vector<4, T>& operator /= (const Vector<4, T>&);

            Vector<4, T>& operator += (T);
            Vector<4, T>& operator -= (T);
            Vector<4, T>& operator *= (T);
            Vector<4, T>& operator /= (T);

            ///@}

        private:
            std::array<T, 4> _v;
        };

        //! Four-dimensional floating point vector.
        typedef Vector<4, float> Vector4f;
    }
}

#include <tgCore/Vector4Inline.h>