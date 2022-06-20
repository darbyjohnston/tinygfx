// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Assert.h>

#include <iostream>

#include <stdlib.h>

namespace tg
{
    namespace error
    {
        void _assert(const char* file, int line)
        {
            std::cout << "ASSERT: " << file << ":" << line << std::endl;
            abort();
        }
    }
}