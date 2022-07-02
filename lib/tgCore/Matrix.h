// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

namespace tg
{
    namespace math
    {
        //! 3x3 matrix.
        template<typename T>
        class Matrix3x3
        {
        public:
            constexpr Matrix3x3() noexcept;
            constexpr Matrix3x3(
                T e0, T e1, T e2,
                T e3, T e4, T e5,
                T e6, T e7, T e8) noexcept;

            T e[9];

            //! \name Operators
            ///@{

            constexpr bool operator == (const Matrix3x3<T>&) const;
            constexpr bool operator != (const Matrix3x3<T>&) const;

            ///@}
        };

        //! 4x4 matrix.
        template<typename T>
        class Matrix4x4
        {
        public:
            constexpr Matrix4x4() noexcept;
            constexpr Matrix4x4(
                T e0, T e1, T e2, T e3,
                T e4, T e5, T e6, T e7,
                T e8, T e9, T e10, T e11,
                T e12, T e13, T e14, T e15) noexcept;

            T e[16];

            //! \name Operators
            ///@{

            constexpr bool operator == (const Matrix4x4<T>&) const;
            constexpr bool operator != (const Matrix4x4<T>&) const;

            ///@}
        };

        //! \name Transforms
        ///@{

        //! Create a translation matrix.
        template<typename T>
        constexpr Matrix4x4<T> translate(const Vector3<T>&);

        //! Create a X rotation matrix.
        template<typename T>
        Matrix4x4<T> rotateX(T);

        //! Create a Y rotation matrix.
        template<typename T>
        Matrix4x4<T> rotateY(T);

        //! Create a Z rotation matrix.
        template<typename T>
        Matrix4x4<T> rotateZ(T);

        //! Create a scale matrix.
        template<typename T>
        constexpr Matrix4x4<T> scale(const Vector3<T>&);

        //! Create an orthographic matrix.
        template<typename T>
        Matrix4x4<T> ortho(T left, T right, T bottom, T top, T near, T far);

        //! Create a perspective matrix.
        template<typename T>
        Matrix4x4<T> perspective(T fov, T aspect, T near, T far);

        ///@}

        //! 3x3 floating point matrix.
        typedef Matrix3x3<float> Matrix3x3f;

        //! 4x4 floating point matrix.
        typedef Matrix4x4<float> Matrix4x4f;

        //! \name Operators
        ///@{

        template<typename T>
        constexpr Matrix3x3<T> operator * (const Matrix3x3<T>&, const Matrix3x3<T>&);
        template<typename T>
        constexpr Matrix4x4<T> operator * (const Matrix4x4<T>&, const Matrix4x4<T>&);

        std::ostream& operator << (std::ostream&, const Matrix3x3f&);
        std::ostream& operator << (std::ostream&, const Matrix4x4f&);

        ///@}
    }
}

#include <tgCore/MatrixInline.h>
