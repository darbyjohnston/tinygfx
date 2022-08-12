// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Matrix.h>
#include <tgCore/Vector3.h>

#include <sstream>

namespace tg
{
    namespace math
    {
        //! 4x4 matrix.
        template<typename T>
        class Matrix<4, 4, T>
        {
        public:
            Matrix();
            Matrix(
                T e0, T e1, T e2, T e3,
                T e4, T e5, T e6, T e7,
                T e8, T e9, T e10, T e11,
                T e12, T e13, T e14, T e15);

            //! Get the underlying array.
            constexpr const std::array<T, 4 * 4>& getArray() const;

            //! Get a pointer to the data.
            constexpr const T* getData() const;

            constexpr T operator [] (size_t) const;
            T& operator [] (size_t);

            bool operator == (const Matrix<4, 4, T>&) const;
            bool operator != (const Matrix<4, 4, T>&) const;

        private:
            std::array<T, 4 * 4> _v;
        };

        //! 4x4 floating point matrix.
        typedef Matrix<4, 4, float> Matrix4x4f;

        //! \name Transforms
        ///@{

        //! Create a translation matrix.
        template<typename T>
        constexpr Matrix<4, 4, T> translate(const Vector<3, T>&);

        //! Create a X rotation matrix.
        template<typename T>
        Matrix<4, 4, T> rotateX(T);

        //! Create a Y rotation matrix.
        template<typename T>
        Matrix<4, 4, T> rotateY(T);

        //! Create a Z rotation matrix.
        template<typename T>
        Matrix<4, 4, T> rotateZ(T);

        //! Create a scale matrix.
        template<typename T>
        constexpr Matrix<4, 4, T> scale(const Vector<3, T>&);

        //! Create an orthographic matrix.
        template<typename T>
        Matrix<4, 4, T> ortho(T left, T right, T bottom, T top, T near, T far);

        //! Create a perspective matrix.
        template<typename T>
        Matrix<4, 4, T> perspective(T fov, T aspect, T near, T far);

        ///@}

        //! \name Operators
        ///@{

        template<typename T>
        constexpr Matrix<4, 4, T> operator * (const Matrix<4, 4, T>&, const Matrix<4, 4, T>&);

        template<typename T>
        std::ostream& operator << (std::ostream&, const Matrix<4, 4, T>&);

        ///@}
    }
}

#include <tgCore/Matrix4Inline.h>
