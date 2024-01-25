// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/WidgetOptions.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <algorithm>
#include <array>

namespace tg
{
    namespace ui
    {
        TG_ENUM_IMPL(
            Orientation,
            "Horizontal",
            "Vertical");

        TG_ENUM_IMPL(
            Stretch,
            "Fixed",
            "Expanding");

        TG_ENUM_IMPL(
            HAlign,
            "Left",
            "Center",
            "Right");

        TG_ENUM_IMPL(
            VAlign,
            "Top",
            "Center",
            "Bottom");
    }
}

