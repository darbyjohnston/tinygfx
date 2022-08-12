// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/BBox.h>
#include <tgCore/Vector3.h>

namespace tg
{
    namespace math
    {
        //! Three-dimensional bounding box.
        template<typename T>
        class BBox<3, T>
        {
        public:
            constexpr BBox();
            constexpr BBox(const Vector<3, T>&);
            constexpr BBox(const Vector<3, T>& min, const Vector<3, T>& max);
            constexpr BBox(T x, T y, T z, T w, T h, T d);

            constexpr const Vector<3, T>& getMin() const;
            constexpr const Vector<3, T>& getMax() const;

            constexpr T x() const;
            constexpr T y() const;
            constexpr T z() const;
            constexpr T w() const;
            constexpr T h() const;
            constexpr T d() const;

            constexpr bool isValid() const;

            bool operator == (const BBox<3, T>&) const;
            bool operator != (const BBox<3, T>&) const;

        private:
            Vector<3, T> _min;
            Vector<3, T> _max;
        };

        //! Three-dimensional floating point bounding box.
        typedef BBox<3, float> BBox3f;

        //! \name Functions
        ///@{

        float getVolume(const BBox<3, float>&);

        ///@}
    }
}

#include <tgCore/BBox3Inline.h>
