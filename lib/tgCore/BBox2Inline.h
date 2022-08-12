// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <algorithm>

namespace tg
{
    namespace math
    {
        template<typename T>
        constexpr BBox<2, T>::BBox() :
            _min(T(0)),
            _max(T(0))
        {}

        template<typename T>
        constexpr BBox<2, T>::BBox(const Vector<2, T>& value) :
            _min(value),
            _max(value)
        {}

        template<typename T>
        constexpr BBox<2, T>::BBox(const Vector<2, T>& min, const Vector<2, T>& max) :
            _min(min),
            _max(max)
        {}

        template<typename T>
        constexpr BBox<2, T>::BBox(T x, T y, T w, T h) :
            _min(x, y),
            _max(x + w, y + h)
        {}

        template<typename T>
        constexpr const Vector<2, T>& BBox<2, T>::getMin() const
        {
            return _min;
        }

        template<typename T>
        constexpr const Vector<2, T>& BBox<2, T>::getMax() const
        {
            return _max;
        }

        template<typename T>
        constexpr T BBox<2, T>::x() const
        {
            return _min[0];
        }

        template<typename T>
        constexpr T BBox<2, T>::y() const
        {
            return _min[1];
        }

        template<typename T>
        constexpr T BBox<2, T>::w() const
        {
            return _max[0] - _min[0];
        }

        template<typename T>
        constexpr T BBox<2, T>::h() const
        {
            return _max[1] - _min[1];
        }
        
        template<typename T>
        constexpr bool BBox<2, T>::isValid() const
        {
            return
                _min[0] < _max[0] &&
                _min[1] < _max[1];
        }

        template<typename T>
        inline bool BBox<2, T>::operator == (const BBox<2, T>& value) const
        {
            return _min == value._min && _max == value._max;
        }

        template<typename T>
        inline bool BBox<2, T>::operator != (const BBox<2, T>& value) const
        {
            return !(*this == value);
        }

        inline BBox<2, int>::BBox() :
            _min(0),
            _max(0)
        {}

        inline BBox<2, int>::BBox(const Vector<2, int>& value) :
            _min(value),
            _max(value)
        {}

        inline BBox<2, int>::BBox(const Vector<2, int>& min, const Vector<2, int>& max) :
            _min(min),
            _max(max)
        {}

        inline BBox<2, int>::BBox(int x, int y, int w, int h) :
            _min(x, y),
            _max(x + w - 1, y + h - 1)
        {}

        inline const Vector<2, int>& BBox<2, int>::getMin() const
        {
            return _min;
        }

        inline const Vector<2, int>& BBox<2, int>::getMax() const
        {
            return _max;
        }

        constexpr int BBox<2, int>::x() const
        {
            return _min[0];
        }

        constexpr int BBox<2, int>::y() const
        {
            return _min[1];
        }

        constexpr int BBox<2, int>::w() const
        {
            return _max[0] - _min[0] + 1;
        }

        constexpr int BBox<2, int>::h() const
        {
            return _max[1] - _min[1] + 1;
        }

        constexpr bool BBox<2, int>::isValid() const
        {
            return
                _min[0] < _max[0] &&
                _min[1] < _max[1];
        }

        inline bool BBox<2, int>::operator == (const BBox<2, int>&value) const
        {
            return _min == value._min && _max == value._max;
        }

        inline bool BBox<2, int>::operator != (const BBox<2, int>&value) const
        {
            return !(*this == value);
        }

        inline Vector<2, int> getSize(const BBox<2, int>& value)
        {
            return value.getMax() - value.getMin() + 1;
        }

        inline Vector<2, int> getCenter(const BBox<2, int>& value)
        {
            return value.getMin() + (value.getMax() - value.getMin() + 1) / 2;
        }

        inline float getArea(const BBox<2, int>& value)
        {
            return value.w() * value.h();
        }

        inline float getArea(const BBox<2, float>& value)
        {
            return value.w() * value.h();
        }

        inline float getAspect(const BBox<2, int>& value)
        {
            const float h = value.h();
            return h != 0.F ? (value.w() / h) : 1.F;
        }

        inline float getAspect(const BBox<2, float>& value)
        {
            const float h = value.h();
            return h != 0.F ? (value.w() / h) : 1.F;
        }

        template<typename T>
        inline BBox<2, T> margin(const BBox<2, T>& bbox, const Vector<2, T>& value)
        {
            return BBox<2, T>(bbox.getMin() - value, bbox.getMax() + value);
        }

        template<typename T>
        inline BBox<2, T> margin(const BBox<2, T>& bbox, T value)
        {
            return BBox<2, T>(bbox.getMin() - value, bbox.getMax() + value);
        }

        template<typename T>
        inline BBox<2, T> margin(const BBox<2, T>& bbox, T x0, T y0, T x1, T y1)
        {
            return BBox<2, T>(
                bbox.getMin() - Vector<2, T>(x0, y0),
                bbox.getMax() + Vector<2, T>(x1, y1));
        }
    }
}
