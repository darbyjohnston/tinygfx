// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

namespace tg
{
    namespace math
    {
        //! Two-dimensional vector.
        template<typename T>
        class Vector<2, T>
        {
        public:
            constexpr Vector();
            constexpr Vector(T);
            constexpr Vector(T, T);

            //! \name Components
            ///@{

            constexpr T x() const;
            constexpr T y() const;

            void setX(T);
            void setY(T);

            constexpr const std::array<T, 2>& getArray() const;

            constexpr const T* getData() const;

            ///@}

            //! \name Operators
            ///@{

            constexpr T operator [] (size_t) const;
            T& operator [] (size_t);

            bool operator == (const Vector<2, T>&) const;
            bool operator != (const Vector<2, T>&) const;

            Vector<2, T>& operator += (const Vector<2, T>&);
            Vector<2, T>& operator -= (const Vector<2, T>&);
            Vector<2, T>& operator *= (const Vector<2, T>&);
            Vector<2, T>& operator /= (const Vector<2, T>&);

            Vector<2, T>& operator += (T);
            Vector<2, T>& operator -= (T);
            Vector<2, T>& operator *= (T);
            Vector<2, T>& operator /= (T);

            ///@}

        private:
            std::array<T, 2> _v;
        };

        //! Two-dimensional integer vector.
        template<>
        class Vector<2, int>
        {
        public:
            Vector();
            Vector(int);
            Vector(int, int);

            //! \name Components
            ///@{

            constexpr int x() const;
            constexpr int y() const;

            void setX(int);
            void setY(int);

            constexpr const std::array<int, 2>& getArray() const;

            constexpr const int* getData() const;

            ///@}

            //! \name Operators
            ///@{

            constexpr int operator [] (size_t) const;
            int& operator [] (size_t);

            bool operator == (const Vector<2, int>&) const;
            bool operator != (const Vector<2, int>&) const;

            Vector<2, int>& operator += (const Vector<2, int>&);
            Vector<2, int>& operator -= (const Vector<2, int>&);
            Vector<2, int>& operator *= (const Vector<2, int>&);
            Vector<2, int>& operator /= (const Vector<2, int>&);

            Vector<2, int>& operator += (int);
            Vector<2, int>& operator -= (int);
            Vector<2, int>& operator *= (int);
            Vector<2, int>& operator /= (int);

            ///@}

        private:
            std::array<int, 2> _v;
        };

        //! Two-dimensional integer vector.
        typedef Vector<2, int> Vector2i;

        //! Two-dimensional floating point vector.
        typedef Vector<2, float> Vector2f;

        //! \name Functions
        ///@{

        //! Get the length.
        template<typename T>
        float length(const Vector<2, T>&);

        //! Normalize.
        template<typename T>
        Vector<2, T> normalize(const Vector<2, T>&);

        //! Get the distance.
        template<typename T>
        float distance(const Vector<2, T>&, const Vector<2, T>&);

        ///@}
    }
}

#include <tgCore/Vector2Inline.h>