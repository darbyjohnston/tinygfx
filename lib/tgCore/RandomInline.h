// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        template<typename T>
        inline const T& Random::getItem(const std::vector<T>& value)
        {
            return value[getI(0, static_cast<int>(value.size()) - 1)];
        }
    }
}
