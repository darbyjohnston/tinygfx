// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgRender/ImageOptions.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <algorithm>
#include <array>

namespace tg
{
    namespace render
    {
        TG_ENUM_IMPL(
            InputVideoLevels,
            "FromFile",
            "FullRange",
            "LegalRange");

        TG_ENUM_IMPL(
            AlphaBlend,
            "None",
            "Straight",
            "Premultiplied");

        TG_ENUM_IMPL(
            ImageFilter,
            "Nearest",
            "Linear");
    }
}
