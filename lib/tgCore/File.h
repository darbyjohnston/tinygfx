// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Util.h>

#include <filesystem>
#include <iostream>
#include <vector>

namespace tg
{
    namespace core
    {
        //! \name Files
        ///@{

        //! Get the list of file system drives.
        std::vector<std::filesystem::path> getDrives();

        //! User paths.
        enum class UserPath
        {
            Home,
            Desktop,
            Documents,
            Downloads,

            Count,
            First = Home
        };
        TG_ENUM(UserPath);

        //! Get a user path.
        std::filesystem::path getUserPath(UserPath);
        
        ///@}
    }
}
