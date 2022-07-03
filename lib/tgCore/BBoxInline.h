// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <algorithm>

namespace tg
{
    namespace math
    {
        template<typename T>
        inline BBox2<T>::BBox2() noexcept :
            min(T(0), T(0)),
            max(T(0), T(0))
        {}

        template<typename T>
        inline BBox2<T>::BBox2(const Vector2<T>& value) noexcept :
            min(value),
            max(value)
        {}

        template<typename T>
        inline BBox2<T>::BBox2(const Vector2<T>& min, const Vector2<T>& max) noexcept :
            min(min),
            max(max)
        {}

        template<typename T>
        inline BBox2<T>::BBox2(T x, T y, T w, T h) noexcept :
            min(x, y),
            max(x + w, y + h)
        {}

        template<>
        inline BBox2<int>::BBox2(int x, int y, int w, int h) noexcept :
            min(x, y),
            max(x + w - 1, y + h - 1)
        {}

        template<typename T>
        inline T BBox2<T>::x() const noexcept
        {
            return min.x;
        }

        template<typename T>
        inline T BBox2<T>::y() const noexcept
        {
            return min.y;
        }

        template<typename T>
        inline T BBox2<T>::w() const noexcept
        {
            return max.x - min.x;
        }

        template<>
        inline int BBox2<int>::w() const noexcept
        {
            return max.x - min.x + 1;
        }

        template<typename T>
        inline T BBox2<T>::h() const noexcept
        {
            return max.y - min.y;
        }

        template<>
        inline int BBox2<int>::h() const noexcept
        {
            return max.y - min.y + 1;
        }

        template<typename T>
        constexpr bool BBox2<T>::isValid() const noexcept
        {
            return
                min.x < max.x &&
                min.y < max.y;
        }

        template<typename T>
        inline void BBox2<T>::zero() noexcept
        {
            min.x = min.y = max.x = max.y = T(0);
        }

        template<typename T>
        inline Vector2<T> BBox2<T>::getSize() const noexcept
        {
            return Vector2<T>(max.x - min.x, max.y - min.y);
        }

        template<>
        inline Vector2<int> BBox2<int>::getSize() const noexcept
        {
            return Vector2<int>(max.x - min.x + 1, max.y - min.y + 1);
        }

        template<typename T>
        inline Vector2<T> BBox2<T>::getCenter() const noexcept
        {
            return Vector2<T>(
                min.x + (max.x - min.x) / T(2),
                min.y + (max.y - min.y) / T(2));
        }

        template<>
        inline Vector2<int> BBox2<int>::getCenter() const noexcept
        {
            return Vector2<int>(
                min.x + static_cast<int>((max.x - min.x + 1) / 2.F),
                min.y + static_cast<int>((max.y - min.y + 1) / 2.F));
        }

        template<typename T>
        inline T BBox2<T>::getArea() const noexcept
        {
            return w() * h();
        }

        template<>
        inline float BBox2<int>::getAspect() const noexcept
        {
            const int h = this->h();
            return h != 0 ? w() / static_cast<float>(h) : 0.F;
        }

        template<>
        inline float BBox2<float>::getAspect() const noexcept
        {
            const float h = this->h();
            return h != 0 ? w() / h : 0.F;
        }

        template<typename T>
        inline bool BBox2<T>::contains(const BBox2<T>& value) const noexcept
        {
            return
                value.min.x >= min.x && value.max.x <= max.x &&
                value.min.y >= min.y && value.max.y <= max.y;
        }

        template<>
        inline bool BBox2<int>::contains(const BBox2<int>& value) const noexcept
        {
            return
                value.min.x >= min.x && value.max.x <= max.x &&
                value.min.y >= min.y && value.max.y <= max.y;
        }

        template<typename T>
        inline bool BBox2<T>::contains(const Vector2<T>& value) const noexcept
        {
            return
                value.x >= min.x && value.x <= max.x &&
                value.y >= min.y && value.y <= max.y;
        }

        template<>
        inline bool BBox2<int>::contains(const Vector2<int>& value) const noexcept
        {
            return
                value.x >= min.x && value.x < max.x &&
                value.y >= min.y && value.y < max.y;
        }

        template<typename T>
        inline bool BBox2<T>::intersects(const BBox2<T>& value) const noexcept
        {
            return !(
                value.max.x < min.x ||
                value.min.x > max.x ||
                value.max.y < min.y ||
                value.min.y > max.y);
        }

        template<typename T>
        inline BBox2<T> BBox2<T>::intersect(const BBox2<T>& value) const
        {
            BBox2<T> out;
            out.min.x = std::max(min.x, value.min.x);
            out.min.y = std::max(min.y, value.min.y);
            out.max.x = std::min(max.x, value.max.x);
            out.max.y = std::min(max.y, value.max.y);
            return out;
        }

        template<typename T>
        inline void BBox2<T>::expand(const BBox2<T>& value)
        {
            min.x = std::min(min.x, value.min.x);
            min.y = std::min(min.y, value.min.y);
            max.x = std::max(max.x, value.max.x);
            max.y = std::max(max.y, value.max.y);
        }

        template<typename T>
        inline void BBox2<T>::expand(const Vector2<T>& value)
        {
            min.x = std::min(min.x, value.x);
            min.y = std::min(min.y, value.y);
            max.x = std::max(max.x, value.x);
            max.y = std::max(max.y, value.y);
        }

        template<typename T>
        constexpr BBox2<T> BBox2<T>::margin(const Vector2<T>& value) const noexcept
        {
            return BBox2<T>(
                Vector2<T>(min.x - value.x, min.y - value.y),
                Vector2<T>(max.x + value.x, max.y + value.y));
        }

        template<typename T>
        constexpr BBox2<T> BBox2<T>::margin(T value) const noexcept
        {
            return BBox2<T>(
                Vector2<T>(min.x - value, min.y - value),
                Vector2<T>(max.x + value, max.y + value));
        }

        template<typename T>
        constexpr BBox2<T> BBox2<T>::margin(T x0, T y0, T x1, T y1) const noexcept
        {
            return BBox2<T>(
                Vector2<T>(min.x - x0, min.y - y0),
                Vector2<T>(max.x + x1, max.y + y1));
        }

        template<typename T>
        constexpr bool BBox2<T>::operator == (const BBox2<T>& value) const noexcept
        {
            return min == value.min && max == value.max;
        }

        template<typename T>
        constexpr bool BBox2<T>::operator != (const BBox2<T>& value) const noexcept
        {
            return !(*this == value);
        }

        template<typename T>
        inline BBox3<T>::BBox3() noexcept :
            min(T(0), T(0), T(0)),
            max(T(0), T(0), T(0))
        {}

        template<typename T>
        inline BBox3<T>::BBox3(const Vector3<T>& value) noexcept :
            min(value),
            max(value)
        {}

        template<typename T>
        inline BBox3<T>::BBox3(const Vector3<T>& min, const Vector3<T>& max) noexcept :
            min(min),
            max(max)
        {}

        template<typename T>
        inline BBox3<T>::BBox3(T x, T y, T z, T w, T h, T d) noexcept :
            min(x, y, z),
            max(x + w, y + h, z + d)
        {}

        template<typename T>
        inline T BBox3<T>::x() const noexcept
        {
            return min.x;
        }

        template<typename T>
        inline T BBox3<T>::y() const noexcept
        {
            return min.y;
        }

        template<typename T>
        inline T BBox3<T>::z() const noexcept
        {
            return min.z;
        }

        template<typename T>
        inline T BBox3<T>::w() const noexcept
        {
            return max.x - min.x;
        }

        template<typename T>
        inline T BBox3<T>::h() const noexcept
        {
            return max.y - min.y;
        }

        template<typename T>
        inline T BBox3<T>::d() const noexcept
        {
            return max.z - min.z;
        }

        template<typename T>
        constexpr bool BBox3<T>::isValid() const noexcept
        {
            return
                min.x < max.x &&
                min.y < max.y &&
                min.z < max.z;
        }

        template<typename T>
        inline void BBox3<T>::zero() noexcept
        {
            min.x = min.y = max.x = max.y = T(0);
        }

        template<typename T>
        inline Vector3<T> BBox3<T>::getSize() const noexcept
        {
            return Vector3<T>(max.x - min.x, max.y - min.y, max.z - min.z);
        }

        template<typename T>
        inline Vector3<T> BBox3<T>::getCenter() const noexcept
        {
            return Vector3<T>(
                min.x + (max.x - min.x) / T(2),
                min.y + (max.y - min.y) / T(2),
                min.z + (max.z - min.z) / T(2));
        }

        template<typename T>
        inline T BBox3<T>::getVolume() const noexcept
        {
            return w() * h() * d();
        }

        template<typename T>
        inline bool BBox3<T>::contains(const BBox3<T>& value) const noexcept
        {
            return
                value.min.x >= min.x && value.max.x <= max.x &&
                value.min.y >= min.y && value.max.y <= max.y &&
                value.min.z >= min.z && value.max.z <= max.z;
        }

        template<typename T>
        inline bool BBox3<T>::contains(const Vector3<T>& value) const noexcept
        {
            return
                value.x >= min.x && value.x < max.x &&
                value.y >= min.y && value.y < max.y &&
                value.z >= min.z && value.z < max.z;
        }

        template<typename T>
        inline bool BBox3<T>::intersects(const BBox3<T>& value) const noexcept
        {
            return !(
                value.max.x < min.x ||
                value.min.x > max.x ||
                value.max.y < min.y ||
                value.min.y > max.y ||
                value.max.z < min.z ||
                value.min.z > max.z);
        }

        template<typename T>
        inline BBox3<T> BBox3<T>::intersect(const BBox3<T>& value) const
        {
            BBox3<T> out;
            out.min.x = std::max(min.x, value.min.x);
            out.min.y = std::max(min.y, value.min.y);
            out.min.z = std::max(min.z, value.min.z);
            out.max.x = std::min(max.x, value.max.x);
            out.max.y = std::min(max.y, value.max.y);
            out.max.z = std::min(max.z, value.max.z);
            return out;
        }

        template<typename T>
        inline void BBox3<T>::expand(const BBox3<T>& value)
        {
            min.x = std::min(min.x, value.min.x);
            min.y = std::min(min.y, value.min.y);
            min.z = std::min(min.z, value.min.z);
            max.x = std::max(max.x, value.max.x);
            max.y = std::max(max.y, value.max.y);
            max.z = std::max(max.z, value.max.z);
        }

        template<typename T>
        inline void BBox3<T>::expand(const Vector3<T>& value)
        {
            min.x = std::min(min.x, value.x);
            min.y = std::min(min.y, value.y);
            min.z = std::min(min.z, value.z);
            max.x = std::max(max.x, value.x);
            max.y = std::max(max.y, value.y);
            max.z = std::max(max.z, value.z);
        }

        template<typename T>
        constexpr bool BBox3<T>::operator == (const BBox3<T>& value) const noexcept
        {
            return min == value.min && max == value.max;
        }

        template<typename T>
        constexpr bool BBox3<T>::operator != (const BBox3<T>& value) const noexcept
        {
            return !(*this == value);
        }
    }
}
