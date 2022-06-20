// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Range.h>

namespace tg
{
    namespace math
    {
        std::ostream& operator << (std::ostream& os, const IntRange& value)
        {
            os << value.getMin() << "-" << value.getMax();
            return os;
        }

        std::ostream& operator << (std::ostream& os, const SizeTRange& value)
        {
            os << value.getMin() << "-" << value.getMax();
            return os;
        }

        std::ostream& operator << (std::ostream& os, const FloatRange& value)
        {
            os << value.getMin() << "-" << value.getMax();
            return os;
        }
    }
}

