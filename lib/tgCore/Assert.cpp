// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Assert.h>

#include <iostream>

#include <stdlib.h>

namespace tg
{
    namespace core
    {
        void _assert(const char* file, int line)
        {
            std::cout << "ASSERT: " << file << ":" << line << std::endl;
            abort();
        }
    }
}
