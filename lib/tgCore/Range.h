// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <iostream>

namespace tg
{
    namespace math
    {
        //! Number range.
        template<typename T>
        class Range
        {
        public:
            constexpr Range() noexcept;
            explicit constexpr Range(T minMax) noexcept;
            constexpr Range(T min, T max);

            //! Get the minimum value.
            constexpr T getMin() const noexcept;

            //! Get the maximum value.
            constexpr T getMax() const noexcept;

            //! Set the range minimum and maximum to zero.
            void zero() noexcept;

            //! Does the range contain the given number?
            constexpr bool contains(T) const noexcept;

            //! Does the range interset the given range?
            constexpr bool intersects(const Range<T>&) const noexcept;

            //! Expand the range to include the given number.
            void expand(T);

            //! Expand the range to include the given range.
            void expand(const Range<T>&);

            //! \name Operators
            ///@{

            constexpr bool operator == (const Range<T>&) const;
            constexpr bool operator != (const Range<T>&) const;
            constexpr bool operator  < (const Range<T>&) const;

            ///@}

        private:
            T _min, _max;
        };

        //! Integer range.
        typedef Range<int> IntRange;

        //! A size_t range.
        typedef Range<size_t> SizeTRange;

        //! Floating point range.
        typedef Range<float> FloatRange;

        //! \name Operators
        ///@{

        std::ostream& operator << (std::ostream&, const IntRange&);
        std::ostream& operator << (std::ostream&, const SizeTRange&);
        std::ostream& operator << (std::ostream&, const FloatRange&);

        ///@}
    }
}

#include <tgCore/RangeInline.h>
