// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/BBox.h>
#include <tgCore/Vector2.h>

namespace tg
{
    namespace math
    {
        //! Two-dimensional bounding box.
        template<typename T>
        class BBox<2, T>
        {
        public:
            constexpr BBox();
            constexpr BBox(const Vector<2, T>&);
            constexpr BBox(const Vector<2, T>& min, const Vector<2, T>& max);
            constexpr BBox(T x, T y, T w, T h);

            constexpr const Vector<2, T>& getMin() const;
            constexpr const Vector<2, T>& getMax() const;

            constexpr T x() const;
            constexpr T y() const;
            constexpr T w() const;
            constexpr T h() const;

            constexpr bool isValid() const;

            bool operator == (const BBox<2, T>&) const;
            bool operator != (const BBox<2, T>&) const;

        private:
            Vector<2, T> _min;
            Vector<2, T> _max;
        };

        //! Two-dimensional integer bounding box.
        template<>
        class BBox<2, int>
        {
        public:
            BBox();
            BBox(const Vector<2, int>&);
            BBox(const Vector<2, int>& min, const Vector<2, int>& max);
            BBox(int x, int y, int w, int h);

            const Vector<2, int>& getMin() const;
            const Vector<2, int>& getMax() const;

            constexpr int x() const;
            constexpr int y() const;
            constexpr int w() const;
            constexpr int h() const;

            constexpr bool isValid() const;

            bool operator == (const BBox<2, int>&) const;
            bool operator != (const BBox<2, int>&) const;

        private:
            Vector<2, int> _min;
            Vector<2, int> _max;
        };

        //! Two-dimensional integer bounding box.
        typedef BBox<2, int> BBox2i;

        //! Two-dimensional floating point bounding box.
        typedef BBox<2, float> BBox2f;

        //! \name Functions
        ///@{

        Vector<2, int> getSize(const BBox<2, int>&);

        Vector<2, int> getCenter(const BBox<2, int>&);

        float getArea(const BBox<2, int>&);
        float getArea(const BBox<2, float>&);

        float getAspect(const BBox<2, int>&);
        float getAspect(const BBox<2, float>&);

        ///@}

        //! \name Margins
        ///@{

        template<typename T>
        BBox<2, T> margin(const BBox<2, T>& bbox, const Vector<2, T>&);
        template<typename T>
        BBox<2, T> margin(const BBox<2, T>& bbox, T);
        template<typename T>
        BBox<2, T> margin(const BBox<2, T>& bbox, T x0, T y0, T x1, T y1);

        ///@}
    }
}

#include <tgCore/BBox2Inline.h>
