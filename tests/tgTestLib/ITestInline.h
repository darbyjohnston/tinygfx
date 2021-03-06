// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Assert.h>

#include <sstream>

namespace tg
{
    namespace tests
    {
        template<typename T>
        inline void ITest::_enum(
            const std::string& name,
            const std::function<std::vector<T>(void)>& value)
        {
            for (auto i : value())
            {
                {
                    std::stringstream ss;
                    ss << name << ": " << i;
                    _print(ss.str());
                }
                {
                    std::stringstream ss;
                    ss << i;
                    T j;
                    ss >> j;
                    TINYGFX_ASSERT(i == j);
                }
            }
        }
    }
}
