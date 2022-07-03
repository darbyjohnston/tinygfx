// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

namespace tg
{
    namespace math
    {
        //! Two-dimensional bounding box.
        template<typename T>
        class BBox2
        {
        public:
            BBox2() noexcept;
            explicit BBox2(const Vector2<T>&) noexcept;
            BBox2(const Vector2<T>& min, const Vector2<T>& max) noexcept;
            BBox2(T x, T y, T w, T h) noexcept;

            //! \name Components
            ///@{

            Vector2<T> min;
            Vector2<T> max;

            T x() const noexcept;
            T y() const noexcept;
            T w() const noexcept;
            T h() const noexcept;

            constexpr bool isValid() const noexcept;

            void zero() noexcept;

            ///@}

            //! \name Dimensions
            ///@{

            Vector2<T> getSize() const noexcept;
            Vector2<T> getCenter() const noexcept;
            T getArea() const noexcept;
            float getAspect() const noexcept;

            ///@}

            //! \name Intersections
            ///@{

            bool contains(const BBox2<T>&) const noexcept;
            bool contains(const Vector2<T>&) const noexcept;

            bool intersects(const BBox2<T>&) const noexcept;
            BBox2<T> intersect(const BBox2<T>&) const;

            ///@}

            //! \name Expand
            ///@{

            void expand(const BBox2<T>&);
            void expand(const Vector2<T>&);

            ///@}

            //! \name Margin
            ///@{

            constexpr BBox2<T> margin(const Vector2<T>&) const noexcept;
            constexpr BBox2<T> margin(T) const noexcept;
            constexpr BBox2<T> margin(T x0, T y0, T x1, T y1) const noexcept;

            ///@}

            constexpr bool operator == (const BBox2<T>&) const noexcept;
            constexpr bool operator != (const BBox2<T>&) const noexcept;
        };

        //! Three-dimensional bounding box.
        template<typename T>
        class BBox3
        {
        public:
            BBox3() noexcept;
            explicit BBox3(const Vector3<T>&) noexcept;
            BBox3(const Vector3<T>& min, const Vector3<T>& max) noexcept;
            BBox3(T x, T y, T z, T w, T h, T d) noexcept;

            //! \name Components
            ///@{

            Vector3<T> min;
            Vector3<T> max;

            T x() const noexcept;
            T y() const noexcept;
            T z() const noexcept;
            T w() const noexcept;
            T h() const noexcept;
            T d() const noexcept;

            constexpr bool isValid() const noexcept;

            void zero() noexcept;

            ///@}

            //! \name Dimensions
            ///@{

            Vector3<T> getSize() const noexcept;
            Vector3<T> getCenter() const noexcept;
            T getVolume() const noexcept;

            ///@}

            //! \name Intersections
            ///@{

            bool contains(const BBox3<T>&) const noexcept;
            bool contains(const Vector3<T>&) const noexcept;

            bool intersects(const BBox3<T>&) const noexcept;
            BBox3<T> intersect(const BBox3<T>&) const;

            ///@}

            //! \name Expand
            ///@{

            void expand(const BBox3<T>&);
            void expand(const Vector3<T>&);

            ///@}

            constexpr bool operator == (const BBox3<T>&) const noexcept;
            constexpr bool operator != (const BBox3<T>&) const noexcept;
        };

        //! Two-dimensional integer bounding box.
        typedef BBox2<int> BBox2i;

        //! Two-dimensional floating point bounding box.
        typedef BBox2<float> BBox2f;

        //! Three-dimensional floating point bounding box.
        typedef BBox3<float> BBox3f;

        std::ostream& operator << (std::ostream&, const BBox2i&);
        std::ostream& operator << (std::ostream&, const BBox2f&);
        std::ostream& operator << (std::ostream&, const BBox3f&);

        std::istream& operator >> (std::istream&, BBox2i&);
        std::istream& operator >> (std::istream&, BBox2f&);
        std::istream& operator >> (std::istream&, BBox3f&);
    }
}

#include <tgCore/BBoxInline.h>
