// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <array>
#include <iostream>

namespace tg
{
    namespace math
    {
        //! Vector template.
        template<size_t D, typename T>
        class Vector
        {
        public:
            constexpr Vector();

            //! Get the underlying array.
            constexpr const std::array<T, D>& getArray() const;

            //! Get a pointer to the data.
            constexpr const T* getData() const;

            //! \name Operators
            ///@{

            constexpr T operator [] (size_t) const;
            T& operator [] (size_t);

            bool operator == (const Vector<D, T>&) const;
            bool operator != (const Vector<D, T>&) const;

            Vector<D, T>& operator += (const Vector<D, T>&);
            Vector<D, T>& operator -= (const Vector<D, T>&);
            Vector<D, T>& operator *= (const Vector<D, T>&);
            Vector<D, T>& operator /= (const Vector<D, T>&);

            Vector<D, T>& operator += (T);
            Vector<D, T>& operator -= (T);
            Vector<D, T>& operator *= (T);
            Vector<D, T>& operator /= (T);

            ///@}

        private:
            std::array<T, D> _v;
        };

        //! \name Operators
        ///@{

        template<size_t D, typename T>
        void zero(Vector<D, T>&);

        ///@}
    
        //! \name Operators
        ///@{

        template<size_t D, typename T>
        constexpr Vector<D, T> operator + (const Vector<D, T>&, const Vector<D, T>&);
        template<size_t D, typename T>
        constexpr Vector<D, T> operator - (const Vector<D, T>&, const Vector<D, T>&);
        template<size_t D, typename T>
        constexpr Vector<D, T> operator * (const Vector<D, T>&, const Vector<D, T>&);
        template<size_t D, typename T>
        constexpr Vector<D, T> operator / (const Vector<D, T>&, const Vector<D, T>&);

        template<size_t D, typename T>
        constexpr Vector<D, T> operator + (const Vector<D, T>&, T);
        template<size_t D, typename T>
        constexpr Vector<D, T> operator - (const Vector<D, T>&, T);
        template<size_t D, typename T>
        constexpr Vector<D, T> operator * (const Vector<D, T>&, T);
        template<size_t D, typename T>
        constexpr Vector<D, T> operator / (const Vector<D, T>&, T);

        template<size_t D, typename T>
        std::ostream& operator << (std::ostream&, const Vector<D, T>&);

        template<size_t D, typename T>
        std::istream& operator >> (std::istream&, Vector<D, T>&);

        ///@}
    }
}

#include <tgCore/VectorInline.h>