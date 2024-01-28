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
        //! \name Colors
        ///@{

        //! Color.
        template<int C, typename T>
        class Color
        {
        public:
            Color();

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();

            std::array<T, C> e;
        };

        //! One channel color (luminance).
        template<typename T>
        class Color<1, T>
        {
        public:
            Color();
            explicit Color(T);
            Color(const Color<1, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            std::array<T, 1> e;
            T& l;

            Color<1, T>& operator = (const Color<1, T>&);
        };

        //! Two channel color (luminance and alpha).
        template<typename T>
        class Color<2, T>
        {
        public:
            Color();
            explicit Color(T);
            Color(T, T);
            Color(const Color<2, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            std::array<T, 2> e;
            T& l;
            T& a;

            Color<2, T>& operator = (const Color<2, T>&);
        };

        //! Three channel color (RGB).
        template<typename T>
        class Color<3, T>
        {
        public:
            Color();
            Color(T, T, T);
            Color(const Color<3, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            std::array<T, 3> e;
            T& r;
            T& g;
            T& b;

            Color<3, T>& operator = (const Color<3, T>&);
        };

        //! Four channel color (RGBA).
        template<typename T>
        class Color<4, T>
        {
        public:
            Color();
            Color(T, T, T);
            Color(T, T, T, T);
            Color(const Color<4, T>&);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            std::array<T, 4> e;
            T& r;
            T& g;
            T& b;
            T& a;

            Color<4, T>& operator = (const Color<4, T>&);
        };

        typedef Color<1, float> Color1F;
        typedef Color<2, float> Color2F;
        typedef Color<3, float> Color3F;
        typedef Color<4, float> Color4F;

        template<int C, typename T>
        bool operator == (const Color<C, T>&, const Color<C, T>&);
        template<int C, typename T>
        bool operator != (const Color<C, T>&, const Color<C, T>&);
                
        template<int C, typename T>
        std::ostream& operator << (std::ostream&, const Color<C, T>&);
        template<int C, typename T>
        std::istream& operator >> (std::istream&, Color<C, T>&);

        ///@}
    }
}

#include <tgCore/ColorInline.h>

