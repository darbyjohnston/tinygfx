// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Path.h>

namespace tg
{
    //! File system.
    namespace file
    {
        // Does a file exist?
        bool exists(const Path&);

        // Get the temporary directory.
        std::string getTemp();

        // Create a temporary directory.
        std::string createTempDir();
    }
}
