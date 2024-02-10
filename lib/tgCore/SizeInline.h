// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        template<int C, typename T>
        inline Size<C, T>::Size()
        {
            for (int c = 0; c < C; ++c)
            {
                e[c] = T(0);
            }
        }

        template<int C, typename T>
        constexpr T Size<C, T>::operator [] (int c) const
        {
            return e[c];
        }

        template<int C, typename T>
        constexpr T& Size<C, T>::operator [] (int c)
        {
            return e[c];
        }

        template<int C, typename T>
        constexpr const T* Size<C, T>::data() const
        {
            return e.data();
        }

        template<int C, typename T>
        constexpr T* Size<C, T>::data()
        {
            return e.data();
        }

        template<int C, typename T>
        inline bool Size<C, T>::isValid() const
        {
            bool out = true;
            for (int c = 0; c < C; ++c)
            {
                out &= e[c] > 0;
            }
            return out;
        }

        template<typename T>
        constexpr Size<2, T>::Size() :
            e({ T(0), T(0) }),
            w(e[0]),
            h(e[1])
        {}

        template<typename T>
        constexpr Size<2, T>::Size(T w, T h) :
            e({ w, h }),
            w(e[0]),
            h(e[1])
        {}

        template<typename T>
        constexpr Size<2, T>::Size(const Size<2, T>& v) :
            e(v.e),
            w(e[0]),
            h(e[1])
        {}

        template<typename T>
        constexpr T Size<2, T>::operator [] (int c) const
        {
            return e[c];
        }

        template<typename T>
        constexpr T& Size<2, T>::operator [] (int c)
        {
            return e[c];
        }

        template<typename T>
        constexpr const T* Size<2, T>::data() const
        {
            return e.data();
        }

        template<typename T>
        constexpr T* Size<2, T>::data()
        {
            return e.data();
        }

        template<typename T>
        constexpr bool Size<2, T>::isValid() const
        {
            return e[0] > 0 && e[1] > 0;
        }

        template<typename T>
        constexpr Size<2, T>& Size<2, T>::operator = (const Size<2, T>& v)
        {
            e = v.e;
            return *this;
        }

        template<typename T>
        constexpr Size<3, T>::Size() :
            e({ T(0), T(0), T(0) }),
            w(e[0]),
            h(e[1]),
            d(e[2])
        {}

        template<typename T>
        constexpr Size<3, T>::Size(T w, T h, T d) :
            e({ w, h, d }),
            w(e[0]),
            h(e[1]),
            d(e[2])
        {}

        template<typename T>
        constexpr Size<3, T>::Size(const Size<3, T>& v) :
            e(v.e),
            w(e[0]),
            h(e[1]),
            d(e[2])
        {}

        template<typename T>
        constexpr T Size<3, T>::operator [] (int c) const
        {
            return e[c];
        }

        template<typename T>
        constexpr T& Size<3, T>::operator [] (int c)
        {
            return e[c];
        }

        template<typename T>
        constexpr const T* Size<3, T>::data() const
        {
            return e.data();
        }

        template<typename T>
        constexpr T* Size<3, T>::data()
        {
            return e.data();
        }
        
        template<typename T>
        constexpr bool Size<3, T>::isValid() const
        {
            return e[0] > 0 && e[1] > 0 && e[2] > 0;
        }

        template<typename T>
        constexpr Size<3, T>& Size<3, T>::operator = (const Size<3, T>& v)
        {
            e = v.e;
            return *this;
        }

        template<typename T>
        constexpr T aspectRatio(const Size<2, T>& a)
        {
            return a.h > T(0) ? (a.w / a.h) : T(0);
        }

        constexpr float aspectRatio(const Size<2, int>& a)
        {
            return a.h > 0 ? (a.w / static_cast<float>(a.h)) : 0.F;
        }
        
        template<typename T>
        constexpr T area(const Size<2, T>& a)
        {
            return a.w * a.h;
        }
        
        template<typename T>
        constexpr T volume(const Size<3, T>& a)
        {
            return a.w * a.h * a.d;
        }

        template<int C, typename T>
        inline Size<C, T> operator + (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int c = 0; c < C; ++c)
            {
                out[c] = a[c] + b;
            }
            return out;
        }
        
        template<int C, typename T>
        inline Size<C, T> operator - (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int c = 0; c < C; ++c)
            {
                out[c] = a[c] - b;
            }
            return out;
        }
        
        template<int C, typename T>
        inline Size<C, T> operator * (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int c = 0; c < C; ++c)
            {
                out[c] = a[c] * b;
            }
            return out;
        }
        
        template<int C, typename T>
        inline Size<C, T> operator / (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int c = 0; c < C; ++c)
            {
                out[c] = a[c] / b;
            }
            return out;
        }

        template<int C, typename T>
        inline bool operator == (const Size<C, T>& a, const Size<C, T>& b)
        {
            bool out = true;
            for (int c = 0; c < C; ++c)
            {
                out &= a[c] == b[c];
            }
            return out;
        }
        
        template<int C, typename T>
        inline bool operator != (const Size<C, T>& a, const Size<C, T>& b)
        {
            return !(a == b);
        }
        
        template<int C, typename T>
        inline std::ostream& operator << (std::ostream& os, const Size<C, T>& v)
        {
            int c = 0;
            for (; c < C - 1; ++c)
            {
                os << v[c] << " ";
            }
            os << v[c];
            return os;
        }
        
        template<int C, typename T>
        inline std::istream& operator >> (std::istream& is, Size<C, T>& v)
        {
            for (int c = 0; c < C; ++c)
            {
                is >> v[c];
            }
            return is;
        }
    }
}

