// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <array>
#include <iostream>

namespace tg
{
    namespace core
    {
        //! \name Sizes
        ///@{
        
        //! Base class for sizes.
        template<int C, typename T>
        class Size
        {
        public:
            Size();

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            bool isValid() const;

            std::array<T, C> e;
        };

        //! Two-dimensional size.
        template<typename T>
        class Size<2, T>
        {
        public:
            Size();
            Size(T, T);
            Size(const Size<2, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            std::array<T, 2> e;
            T& w;
            T& h;

            bool isValid() const;

            Size<2, T>& operator = (const Size<2, T>&);
        };

        //! Three-dimensional size.
        template<typename T>
        class Size<3, T>
        {
        public:
            Size();
            Size(T, T, T);
            Size(const Size<3, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            std::array<T, 3> e;
            T& w;
            T& h;
            T& d;

            bool isValid() const;

            Size<3, T>& operator = (const Size<3, T>&);
        };

        typedef Size<2, int> Size2I;
        typedef Size<2, float> Size2F;
        typedef Size<3, float> Size3F;

        //! Get the aspect ratio of the given size.
        template<typename T>
        T aspectRatio(const Size<2, T>&);
        
        //! Get the area of the given size.
        template<typename T>
        T area(const Size<2, T>&);
        
        //! Get the volume of the given size.
        template<typename T>
        T volume(const Size<3, T>&);
        
        template<int C, typename T>
        Size<C, T> operator + (const Size<C, T>&, T);
        template<int C, typename T>
        Size<C, T> operator - (const Size<C, T>&, T);
        template<int C, typename T>
        Size<C, T> operator * (const Size<C, T>&, T);
        template<int C, typename T>
        Size<C, T> operator / (const Size<C, T>&, T);
        
        template<int C, typename T>
        bool operator == (const Size<C, T>&, const Size<C, T>&);
        template<int C, typename T>
        bool operator != (const Size<C, T>&, const Size<C, T>&);
        
        template<int C, typename T>
        std::ostream& operator << (std::ostream&, const Size<C, T>&);
        template<int C, typename T>
        std::istream& operator >> (std::istream&, Size<C, T>&);

        ///@}
    }
}

#include <tgCore/SizeInline.h>

