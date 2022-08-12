// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <algorithm>
#include <sstream>

namespace tg
{
    namespace math
    {
        template<size_t D, typename T>
        constexpr BBox<D, T>::BBox()
        {
            zero(_min);
            zero(_max);
        }

        template<size_t D, typename T>
        constexpr BBox<D, T>::BBox(const Vector<D, T>& value) :
            _min(value),
            _max(value)
        {}

        template<size_t D, typename T>
        constexpr BBox<D, T>::BBox(const Vector<D, T>& min, const Vector<D, T>& max) :
            _min(min),
            _max(max)
        {}

        template<size_t D, typename T>
        constexpr const Vector<D, T>& BBox<D, T>::getMin() const
        {
            return _min;
        }

        template<size_t D, typename T>
        constexpr const Vector<D, T>& BBox<D, T>::getMax() const
        {
            return _max;
        }

        template<size_t D, typename T>
        constexpr bool BBox<D, T>::isValid() const
        {
            return
                _min[0] < _max[0] &&
                _min[1] < _max[1];
        }
\
        template<size_t D, typename T>
        inline bool BBox<D, T>::operator == (const BBox<D, T>& value) const
        {
            return _min == value._min && _max == value._max;
        }

        template<size_t D, typename T>
        inline bool BBox<D, T>::operator != (const BBox<D, T>& value) const
        {
            return !(*this == value);
        }

        template<size_t D, typename T>
        inline Vector<D, T> getSize(const BBox<D, T>& value)
        {
            return value.getMax() - value.getMin();
        }

        template<size_t D, typename T>
        inline Vector<D, T> getCenter(const BBox<D, T>& value)
        {
            return value.getMin() + (value.getMax() - value.getMin()) / T(2);
        }

        template<size_t D, typename T>
        inline bool contains(const BBox<D, T>& bbox, const BBox<D, T>& value)
        {
            bool out = true;
            const auto& bboxMin = bbox.getMin();
            const auto& bboxMax = bbox.getMax();
            const auto& valueMin = value.getMin();
            const auto& valueMax = value.getMax();
            for (size_t i = 0; i < D; ++i)
            {
                if (bboxMin[i] < valueMin[i] || bboxMax[i] > valueMax[i])
                {
                    out = false;
                    break;
                }
            }
            return out;
        }

        template<size_t D, typename T>
        inline bool contains(const BBox<D, T>& bbox, const Vector<D, T>& value)
        {
            bool out = true;
            const auto& min = bbox.getMin();
            const auto& max = bbox.getMax();
            for (size_t i = 0; i < D; ++i)
            {
                if (value.min < min[i] || value.max > max[i])
                {
                    out = false;
                    break;
                }
            }
            return out;
        }

        template<size_t D, typename T>
        inline bool intersects(const BBox<D, T>& bbox, const BBox<D, T>& value)
        {
            bool out = false;
            const auto& bboxMin = bbox.getMin();
            const auto& bboxMax = bbox.getMax();
            const auto& valueMin = value.getMin();
            const auto& valueMax = value.getMax();
            for (size_t i = 0; i < D; ++i)
            {
                out |= valueMax[i] < bboxMin[i];
                out |= valueMin[i] > bboxMax[i];
            }
            return !out;
        }

        template<size_t D, typename T>
        inline BBox<D, T> intersect(const BBox<D, T>& bbox, const BBox<D, T>& value)
        {
            Vector<D, T> min;
            Vector<D, T> max;
            const auto& bboxMin = bbox.getMin();
            const auto& bboxMax = bbox.getMax();
            const auto& valueMin = value.getMin();
            const auto& valueMax = value.getMax();
            for (size_t i = 0; i < D; ++i)
            {
                min[i] = std::max(bboxMin[i], valueMin[i]);
                max[i] = std::min(bboxMax[i], valueMax[i]);
            }
            return BBox<D, T>(min, max);
        }

        template<size_t D, typename T>
        inline BBox<D, T> expand(const BBox<D, T>& bbox, const BBox<D, T>& value)
        {
            Vector<D, T> min;
            Vector<D, T> max;
            const auto& bboxMin = bbox.getMin();
            const auto& bboxMax = bbox.getMax();
            const auto& valueMin = value.getMin();
            const auto& valueMax = value.getMax();
            for (size_t i = 0; i < D; ++i)
            {
                min[i] = std::min(bboxMin[i], valueMin[i]);
                max[i] = std::max(bboxMax[i], valueMax[i]);
            }
            return BBox<D, T>(min, max);
        }

        template<size_t D, typename T>
        inline BBox<D, T> expand(const BBox<D, T>& bbox, const Vector<D, T>& value)
        {
            Vector<D, T> min;
            Vector<D, T> max;
            const auto& bboxMin = bbox.getMin();
            const auto& bboxMax = bbox.getMax();
            for (size_t i = 0; i < D; ++i)
            {
                min[i] = std::min(bboxMin[i], value[i]);
                max[i] = std::max(bboxMax[i], value[i]);
            }
            return BBox<D, T>(min, max);
        }

        template<size_t D, typename T>
        inline std::ostream& operator << (std::ostream& os, const BBox<D, T>& value)
        {
            os << value.min << "-" << value.max;
            return os;
        }

        template<size_t D, typename T>
        inline std::istream& operator >> (std::istream& is, BBox<D, T>& value)
        {
            std::string s;
            is >> s;
            auto split = string::split(s, '-');
            if (split.size() != 2)
            {
                throw error::ParseError();
            }
            {
                std::stringstream ss(split[0]);
                ss >> value.min;
            }
            {
                std::stringstream ss(split[1]);
                ss >> value.max;
            }
            return is;
        }
    }
}
