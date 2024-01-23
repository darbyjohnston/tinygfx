// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        template<int C, typename T>
        inline Box<C, T>::Box(const Vector<C, T>& min, const Vector<C, T>& max) :
            _min(min),
            _max(max)
        {}

        template<int C, typename T>
        inline Box<C, T>::Box(const Vector<C, T>& min, const Size<C, T>& size) :
            _min(min),
            _max(min + size)
        {}
        
        template<int C, typename T>
        inline const Vector<C, T>& Box<C, T>::min() const
        {
            return _min;
        }

        template<int C, typename T>
        inline const Vector<C, T>& Box<C, T>::max() const
        {
            return _max;
        }
        
        template<int C, typename T>
        inline Vector<C, T>& Box<C, T>::min()
        {
            return _min;
        }

        template<int C, typename T>
        inline Vector<C, T>& Box<C, T>::max()
        {
            return _max;
        }
                
        template<int C, typename T>
        inline Size<C, T> Box<C, T>::size() const
        {
            Size<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = _max[i] - _min[i];
            }
            return out;
        }

        template<typename T>
        inline Box<2, T>::Box(const Vector<2, T>& min, const Vector<2, T>& max) :
            _min(min),
            _max(max)
        {}

        template<typename T>
        inline Box<2, T>::Box(const Vector<2, T>& min, const Size<2, T>& size) :
            _min(min),
            _max(min + size)
        {}

        template<>
        inline Box<2, int>::Box(const Vector<2, int>& min, const Size<2, int>& size) :
            _min(min),
            _max(min + size - 1)
        {}

        template<typename T>
        inline Box<2, T>::Box(T x, T y, T width, T height) :
            _min(x, y),
            _max(x + width, y + height)
        {}

        template<>
        inline Box<2, int>::Box(int x, int y, int width, int height) :
            _min(x, y),
            _max(x + width - 1, y + height - 1)
        {}
        
        template<typename T>
        inline const Vector<2, T>& Box<2, T>::min() const
        {
            return _min;
        }

        template<typename T>
        inline const Vector<2, T>& Box<2, T>::max() const
        {
            return _max;
        }
        
        template<typename T>
        inline Vector<2, T>& Box<2, T>::min()
        {
            return _min;
        }

        template<typename T>
        inline Vector<2, T>& Box<2, T>::max()
        {
            return _max;
        }
        
        template<typename T>
        inline T Box<2, T>::x() const
        {
            return _min.x();
        }

        template<typename T>
        inline T Box<2, T>::y() const
        {
            return _min.y();
        }
        
        template<typename T>
        inline Size<2, T> Box<2, T>::size() const
        {
            return Size<2, T>(
                _max.x() - _min.x(),
                _max.y() - _min.y());
        }

        template<>
        inline Size<2, int> Box<2, int>::size() const
        {
            return Size<2, int>(
                _max.x() - _min.x() + 1,
                _max.y() - _min.y() + 1);
        }

        template<typename T>
        inline T Box<2, T>::w() const
        {
            return size().w();
        }

        template<typename T>
        inline T Box<2, T>::h() const
        {
            return size().h();
        }

        template<typename T>
        inline Box<3, T>::Box(const Vector<3, T>& min, const Vector<3, T>& max) :
            _min(min),
            _max(max)
        {}

        template<typename T>
        inline Box<3, T>::Box(const Vector<3, T>& min, const Size<3, T>& size) :
            _min(min),
            _max(min + size)
        {}

        template<typename T>
        inline Box<3, T>::Box(T x, T y, T z, T width, T height, T depth) :
            _min(x, y, z),
            _max(x + width, y + height, z + depth)
        {}
        
        template<typename T>
        inline const Vector<3, T>& Box<3, T>::min() const
        {
            return _min;
        }

        template<typename T>
        inline const Vector<3, T>& Box<3, T>::max() const
        {
            return _max;
        }
        
        template<typename T>
        inline Vector<3, T>& Box<3, T>::min()
        {
            return _min;
        }

        template<typename T>
        inline Vector<3, T>& Box<3, T>::max()
        {
            return _max;
        }
        
        template<typename T>
        inline T Box<3, T>::x() const
        {
            return _min.x();
        }

        template<typename T>
        inline T Box<3, T>::y() const
        {
            return _min.y();
        }

        template<typename T>
        inline T Box<3, T>::z() const
        {
            return _min.z();
        }
        
        template<typename T>
        inline Size<3, T> Box<3, T>::size() const
        {
            return Size<3, T>(
                _max.x() - _min.x(),
                _max.y() - _min.y(),
                _max.z() - _min.z());
        }

        template<typename T>
        inline T Box<3, T>::w() const
        {
            return size().w();
        }

        template<typename T>
        inline T Box<3, T>::h() const
        {
            return size().h();
        }

        template<typename T>
        inline T Box<3, T>::d() const
        {
            return size().d();
        }

        template<int C, typename T>
        inline Vector<C, T> center(const Box<C, T>& a)
        {
            Vector<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = (a.min()[i] + a.max()[i]) / 2;
            }
            return out;
        }

        template<typename T>
        inline T area(const Box<2, T>& a)
        {
            return core::area(a.size());
        }

        template<typename T>
        inline T volume(const Box<3, T>& a)
        {
            return core::volume(a.size());
        }

        template<>
        inline bool contains(const Box<2, int>& a, const Box<2, int>& b)
        {
            return
                b.min().x() >= a.min().x() && b.max().x() <= a.max().x() &&
                b.min().y() >= a.min().y() && b.max().y() <= a.max().y();
        }

        template<>
        inline bool contains(const Box<2, float>& a, const Box<2, float>& b)
        {
            return
                b.min().x() >= a.min().x() && b.max().x() <= a.max().x() &&
                b.min().y() >= a.min().y() && b.max().y() <= a.max().y();
        }

        template<>
        inline bool contains(const Box<2, int>& a, const Vector<2, int>& b)
        {
            return
                b.x() >= a.min().x() && b.x() < a.max().x()&&
                b.y() >= a.min().y() && b.y() < a.max().y();
        }

        template<>
        inline bool contains(const Box<2, float>& a, const Vector<2, float>& b)
        {
            return
                b.x() >= a.min().x() && b.x() <= a.max().x() &&
                b.y() >= a.min().y() && b.y() <= a.max().y();
        }

        template<>
        inline bool intersects(const Box<2, int>& a, const Box<2, int>& b)
        {
            return !(
                b.max().x() < a.min().x() ||
                b.min().x() > a.max().x() ||
                b.max().y() < a.min().y() ||
                b.min().y() > a.max().y());
        }

        template<>
        inline bool intersects(const Box<2, float>& a, const Box<2, float>& b)
        {
            return !(
                b.max().x() < a.min().x() ||
                b.min().x() > a.max().x() ||
                b.max().y() < a.min().y() ||
                b.min().y() > a.max().y());
        }

        template<typename T>
        inline Box<2, T> intersect(const Box<2, T>& a, const Box<2, T>& b)
        {
            return Box<2, T>(
                Vector<2, T>(
                    std::max(a.min().x(), b.min().x()),
                    std::max(a.min().y(), b.min().y())),
                Vector<2, T>(
                    std::min(a.max().x(), b.max().x()),
                    std::min(a.max().y(), b.max().y())));
        }

        template<typename T>
        inline Box<2, T> expand(const Box<2, T>& a, const Box<2, T>& b)
        {
            return Box<2, T>(
                Vector<2, T>(
                    std::min(a.min().x(), b.min().x()),
                    std::min(a.min().y(), b.min().y())),
                Vector<2, T>(
                    std::max(a.max().x(), b.max().x()),
                    std::max(a.max().y(), b.max().y())));
        }

        template<typename T>
        inline Box<2, T> expand(const Box<2, T>& a, const Vector<2, T>& b)
        {
            return Box<2, T>(
                Vector<2, T>(
                    std::min(a.min().x(), b.x()),
                    std::min(a.min().y(), b.y())),
                Vector<2, T>(
                    std::max(a.max().x(), b.x()),
                    std::max(a.max().y(), b.y())));
        }

        template<typename T>
        inline Box<2, T> margin(const Box<2, T>& a, const Vector<2, T>& b)
        {
            return Box<2, T>(
                Vector<2, T>(a.min().x() - b.x(), a.min().y() - b.y()),
                Vector<2, T>(a.max().x() + b.x(), a.max().y() + b.y()));
        }

        template<typename T>
        inline Box<2, T> margin(const Box<2, T>& a, T b)
        {
            return Box<2, T>(
                Vector<2, T>(a.min().x() - b, a.min().y() - b),
                Vector<2, T>(a.max().x() + b, a.max().y() + b));
        }

        template<typename T>
        inline Box<2, T> margin(const Box<2, T>& a, T x0, T y0, T x1, T y1)
        {
            return Box<2, T>(
                Vector<2, T>(a.min().x() - x0, a.min().y() - y0),
                Vector<2, T>(a.max().x() + x1, a.max().y() + y1));
        }

        template<int C, typename T>
        inline bool operator == (const Box<C, T>& a, const Box<C, T>& b)
        {
            return a.min() == b.min() && a.max() == b.max();
        }
        
        template<int C, typename T>
        inline bool operator != (const Box<C, T>& a, const Box<C, T>& b)
        {
            return !(a == b);
        }
        
        template<int C, typename T>
        inline std::ostream& operator << (std::ostream& os, const Box<C, T>& v)
        {
            os << v.min() << " " << v.max();
            return os;
        }
        
        template<int C, typename T>
        inline std::istream& operator >> (std::istream& is, Box<C, T>& v)
        {
            is >> v.min();
            is >> v.max();
            return is;
        }
    }
}

