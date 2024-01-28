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
        //! \name Boxes
        ///@{

        //! Base class for boxes.
        template<int C, typename T>
        class Box
        {
        public:
            Box() = default;
            Box(const Vector<C, T>& min, const Vector<C, T>& max);
            Box(const Vector<C, T>& min, const Size<C, T>& max);
            
            Vector<C, T> min;
            Vector<C, T> max;
            
            Size<C, T> size() const;
        };

        //! Two-dimensional box.
        template<typename T>
        class Box<2, T>
        {
        public:
            Box() = default;
            Box(const Vector<2, T>& min, const Vector<2, T>& max);
            Box(const Vector<2, T>& min, const Size<2, T>& max);
            Box(T x, T y, T width, T height);
            
            Vector<2, T> min;
            Vector<2, T> max;
            
            T x() const;
            T y() const;

            Size<2, T> size() const;
            T w() const;
            T h() const;
        };

        //! Three-dimensional box.
        template<typename T>
        class Box<3, T>
        {
        public:
            Box() = default;
            Box(const Vector<3, T>& min, const Vector<3, T>& max);
            Box(const Vector<3, T>& min, const Size<3, T>& max);
            Box(T x, T y, T z, T width, T height, T depth);
            Box(const Box<3, T>&);
            
            Vector<3, T> min;
            Vector<3, T> max;
            
            T x() const;
            T y() const;
            T z() const;

            Size<3, T> size() const;
            T w() const;
            T h() const;
            T d() const;
        };

        typedef Box<2, int> Box2I;
        typedef Box<2, float> Box2F;
        typedef Box<3, float> Box3F;

        //! Get the center of a box.
        template<int C, typename T>
        Vector<C, T> center(const Box<C, T>&);

        //! Get the area of a box.
        template<typename T>
        T area(const Box<2, T>&);

        //! Get the volume of a box.
        template<typename T>
        T volume(const Box<3, T>&);

        //! Does the box contain another box?
        template<typename T>
        bool contains(const Box<2, T>&, const Box<2, T>&);

        //! Does the box contain a vector?
        template<typename T>
        bool contains(const Box<2, T>&, const Vector<2, T>&);

        //! Does the box intersect another box?
        template<typename T>
        bool intersects(const Box<2, T>&, const Box<2, T>&);

        //! Get the intersection of the boxes.
        template<typename T>
        Box<2, T> intersect(const Box<2, T>&, const Box<2, T>&);

        //! Expand the box with the another box.
        template<typename T>
        Box<2, T> expand(const Box<2, T>&, const Box<2, T>&);

        //! Expand the box with a vector.
        template<typename T>
        Box<2, T> expand(const Box<2, T>&, const Vector<2, T>&);

        //! Add a margin to a box.
        template<typename T>
        Box<2, T> margin(const Box<2, T>&, const Vector<2, T>&);

        //! Add a margin to a box.
        template<typename T>
        Box<2, T> margin(const Box<2, T>&, T);

        //! Add a margin to a box.
        template<typename T>
        Box<2, T> margin(const Box<2, T>&, T x0, T y0, T x1, T y1);

        template<int C, typename T>
        bool operator == (const Box<C, T>&, const Box<C, T>&);
        template<int C, typename T>
        bool operator != (const Box<C, T>&, const Box<C, T>&); 

        template<int C, typename T>
        std::ostream& operator << (std::ostream&, const Box<C, T>&);
        template<int C, typename T>
        std::istream& operator >> (std::istream&, Box<C, T>&);

        ///@}
    }
}

#include <tgCore/BoxInline.h>

