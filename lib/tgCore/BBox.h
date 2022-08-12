// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

namespace tg
{
    namespace math
    {
        //! Bounding box template.
        template<size_t D, typename T>
        class BBox
        {
        public:
            constexpr BBox();
            constexpr BBox(const Vector<D, T>&);
            constexpr BBox(const Vector<D, T>& min, const Vector<D, T>& max);

            constexpr const Vector<D, T>& getMin() const;
            constexpr const Vector<D, T>& getMax() const;

            constexpr bool isValid() const;

            bool operator == (const BBox<D, T>&) const;
            bool operator != (const BBox<D, T>&) const;

        private:
            Vector<D, T> _min;
            Vector<D, T> _max;
        };

        //! \name Functions.
        ///@{

        template<size_t D, typename T>
        Vector<D, T> getSize(const BBox<D, T>&);

        template<size_t D, typename T>
        Vector<D, T> getCenter(const BBox<D, T>&);

        ///@}

        //! \name Intersections
        ///@{

        template<size_t D, typename T>
        bool contains(const BBox<D, T>&, const BBox<D, T>&);
        template<size_t D, typename T>
        bool contains(const BBox<D, T>&, const Vector<D, T>&);

        template<size_t D, typename T>
        bool intersects(const BBox<D, T>&, const BBox<D, T>&);
        template<size_t D, typename T>
        BBox<D, T> intersect(const BBox<D, T>&, const BBox<D, T>&);

        ///@}

        //! \name Expand
        ///@{

        template<size_t D, typename T>
        BBox<D, T> expand(const BBox<D, T>&, const BBox<D, T>&);
        template<size_t D, typename T>
        BBox<D, T> expand(const BBox<D, T>&, const Vector<D, T>&);

        ///@}

        //! \name Operators
        ///@{

        template<size_t D, typename T>
        std::ostream& operator << (std::ostream&, const BBox<D, T>&);

        template<size_t D, typename T>
        std::istream& operator >> (std::istream&, BBox<D, T>&);

        ///@}
    }
}

#include <tgCore/BBoxInline.h>
