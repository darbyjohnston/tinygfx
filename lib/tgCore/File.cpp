// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/File.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <algorithm>
#include <array>

namespace tg
{
    namespace core
    {
        TG_ENUM_IMPL(
            UserPath,
            "Home",
            "Desktop",
            "Documents",
            "Downloads");
    }
}

