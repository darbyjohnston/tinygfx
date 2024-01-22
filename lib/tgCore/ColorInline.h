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
            _e({ 0 })
        {}

        template<typename T>
        inline Color<1, T>::Color(T l) :
            _e({ l })
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
        inline T Color<1, T>::l() const
        {
            return _e[0];
        }

        template<typename T>
        inline T& Color<1, T>::l()
        {
            return _e[0];
        }

        template<typename T>
        inline Color<2, T>::Color() :
            _e({ 0, 0 })
        {}

        template<typename T>
        inline Color<2, T>::Color(T l, T a) :
            _e({ l, a })
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
        inline T Color<2, T>::l() const
        {
            return _e[0];
        }

        template<typename T>
        inline T Color<2, T>::a() const
        {
            return _e[1];
        }

        template<typename T>
        inline T& Color<2, T>::l()
        {
            return _e[0];
        }

        template<typename T>
        inline T& Color<2, T>::a()
        {
            return _e[1];
        }

        template<typename T>
        inline Color<3, T>::Color() :
            _e({ 0, 0, 0 })
        {}

        template<typename T>
        inline Color<3, T>::Color(T r, T g, T b) :
            _e({ r, g, b })
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
        inline T Color<3, T>::r() const
        {
            return _e[0];
        }

        template<typename T>
        inline T Color<3, T>::g() const
        {
            return _e[1];
        }

        template<typename T>
        inline T Color<3, T>::b() const
        {
            return _e[2];
        }

        template<typename T>
        inline T& Color<3, T>::r()
        {
            return _e[0];
        }

        template<typename T>
        inline T& Color<3, T>::g()
        {
            return _e[1];
        }

        template<typename T>
        inline T& Color<3, T>::b()
        {
            return _e[2];
        }

        template<typename T>
        inline Color<4, T>::Color() :
            _e({ 0, 0, 0, 0 })
        {}

        template<typename T>
        inline Color<4, T>::Color(T r, T g, T b, T a) :
            _e({ r, g, b, a })
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
        inline T Color<4, T>::r() const
        {
            return _e[0];
        }

        template<typename T>
        inline T Color<4, T>::g() const
        {
            return _e[1];
        }

        template<typename T>
        inline T Color<4, T>::b() const
        {
            return _e[2];
        }

        template<typename T>
        inline T Color<4, T>::a() const
        {
            return _e[3];
        }

        template<typename T>
        inline T& Color<4, T>::r()
        {
            return _e[0];
        }

        template<typename T>
        inline T& Color<4, T>::g()
        {
            return _e[1];
        }

        template<typename T>
        inline T& Color<4, T>::b()
        {
            return _e[2];
        }

        template<typename T>
        inline T& Color<4, T>::a()
        {
            return _e[3];
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
