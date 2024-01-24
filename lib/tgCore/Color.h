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

        private:
            std::array<T, C> _e;
        };

        //! Luminance color.
        template<typename T>
        class Color<1, T>
        {
        public:
            Color();
            Color(T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            T l() const;
            T& l();

        private:
            std::array<T, 1> _e;
        };

        //! Luminance and alpha color.
        template<typename T>
        class Color<2, T>
        {
        public:
            Color();
            Color(T, T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            T l() const;
            T a() const;
            T& l();
            T& a();

        private:
            std::array<T, 2> _e;
        };

        //! RGB color.
        template<typename T>
        class Color<3, T>
        {
        public:
            Color();
            Color(T, T, T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            T r() const;
            T g() const;
            T b() const;
            T& r();            
            T& g();
            T& b();

        private:
            std::array<T, 3> _e;
        };

        //! RGBA color.
        template<typename T>
        class Color<4, T>
        {
        public:
            Color();
            Color(T, T, T, T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            T r() const;            
            T g() const;            
            T b() const;            
            T a() const;
            T& r();
            T& g();
            T& b();
            T& a();

        private:
            std::array<T, 4> _e;
        };

        //! \name Color Operators
        ///@{

        template<int C, typename T>
        bool operator == (const Color<C, T>&, const Color<C, T>&);
        template<int C, typename T>
        bool operator != (const Color<C, T>&, const Color<C, T>&);
        
        ///@}

        //! \name Color Types
        ///@{

        typedef Color<1, float> Color1F;
        typedef Color<2, float> Color2F;
        typedef Color<3, float> Color3F;
        typedef Color<4, float> Color4F;
        
        ///@}

        //! \name Color Serialize
        ///@{

        template<int C, typename T>
        std::ostream& operator << (std::ostream&, const Color<C, T>&);

        template<int C, typename T>
        std::istream& operator >> (std::istream&, Color<C, T>&);

        ///@}
    }
}

#include <tgCore/ColorInline.h>

