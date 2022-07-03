// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <iostream>

namespace tg
{
    namespace math
    {
        //! Two-dimensional vector.
        template<typename T>
        class Vector2
        {
        public:
            constexpr Vector2() noexcept;
            constexpr Vector2(T, T) noexcept;

            T x, y;

            //! \name Operators
            ///@{

            constexpr bool operator == (const Vector2<T>&) const;
            constexpr bool operator != (const Vector2<T>&) const;

            Vector2<T>& operator += (const Vector2<T>&);
            Vector2<T>& operator -= (const Vector2<T>&);
            Vector2<T>& operator *= (const Vector2<T>&);
            Vector2<T>& operator /= (const Vector2<T>&);

            Vector2<T>& operator += (T);
            Vector2<T>& operator -= (T);
            Vector2<T>& operator *= (T);
            Vector2<T>& operator /= (T);

            operator Vector2<float>() const;

            ///@}
        };

        //! Three-dimensional vector.
        template<typename T>
        class Vector3
        {
        public:
            constexpr Vector3() noexcept;
            constexpr Vector3(T, T, T) noexcept;

            T x, y, z;

            //! \name Operators
            ///@{

            constexpr bool operator == (const Vector3<T>&) const;
            constexpr bool operator != (const Vector3<T>&) const;

            Vector3<T>& operator += (const Vector3<T>&);
            Vector3<T>& operator -= (const Vector3<T>&);
            Vector3<T>& operator *= (const Vector3<T>&);
            Vector3<T>& operator /= (const Vector3<T>&);

            Vector3<T>& operator += (T);
            Vector3<T>& operator -= (T);
            Vector3<T>& operator *= (T);
            Vector3<T>& operator /= (T);

            ///@}
        };

        //! Four-dimensional vector.
        template<typename T>
        class Vector4
        {
        public:
            constexpr Vector4() noexcept;
            constexpr Vector4(T, T, T, T) noexcept;

            T x, y, z, w;

            //! \name Operators
            ///@{

            constexpr bool operator == (const Vector4<T>&) const;
            constexpr bool operator != (const Vector4<T>&) const;

            Vector4<T>& operator += (const Vector4<T>&);
            Vector4<T>& operator -= (const Vector4<T>&);
            Vector4<T>& operator *= (const Vector4<T>&);
            Vector4<T>& operator /= (const Vector4<T>&);

            Vector4<T>& operator += (T);
            Vector4<T>& operator -= (T);
            Vector4<T>& operator *= (T);
            Vector4<T>& operator /= (T);

            ///@}
        };

        //! Two-dimensional integer vector.
        typedef Vector2<int> Vector2i;

        //! Two-dimensional floating point vector.
        typedef Vector2<float> Vector2f;

        //! Three-dimensional floating point vector.
        typedef Vector3<float> Vector3f;

        //! Four-dimensional floating point vector.
        typedef Vector4<float> Vector4f;

        //! \name Functions
        ///@{

        //! Get the length of a vector.
        float length(const Vector2i&);

        //! Get the length of a vector.
        float length(const Vector2f&);

        //! Get the distance between two vectors.
        float distance(const Vector2i&, const Vector2i&);

        //! Get the distance between two vectors.
        float distance(const Vector2f&, const Vector2f&);

        ///@}

        //! \name Operators
        ///@{

        template<typename T>
        constexpr Vector2<T> operator + (const Vector2<T>&, const Vector2<T>&);
        template<typename T>
        constexpr Vector2<T> operator - (const Vector2<T>&, const Vector2<T>&);
        template<typename T>
        constexpr Vector2<T> operator * (const Vector2<T>&, const Vector2<T>&);
        template<typename T>
        constexpr Vector2<T> operator / (const Vector2<T>&, const Vector2<T>&);

        template<typename T>
        constexpr Vector2<T> operator + (const Vector2<T>&, T);
        template<typename T>
        constexpr Vector2<T> operator - (const Vector2<T>&, T);
        template<typename T>
        constexpr Vector2<T> operator * (const Vector2<T>&, T);
        template<typename T>
        constexpr Vector2<T> operator / (const Vector2<T>&, T);

        template<typename T>
        constexpr Vector3<T> operator + (const Vector3<T>&, const Vector3<T>&);
        template<typename T>
        constexpr Vector3<T> operator - (const Vector3<T>&, const Vector3<T>&);
        template<typename T>
        constexpr Vector3<T> operator * (const Vector3<T>&, const Vector3<T>&);
        template<typename T>
        constexpr Vector3<T> operator / (const Vector3<T>&, const Vector3<T>&);

        template<typename T>
        constexpr Vector3<T> operator + (const Vector3<T>&, T);
        template<typename T>
        constexpr Vector3<T> operator - (const Vector3<T>&, T);
        template<typename T>
        constexpr Vector3<T> operator * (const Vector3<T>&, T);
        template<typename T>
        constexpr Vector3<T> operator / (const Vector3<T>&, T);

        template<typename T>
        constexpr Vector4<T> operator + (const Vector4<T>&, const Vector4<T>&);
        template<typename T>
        constexpr Vector4<T> operator - (const Vector4<T>&, const Vector4<T>&);
        template<typename T>
        constexpr Vector4<T> operator * (const Vector4<T>&, const Vector4<T>&);
        template<typename T>
        constexpr Vector4<T> operator / (const Vector4<T>&, const Vector4<T>&);

        template<typename T>
        constexpr Vector4<T> operator + (const Vector4<T>&, T);
        template<typename T>
        constexpr Vector4<T> operator - (const Vector4<T>&, T);
        template<typename T>
        constexpr Vector4<T> operator * (const Vector4<T>&, T);
        template<typename T>
        constexpr Vector4<T> operator / (const Vector4<T>&, T);

        std::ostream& operator << (std::ostream&, const Vector2i&);
        std::ostream& operator << (std::ostream&, const Vector2f&);
        std::ostream& operator << (std::ostream&, const Vector3f&);
        std::ostream& operator << (std::ostream&, const Vector4f&);

        ///@}
    }
}

#include <tgCore/VectorInline.h>