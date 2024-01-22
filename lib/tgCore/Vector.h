// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Size.h>

#include <iostream>

namespace tg
{
    namespace core
    {
        //! Vector.
        template<int C, typename T>
        class Vector
        {
        public:
            Vector();
            
            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();

        private:
            std::array<T, C> _e;
        };

        //! Two-dimensional vector.
        template<typename T>
        class Vector<2, T>
        {
        public:
            Vector();
            Vector(T, T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();

            T x() const;
            T y() const;
            T& x();
            T& y();

        private:
            std::array<T, 2> _e;
        };

        //! Three-dimensional vector.
        template<typename T>
        class Vector<3, T>
        {
        public:
            Vector();
            Vector(T, T, T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();

            T x() const;
            T y() const;
            T z() const;
            T& x();
            T& y();
            T& z();

        private:
            std::array<T, 3> _e;
        };

        //! Four-dimensional vector.
        template<typename T>
        class Vector<4, T>
        {
        public:
            Vector();
            Vector(T, T, T, T = T(0));

            T operator [] (int) const;
            T& operator [] (int);

            const T* data() const;
            T* data();

            T x() const;
            T y() const;
            T z() const;
            T w() const;
            T& x();
            T& y();
            T& z();
            T& w();

        private:
            std::array<T, 4> _e;
        };

        //! \name Vector Functions
        ///@{
        
        //! Get the length of a vector.
        template<int C, typename T>
        T length(const Vector<C, T>&);
        
        //! Normalize the given vector.
        template<int C, typename T>
        Vector<C, T> normalize(const Vector<C, T>&);        
        
        //! Get the vector dot product.
        template<int C, typename T>
        T dot(const Vector<C, T>&, const Vector<C, T>&);
        
        //! Get a vector perpindicular to the given vector in the clockwise
        //! direction.
        template<typename T>
        Vector<2, T> perpCW(const Vector<2, T>&);

        //! Get a vector perpindicular to the given vector in the
        //! counter-clockwise direction.
        template<typename T>
        Vector<2, T> perpCCW(const Vector<2, T>&);
        
        ///@}

        //! \name Vector Operators
        ///@{

        template<int C, typename T>
        Vector<C, T> operator + (const Vector<C, T>&, const Vector<C, T>&);
        template<int C, typename T>
        Vector<C, T> operator + (const Vector<C, T>&, const Size<C, T>&);
        template<int C, typename T>
        Vector<C, T> operator + (const Vector<C, T>&, T);
        
        template<int C, typename T>
        Vector<C, T> operator - (const Vector<C, T>&, const Vector<C, T>&);
        template<int C, typename T>
        Vector<C, T> operator - (const Vector<C, T>&, T);

        template<int C, typename T>
        Vector<C, T> operator * (const Vector<C, T>&, T);
        template<int C, typename T>
        Vector<C, T> operator / (const Vector<C, T>&, T);
        
        template<int C, typename T>
        bool operator == (const Vector<C, T>&, const Vector<C, T>&);
        template<int C, typename T>
        bool operator != (const Vector<C, T>&, const Vector<C, T>&);
        
        ///@}

        //! \name Vector Types
        ///@{

        typedef Vector<2, int> V2I;
        typedef Vector<2, float> V2F;
        typedef Vector<3, float> V3F;
        typedef Vector<4, float> V4F;
        
        ///@}

        //! \name Vector Serialize
        ///@{

        template<int C, typename T>
        std::ostream& operator << (std::ostream&, const Vector<C, T>&);

        template<int C, typename T>
        std::istream& operator >> (std::istream&, Vector<C, T>&);

        ///@}
    }
}

#include <tgCore/VectorInline.h>

