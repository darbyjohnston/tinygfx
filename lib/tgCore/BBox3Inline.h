// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <algorithm>

namespace tg
{
    namespace math
    {
        template<typename T>
        constexpr BBox<3, T>::BBox() :
            _min(T(0)),
            _max(T(0))
        {}

        template<typename T>
        constexpr BBox<3, T>::BBox(const Vector<3, T>& value) :
            _min(value),
            _max(value)
        {}

        template<typename T>
        constexpr BBox<3, T>::BBox(const Vector<3, T>& min, const Vector<3, T>& max) :
            _min(min),
            _max(max)
        {}

        template<typename T>
        constexpr BBox<3, T>::BBox(T x, T y, T z, T w, T h, T d) :
            _min(x, y, z),
            _max(x + w, y + h, z + d)
        {}

        template<typename T>
        constexpr const Vector<3, T>& BBox<3, T>::getMin() const
        {
            return _min;
        }

        template<typename T>
        constexpr const Vector<3, T>& BBox<3, T>::getMax() const
        {
            return _max;
        }

        template<typename T>
        constexpr T BBox<3, T>::x() const
        {
            return _min[0];
        }

        template<typename T>
        constexpr T BBox<3, T>::y() const
        {
            return _min[1];
        }

        template<typename T>
        constexpr T BBox<3, T>::z() const
        {
            return _min[2];
        }

        template<typename T>
        constexpr T BBox<3, T>::w() const
        {
            return _max[0] - _min[0];
        }

        template<typename T>
        constexpr T BBox<3, T>::h() const
        {
            return _max[1] - _min[1];
        }

        template<typename T>
        constexpr T BBox<3, T>::d() const
        {
            return _max[2] - _min[2];
        }

        template<typename T>
        constexpr bool BBox<3, T>::isValid() const
        {
            return
                _min[0] < _max[0] &&
                _min[1] < _max[1];
        }

        template<typename T>
        inline bool BBox<3, T>::operator == (const BBox<3, T>& value) const
        {
            return _min == value._min && _max == value._max;
        }

        template<typename T>
        inline bool BBox<3, T>::operator != (const BBox<3, T>& value) const
        {
            return !(*this == value);
        }

        inline float getVolume(const BBox<3, float>& value)
        {
            return value.w() * value.h() * value.d();
        }
    }
}
