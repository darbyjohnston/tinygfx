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
            _e({ 0 }),
            l(_e[0])
        {}

        template<typename T>
        inline Color<1, T>::Color(T l) :
            _e({ l }),
            l(_e[0])
        {}

        template<typename T>
        inline Color<1, T>::Color(const Color<1, T>& v) :
            _e(v._e),
            l(_e[0])
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
            _e({ 0, 0 }),
            l(_e[0]),
            a(_e[1])
        {}

        template<typename T>
        inline Color<2, T>::Color(T l, T a) :
            _e({ l, a }),
            l(_e[0]),
            a(_e[1])
        {}

        template<>
        inline Color<2, float>::Color(float l) :
            _e({ l, a }),
            l(_e[0]),
            a(_e[1])
        {}

        template<typename T>
        inline Color<2, T>::Color(const Color<2, T>& v) :
            _e(v._e),
            l(_e[0]),
            a(_e[1])
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
            _e({ 0, 0, 0 }),
            r(_e[0]),
            g(_e[1]),
            b(_e[2])
        {}

        template<typename T>
        inline Color<3, T>::Color(T r, T g, T b) :
            _e({ r, g, b }),
            r(_e[0]),
            g(_e[1]),
            b(_e[2])
        {}

        template<typename T>
        inline Color<3, T>::Color(const Color<3, T>& v) :
            _e(v._e),
            r(_e[0]),
            g(_e[1]),
            b(_e[2])
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
            _e({ 0, 0, 0, 0 }),
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3])
        {}

        template<typename T>
        inline Color<4, T>::Color(T r, T g, T b, T a) :
            _e({ r, g, b, a }),
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3])
        {}

        template<>
        inline Color<4, float>::Color(float r, float g, float b) :
            _e({ r, g, b, 1.F }),
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3])
        {}

        template<typename T>
        inline Color<4, T>::Color(const Color<4, T>& v) :
            _e(v._e),
            r(_e[0]),
            g(_e[1]),
            b(_e[2]),
            a(_e[3])
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
