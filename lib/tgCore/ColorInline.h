// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        template<int C, typename T>
        inline Color<C, T>::Color()
        {
            for (int i = 0; i < C; ++i)
            {
                _e[i] = T(0);
            }
        }

        template<int C, typename T>
        inline T Color<C, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<int C, typename T>
        inline T& Color<C, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<int C, typename T>
        inline const T* Color<C, T>::data() const
        {
            return _e.data();
        }

        template<int C, typename T>
        inline T* Color<C, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline Color<1, T>::Color() :
            l(_e[0]),
            _e({ 0 })
        {}

        template<typename T>
        inline Color<1, T>::Color(T l) :
            l(_e[0]),
            _e({ l })
        {}

        template<typename T>
        inline Color<1, T>::Color(const Color<1, T>& v) :
            l(_e[0]),
            _e(v._e)
        {}

        template<typename T>
        inline T Color<1, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Color<1, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Color<1, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Color<1, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline Color<1, T>& Color<1, T>::operator = (const Color<1, T>& v)
        {
            _e = v._e;
            return *this;
        }

        template<typename T>
        inline Color<2, T>::Color() :
            l(_e[0]),
            a(_e[1]),
            _e({ 0, 0 })
        {}

        template<typename T>
        inline Color<2, T>::Color(T l, T a) :
            l(_e[0]),
            a(_e[1]),
            _e({ l, a })
        {}

        template<>
        inline Color<2, float>::Color(float l) :
            l(_e[0]),
            a(_e[1]),
            _e({ l, a })
        {}

        template<typename T>
        inline Color<2, T>::Color(const Color<2, T>& v) :
            l(_e[0]),
            a(_e[1]),
            _e(v._e)
        {}

        template<typename T>
        inline T Color<2, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Color<2, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Color<2, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Color<2, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline Color<2, T>& Color<2, T>::operator = (const Color<2, T>& v)
        {
            _e = v._e;
            return *this;
        }

        template<typename T>
        inline Color<3, T>::Color() :
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            _e({ 0, 0, 0 })
        {}

        template<typename T>
        inline Color<3, T>::Color(T r, T g, T b) :
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            _e({ r, g, b })
        {}

        template<typename T>
        inline Color<3, T>::Color(const Color<3, T>& v) :
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            _e(v._e)
        {}

        template<typename T>
        inline T Color<3, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Color<3, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Color<3, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Color<3, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline Color<3, T>& Color<3, T>::operator = (const Color<3, T>& v)
        {
            _e = v._e;
            return *this;
        }

        template<typename T>
        inline Color<4, T>::Color() :
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3]),
            _e({ 0, 0, 0, 0 })
        {}

        template<typename T>
        inline Color<4, T>::Color(T r, T g, T b, T a) :
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3]),
            _e({ r, g, b, a })
        {}

        template<>
        inline Color<4, float>::Color(float r, float g, float b) :
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3]),
            _e({ r, g, b, 1.F })
        {}

        template<typename T>
        inline Color<4, T>::Color(const Color<4, T>& v) :
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3]),
            _e(v._e)
        {}

        template<typename T>
        inline T Color<4, T>::operator [] (int i) const
        {
            return _e[i];
        }

        template<typename T>
        inline T& Color<4, T>::operator [] (int i)
        {
            return _e[i];
        }

        template<typename T>
        inline const T* Color<4, T>::data() const
        {
            return _e.data();
        }

        template<typename T>
        inline T* Color<4, T>::data()
        {
            return _e.data();
        }

        template<typename T>
        inline Color<4, T>& Color<4, T>::operator = (const Color<4, T>& v)
        {
            _e = v._e;
            return *this;
        }

        template<int C, typename T>
        inline bool operator == (const Color<C, T>& a, const Color<C, T>& b)
        {
            bool out = true;
            for (int i = 0; i < C; ++i)
            {
                out &= a[i] == b[i];
            }
            return out;
        }
        
        template<int C, typename T>
        inline bool operator != (const Color<C, T>& a, const Color<C, T>& b)
        {
            return !(a == b);
        }
        
        template<int C, typename T>
        inline std::ostream& operator << (std::ostream& os, const Color<C, T>& v)
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
        inline std::istream& operator >> (std::istream& is, Color<C, T>& v)
        {
            for (int i = 0; i < C; ++i)
            {
                is >> v[i];
            }
            return is;
        }
    }
}
