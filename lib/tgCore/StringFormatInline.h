// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <sstream>

namespace tg
{
    namespace string
    {
        template<typename T>
        inline Format& Format::arg(T value)
        {
            std::stringstream ss;
            ss << value;
            return arg(ss.str());
        }
    }
}
