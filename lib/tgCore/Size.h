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
        //! Size.
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

        private:
            std::array<T, C> _e;
        };

        //! Two-dimensional size.
        template<typename T>
        class Size<2, T>
        {
        public:
            Size();
            Size(T, T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            T w() const;
            T h() const;
            T& w();
            T& h();

            bool isValid() const;

        private:
            std::array<T, 2> _e;
        };

        //! Three-dimensional size.
        template<typename T>
        class Size<3, T>
        {
        public:
            Size();
            Size(T, T, T);

            T operator [] (int) const;
            T& operator [] (int);
            
            const T* data() const;
            T* data();
            
            T w() const;
            T h() const;
            T d() const;
            T& w();
            T& h();
            T& d();

            bool isValid() const;

        private:
            std::array<T, 3> _e;
        };

        //! \name Size Functions
        ///@{
        
        template<typename T>
        T aspectRatio(const Size<2, T>&);
        
        template<typename T>
        T area(const Size<2, T>&);
        
        template<typename T>
        T volume(const Size<3, T>&);

        ///@}

        //! \name Size Operators
        ///@{
        
        //! Add a size and scalar.
        template<int C, typename T>
        Size<C, T> operator + (const Size<C, T>&, T);
        
        //! Subtract a size and scalar.
        template<int C, typename T>
        Size<C, T> operator - (const Size<C, T>&, T);

        //! Size comparison.
        template<int C, typename T>
        bool operator == (const Size<C, T>&, const Size<C, T>&);
        
        //! Size comparison.
        template<int C, typename T>
        bool operator != (const Size<C, T>&, const Size<C, T>&);
        
        ///@}

        //! \name Size Types
        ///@{

        typedef Size<2, int> Size2I;
        typedef Size<2, float> Size2F;
        typedef Size<3, float> Size3F;
        
        ///@}

        //! \name Size Serialize
        ///@{

        template<int C, typename T>
        std::ostream& operator << (std::ostream&, const Size<C, T>&);

        template<int C, typename T>
        std::istream& operator >> (std::istream&, Size<C, T>&);

        ///@}
    }
}

#include <tgCore/SizeInline.h>
