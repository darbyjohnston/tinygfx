// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Size.h>
#include <tgCore/Vector.h>

namespace tg
{
    namespace core
    {
        // Box.
        template<int C, typename T>
        class Box
        {
        public:
            Box();
            Box(const Vector<C, T>& min, const Vector<C, T>& max);
            Box(const Vector<C, T>& min, const Size<C, T>& max);
            
            const Vector<C, T>& min() const;
            const Vector<C, T>& max() const;
            Vector<C, T>& min();
            Vector<C, T>& max();
            
            Size<C, T> size() const;
        
        private:
            Vector<C, T> _min;
            Vector<C, T> _max;
        };

        // Two-dimensional box.
        template<typename T>
        class Box<2, T>
        {
        public:
            Box();
            Box(const Vector<2, T>& min, const Vector<2, T>& max);
            Box(const Vector<2, T>& min, const Size<2, T>& max);
            Box(T x, T y, T width, T height);
            
            const Vector<2, T>& min() const;
            const Vector<2, T>& max() const;
            Vector<2, T>& min();
            Vector<2, T>& max();
            
            T x() const;
            T y() const;

            Size<2, T> size() const;
            T w() const;
            T h() const;
        
        private:
            Vector<2, T> _min;
            Vector<2, T> _max;
        };

        // Three-dimensional box.
        template<typename T>
        class Box<3, T>
        {
        public:
            Box();
            Box(const Vector<3, T>& min, const Vector<3, T>& max);
            Box(const Vector<3, T>& min, const Size<3, T>& max);
            Box(T x, T y, T z, T width, T height, T depth);
            
            const Vector<3, T>& min() const;
            const Vector<3, T>& max() const;
            Vector<3, T>& min();
            Vector<3, T>& max();
            
            T x() const;
            T y() const;
            T z() const;

            Size<3, T> size() const;
            T w() const;
            T h() const;
            T d() const;
        
        private:
            Vector<3, T> _min;
            Vector<3, T> _max;
        };

        //! \name Box Functions
        ///@{

        template<int C, typename T>
        Vector<C, T> center(const Box<C, T>&);

        template<typename T>
        T area(const Box<2, T>&);

        template<typename T>
        T volume(const Box<3, T>&);

        template<typename T>
        bool contains(const Box<2, T>&, const Box<2, T>&);
        template<typename T>
        bool contains(const Box<2, T>&, const Vector<2, T>&);

        template<typename T>
        bool intersects(const Box<2, T>&, const Box<2, T>&);
        template<typename T>
        Box<2, T> intersect(const Box<2, T>&, const Box<2, T>&);

        template<typename T>
        Box<2, T> expand(const Box<2, T>&, const Box<2, T>&);
        template<typename T>
        Box<2, T> expand(const Box<2, T>&, const Vector<2, T>&);

        template<typename T>
        Box<2, T> margin(const Box<2, T>&, const Vector<2, T>&);
        template<typename T>
        Box<2, T> margin(const Box<2, T>&, T);
        template<typename T>
        Box<2, T> margin(const Box<2, T>&, T x0, T y0, T x1, T y1);

        ///@}

        //! \name Box Operators
        ///@{
        
        //! Box comparison.
        template<int C, typename T>
        bool operator == (const Box<C, T>&, const Box<C, T>&);
        
        //! Box comparison.
        template<int C, typename T>
        bool operator != (const Box<C, T>&, const Box<C, T>&);
        
        ///@}

        //! \name Box Types
        ///@{
        
        typedef Box<2, int> Box2I;
        typedef Box<2, float> Box2F;
        typedef Box<3, float> Box3F;
        
        ///@}

        //! \name Box Serialize
        ///@{

        template<int C, typename T>
        std::ostream& operator << (std::ostream&, const Box<C, T>&);

        template<int C, typename T>
        std::istream& operator >> (std::istream&, Box<C, T>&);

        ///@}
    }
}

#include <tgCore/BoxInline.h>

