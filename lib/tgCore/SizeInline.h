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
            for (int i = 0; i < C; ++i)
            {
                _e[i] = T(0);
            }
        }

        template<int C, typename T>
        inline T Size<C, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<int C, typename T>
        inline T& Size<C, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<int C, typename T>
        inline const T* Size<C, T>::data() const
        {
            return _e.data();
        }

        template<int C, typename T>
        inline T* Size<C, T>::data()
        {
            return _e.data();
        }

        template<int C, typename T>
        inline bool Size<C, T>::isValid() const
        {
            bool out = true;
            for (int i = 0; i < C; ++i)
            {
                out &= _e[i] > 0;
            }
            return out;
        }

        template<typename T>
        inline Size<2, T>::Size() :
            _e({ T(0), T(0) }),
            w(_e[0]),
            h(_e[1])
        {}

        template<typename T>
        inline Size<2, T>::Size(T w, T h) :
            _e({ w, h }),
            w(_e[0]),
            h(_e[1])
        {}

        template<typename T>
        inline Size<2, T>::Size(const Size<2, T>& v) :
            _e(v._e),
            w(_e[0]),
            h(_e[1])
        {}

        template<typename T>
        inline T Size<2, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Size<2, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Size<2, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Size<2, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline bool Size<2, T>::isValid() const
        {
            return _e[0] > 0 && _e[1] > 0;
        }

        template<typename T>
        inline Size<2, T>& Size<2, T>::operator = (const Size<2, T>& v)
        {
            _e = v._e;
            return *this;
        }

        template<typename T>
        inline Size<3, T>::Size() :
            _e({ T(0), T(0), T(0) }),
            w(_e[0]),
            h(_e[1]),
            d(_e[2])
        {}

        template<typename T>
        inline Size<3, T>::Size(T w, T h, T d) :
            _e({ w, h, d }),
            w(_e[0]),
            h(_e[1]),
            d(_e[2])
        {}

        template<typename T>
        inline Size<3, T>::Size(const Size<3, T>& v) :
            _e(v._e),
            w(_e[0]),
            h(_e[1]),
            d(_e[2])
        {}

        template<typename T>
        inline T Size<3, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Size<3, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Size<3, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Size<3, T>::data()
        {
            return _e.data();
        }
        
        template<typename T>
        inline bool Size<3, T>::isValid() const
        {
            return _e[0] > 0 && _e[1] > 0 && _e[2] > 0;
        }

        template<typename T>
        inline Size<3, T>& Size<3, T>::operator = (const Size<3, T>& v)
        {
            _e = v._e;
            return *this;
        }

        template<typename T>
        inline T aspectRatio(const Size<2, T>& a)
        {
            return a.h > T(0) ? (a.w / a.h) : T(0);
        }

        inline float aspectRatio(const Size<2, int>& a)
        {
            return a.h > 0 ? (a.w / static_cast<float>(a.h)) : 0.F;
        }
        
        template<typename T>
        inline T area(const Size<2, T>& a)
        {
            return a.w * a.h;
        }
        
        template<typename T>
        inline T volume(const Size<3, T>& a)
        {
            return a.w * a.h * a.d;
        }

        template<int C, typename T>
        inline Size<C, T> operator + (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = a[i] + b;
            }
            return out;
        }
        
        template<int C, typename T>
        inline Size<C, T> operator - (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = a[i] - b;
            }
            return out;
        }
        
        template<int C, typename T>
        inline Size<C, T> operator * (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = a[i] * b;
            }
            return out;
        }
        
        template<int C, typename T>
        inline Size<C, T> operator / (const Size<C, T>& a, T b)
        {
            Size<C, T> out;
            for (int i = 0; i < C; ++i)
            {
                out[i] = a[i] / b;
            }
            return out;
        }

        template<int C, typename T>
        inline bool operator == (const Size<C, T>& a, const Size<C, T>& b)
        {
            bool out = true;
            for (int i = 0; i < C; ++i)
            {
                out &= a[i] == b[i];
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
            int i = 0;
            for (; i < C - 1; ++i)
            {
                os << v[i] << " ";
            }
            os << v[i];
            return os;
        }
        
        template<int C, typename T>
        inline std::istream& operator >> (std::istream& is, Size<C, T>& v)
        {
            for (int i = 0; i < C; ++i)
            {
                is >> v[i];
            }
            return is;
        }
    }
}

