// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

namespace tg
{
    namespace math
    {
        //! Three-dimensional vector.
        template<typename T>
        class Vector<3, T>
        {
        public:
            constexpr Vector();
            constexpr Vector(T);
            constexpr Vector(T, T, T);

            //! \name Components
            ///@{

            constexpr T x() const;
            constexpr T y() const;
            constexpr T z() const;

            void setX(T);
            void setY(T);
            void setZ(T);

            constexpr const std::array<T, 3>& getArray() const;

            constexpr const T* getData() const;

            ///@}

            //! \name Operators
            ///@{

            constexpr T operator [] (size_t) const;
            T& operator [] (size_t);

            bool operator == (const Vector<3, T>&) const;
            bool operator != (const Vector<3, T>&) const;

            Vector<3, T>& operator += (const Vector<3, T>&);
            Vector<3, T>& operator -= (const Vector<3, T>&);
            Vector<3, T>& operator *= (const Vector<3, T>&);
            Vector<3, T>& operator /= (const Vector<3, T>&);

            Vector<3, T>& operator += (T);
            Vector<3, T>& operator -= (T);
            Vector<3, T>& operator *= (T);
            Vector<3, T>& operator /= (T);

            ///@}

        private:
            std::array<T, 3> _v;
        };

        //! Three-dimensional floating point vector.
        typedef Vector<3, float> Vector3f;

        //! \name Functions
        ///@{

        //! Get the length.
        template<typename T>
        T length(const Vector<3, T>&);

        //! Normalize.
        template<typename T>
        Vector<3, T> normalize(const Vector<3, T>&);

        //! Get the distance.
        template<typename T>
        T distance(const Vector<3, T>&, const Vector<3, T>&);

        //! Get the dot product.
        template<typename T>
        T dot(const Vector<3, T>&, const Vector<3, T>&);

        //! Get the cross product.
        template<typename T>
        Vector<3, T> cross(const Vector<3, T>&, const Vector<3, T>&);

        ///@}
    }
}

#include <tgCore/Vector3Inline.h>