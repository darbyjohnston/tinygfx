// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <cmath>

namespace tg
{
    namespace core
    {
        template<int C, typename T>
        inline Vector<C, T>::Vector()
        {
            for (int i = 0; i < C; ++i)
            {
                _e[i] = T(0);
            }
        }
        
        template<int C, typename T>
        inline Vector<C, T>::Vector(const Size<C, T>& size)
        {
            for (int i = 0; i < C; ++i)
            {
                _e[i] = size[i];
            }
        }

        template<int C, typename T>
        inline T Vector<C, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<int C, typename T>
        inline T& Vector<C, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<int C, typename T>
        inline const T* Vector<C, T>::data() const
        {
            return _e.data();
        }

        template<int C, typename T>
        inline T* Vector<C, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline Vector<2, T>::Vector() :
            _e({ T(0), T(0) })
        {}

        template<typename T>
        inline Vector<2, T>::Vector(T x, T y) :
            _e({ x, y })
        {}

        template<typename T>
        inline Vector<2, T>::Vector(const Size<2, T>& size) :
            _e({ size.w(), size.h() })
        {}

        template<typename T>
        inline T Vector<2, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Vector<2, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Vector<2, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Vector<2, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline T Vector<2, T>::x() const
        {
            return _e[0];
        }

        template<typename T>
        inline T Vector<2, T>::y() const
        {
            return _e[1];
        }

        template<typename T>
        inline T& Vector<2, T>::x()
        {
            return _e[0];
        }

        template<typename T>
        inline T& Vector<2, T>::y()
        {
            return _e[1];
        }

        template<typename T>
        inline Vector<3, T>::Vector() :
            _e({ T(0), T(0), T(0) })
        {}

        template<typename T>
        inline Vector<3, T>::Vector(T x, T y, T z) :
            _e({ x, y, z })
        {}

        template<typename T>
        inline Vector<3, T>::Vector(const Size<3, T>& size) :
            _e({ size.w(), size.h(), size.d() })
        {}

        template<typename T>
        inline T Vector<3, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Vector<3, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Vector<3, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Vector<3, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline T Vector<3, T>::x() const
        {
            return _e[0];
        }

        template<typename T>
        inline T Vector<3, T>::y() const
        {
            return _e[1];
        }

        template<typename T>
        inline T Vector<3, T>::z() const
        {
            return _e[2];
        }

        template<typename T>
        inline T& Vector<3, T>::x()
        {
            return _e[0];
        }

        template<typename T>
        inline T& Vector<3, T>::y()
        {
            return _e[1];
        }

        template<typename T>
        inline T& Vector<3, T>::z()
        {
            return _e[2];
        }

        template<typename T>
        inline Vector<4, T>::Vector() :
            _e({ T(0), T(0), T(0), T(0) })
        {}

        template<typename T>
        inline Vector<4, T>::Vector(T x, T y, T z, T w) :
            _e({ x, y, z, w })
        {}

        template<typename T>
        inline T Vector<4, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Vector<4, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Vector<4, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Vector<4, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline T Vector<4, T>::x() const
        {
            return _e[0];
        }

        template<typename T>
        inline T Vector<4, T>::y() const
        {
            return _e[1];
        }

        template<typename T>
        inline T Vector<4, T>::z() const
        {
            return _e[2];
        }

        template<typename T>
        inline T Vector<4, T>::w() const
        {
            return _e[3];
        }

        template<typename T>
        inline T& Vector<4, T>::x()
        {
            return _e[0];
        }

        template<typename T>
        inline T& Vector<4, T>::y()
        {
            return _e[1];
        }

        template<typename T>
        inline T& Vector<4, T>::z()
        {
            return _e[2];
        }

        template<typename T>
        inline T& Vector<4, T>::w()
        {
            return _e[3];
        }

        template<int C, typename T>
        inline T length(const Vector<C, T>& v)
        {
            T s = T(0);
            for (int i = 0; i < C; ++i)
            {
                s += v[i] * v[i];
            }
            return std::sqrt(s);
        }
        
        template<int C, typename T>
        inline Vector<C, T> normalize(const Vector<C, T>& v)
        {
            const T l = length(v);
            Vector<C, T> out = v;
            for (int i = 0; i < C; ++i)
            {
                out[i] /= l;
            }
            return out;
        }

        template<int C, typename T>
        inline T dot(const Vector<C, T>& v0, const Vector<C, T>& v1)
        {
            T out = T(0);
            for (int i = 0; i < C; ++i)
            {
                out += v0[i] * v1[i];
            }
            return out;
        }

        template<typename T>
        inline Vector<2, T> perpCW(const Vector<2, T>& v)
        {
            return Vector<2, T>(v[1], -v[0]);
        }

        template<typename T>
        inline Vector<2, T> perpCCW(const Vector<2, T>& v)
        {
            return Vector<2, T>(-v[1], v[0]);
        }

        template<int C, typename T>
        inline Vector<C, T> operator + (const Vector<C, T>& v0, const Vector<C, T>& v1)
        {
            Vector<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = v0[i] + v1[i];
            }
            return out;
        }

        template<int C, typename T>
        inline Vector<C, T> operator + (const Vector<C, T>& v, T s)
        {
            Vector<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = v[i] + s;
            }
            return out;
        }
        
        template<int C, typename T>
        inline Vector<C, T> operator - (const Vector<C, T>& v0, const Vector<C, T>& v1)
        {
            Vector<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = v0[i] - v1[i];
            }
            return out;
        }

        template<int C, typename T>
        inline Vector<C, T> operator - (const Vector<C, T>& v, T s)
        {
            Vector<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = v[i] - s;
            }
            return out;
        }

        template<int C, typename T>
        inline Vector<C, T> operator * (const Vector<C, T>& v, T s)
        {
            Vector<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = v[i] * s;
            }
            return out;
        }

        template<int C, typename T>
        inline Vector<C, T> operator / (const Vector<C, T>& v, T s)
        {
            Vector<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = v[i] / s;
            }
            return out;
        }

        template<int C, typename T>
        inline bool operator == (const Vector<C, T>& a, const Vector<C, T>& b)
        {
            bool out = true;
            for (int i = 0; i < C; ++i)
            {
                out &= a[i] == b[i];
            }
            return out;
        }
        
        template<int C, typename T>
        inline bool operator != (const Vector<C, T>& a, const Vector<C, T>& b)
        {
            return !(a == b);
        }
        
        template<int C, typename T>
        inline std::ostream& operator << (std::ostream& os, const Vector<C, T>& v)
        {
            int i = 0;
            for (; i < C - 1; ++i)
            {
                os << v[i] << " ";
            }
            os << v[i];
            return os;
        }
        
        template<int C, typename T>
        inline std::istream& operator >> (std::istream& is, Vector<C, T>& v)
        {
            for (int i = 0; i < C; ++i)
            {
                is >> v[i];
            }
            return is;
        }
    }
}

