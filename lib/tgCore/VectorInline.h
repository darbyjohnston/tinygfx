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
                e[i] = T(0);
            }
        }
        
        template<int C, typename T>
        inline Vector<C, T>::Vector(const Size<C, T>& size)
        {
            for (int i = 0; i < C; ++i)
            {
                e[i] = size[i];
            }
        }

        template<int C, typename T>
        inline T Vector<C, T>::operator [] (int i) const
        {
            return e[i];
        }

        template<int C, typename T>
        inline T& Vector<C, T>::operator [] (int i)
        {
            return e[i];
        }

        template<int C, typename T>
        inline const T* Vector<C, T>::data() const
        {
            return e.data();
        }

        template<int C, typename T>
        inline T* Vector<C, T>::data()
        {
            return e.data();
        }

        template<typename T>
        inline Vector<2, T>::Vector() :
            e({ T(0), T(0) }),
            x(e[0]),
            y(e[1])
        {}

        template<typename T>
        inline Vector<2, T>::Vector(T x, T y) :
            e({ x, y }),
            x(e[0]),
            y(e[1])
        {}

        template<typename T>
        inline Vector<2, T>::Vector(const Size<2, T>& size) :
            e({ size.w, size.h }),
            x(e[0]),
            y(e[1])
        {}

        template<typename T>
        inline Vector<2, T>::Vector(const Vector<2, T>& v) :
            e(v.e),
            x(e[0]),
            y(e[1])
        {}        

        template<typename T>
        inline T Vector<2, T>::operator [] (int i) const
        {
            return e[i];
        }

        template<typename T>
        inline T& Vector<2, T>::operator [] (int i)
        {
            return e[i];
        }

        template<typename T>
        inline const T* Vector<2, T>::data() const
        {
            return e.data();
        }

        template<typename T>
        inline T* Vector<2, T>::data()
        {
            return e.data();
        }
            
        template<typename T>
        inline Vector<2, T>& Vector<2, T>::operator = (const Vector<2, T>& v)
        {
            e = v.e;
            return *this;
        }

        template<typename T>
        inline Vector<3, T>::Vector() :
            e({ T(0), T(0), T(0) }),
            x(e[0]),
            y(e[1]),
            z(e[2])
        {}

        template<typename T>
        inline Vector<3, T>::Vector(T x, T y, T z) :
            e({ x, y, z }),
            x(e[0]),
            y(e[1]),
            z(e[2])
        {}

        template<typename T>
        inline Vector<3, T>::Vector(const Size<3, T>& size) :
            e({ size.w, size.h, size.d }),
            x(e[0]),
            y(e[1]),
            z(e[2])
        {}

        template<typename T>
        inline Vector<3, T>::Vector(const Vector<3, T>& v) :
            e(v.e),
            x(e[0]),
            y(e[1]),
            z(e[2])
        {}        

        template<typename T>
        inline T Vector<3, T>::operator [] (int i) const
        {
            return e[i];
        }

        template<typename T>
        inline T& Vector<3, T>::operator [] (int i)
        {
            return e[i];
        }

        template<typename T>
        inline const T* Vector<3, T>::data() const
        {
            return e.data();
        }

        template<typename T>
        inline T* Vector<3, T>::data()
        {
            return e.data();
        }
            
        template<typename T>
        inline Vector<3, T>& Vector<3, T>::operator = (const Vector<3, T>& v)
        {
            e = v.e;
            return *this;
        }

        template<typename T>
        inline Vector<4, T>::Vector() :
            e({ T(0), T(0), T(0), T(0) }),
            x(e[0]),
            y(e[1]),
            z(e[2]),
            w(e[3])
        {}

        template<typename T>
        inline Vector<4, T>::Vector(T x, T y, T z, T w) :
            e({ x, y, z, w }),
            x(e[0]),
            y(e[1]),
            z(e[2]),
            w(e[3])
        {}

        template<typename T>
        inline Vector<4, T>::Vector(const Vector<4, T>& v) :
            e(v.e),
            x(e[0]),
            y(e[1]),
            z(e[2]),
            w(e[3])
        {}        

        template<typename T>
        inline T Vector<4, T>::operator [] (int i) const
        {
            return e[i];
        }

        template<typename T>
        inline T& Vector<4, T>::operator [] (int i)
        {
            return e[i];
        }

        template<typename T>
        inline const T* Vector<4, T>::data() const
        {
            return e.data();
        }

        template<typename T>
        inline T* Vector<4, T>::data()
        {
            return e.data();
        }
            
        template<typename T>
        inline Vector<4, T>& Vector<4, T>::operator = (const Vector<4, T>& v)
        {
            e = v.e;
            return *this;
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

