// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Size.h>

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
            explicit Vector(const Size<C, T>&);
            
            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();

            std::array<T, C> e;
        };

        //! Two-dimensional vector.
        template<typename T>
        class Vector<2, T>
        {
        public:
            Vector();
            Vector(T, T);
            explicit Vector(const Size<2, T>&);
            Vector(const Vector<2, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();

            std::array<T, 2> e;
            T& x;
            T& y;
            
            Vector<2, T>& operator = (const Vector<2, T>&);
        };

        //! Three-dimensional vector.
        template<typename T>
        class Vector<3, T>
        {
        public:
            Vector();
            Vector(T, T, T);
            explicit Vector(const Size<3, T>&);
            Vector(const Vector<3, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();

            std::array<T, 3> e;
            T& x;
            T& y;
            T& z;

            Vector<3, T>& operator = (const Vector<3, T>&);
        };

        //! Four-dimensional vector.
        template<typename T>
        class Vector<4, T>
        {
        public:
            Vector();
            Vector(T, T, T, T = T(0));
            Vector(const Vector<4, T>&);

            T operator [] (int) const;
            T& operator [] (int);

            const T* data() const;
            T* data();

            std::array<T, 4> e;
            T& x;
            T& y;
            T& z;
            T& w;

            Vector<4, T>& operator = (const Vector<4, T>&);
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

